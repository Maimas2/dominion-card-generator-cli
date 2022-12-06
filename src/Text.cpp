#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils.h"
#include "main.h"
#include "Log.h"
#include "Text.h"

#define cf Chars
#define LARGE_ICON_SIZE 0.24

#define Chars Charsets[currentFont + (isBold ? "b" : "")]

bool isDigit(char c);

struct Char {
	GLuint id;
	float width;
	float height;
	float bearX;
	float bearY;
	float advanceX;
	float advanceY;
	float xMax;
	float yMax;
	unsigned char represents;
};

typedef map<GLchar, Char> CharSet;

float currentFontHeight = 0.1f;

int fontSize = 144;
int totalSize;

float fontDownscale = 0.05f;

string currentFont;

map<string, CharSet> Charsets;

bool isTextLoaded = false;

FT_Library freetype;

bool  isDrawingIcons      = true;
bool  isDrawingLargeIcons = true;
float largeIconSize       = 4.f;

bool isBold = false;

char  digitList[]   = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', /* Account for misc symbols */ '?', '*'};
char  symbolList[]  = {'$', '@', '^', '%'};
vector<string> boldedWords = {"Action", "Buy", "Card", "Villager", "Coffer", "Favor", "Actions", "Buys", "Cards", "Villagers", "Coffers", "Favors"};
bool isDigit(char c) {
	for(int i = 0; i < 12; i++) {
		if(c == digitList[i]) return true;
	}
	return false;
}
bool isActualDigit(char c) {
	for(int i = 0; i < 10; i++) {
		if(c == digitList[i]) return true;
	}
	return false;
}
bool isIconSymbol(char c) {
	for(int i = 0; i < 12; i++) {
		if(c == symbolList[i]) return true;
	}
	return false;
}
string strip(string in) {
	int sp = 0;
	for(int i = 0; i < in.size(); i++) {
		if(in.at(i) != ' ') {
			break;
		}
		sp++;
	}
	return in.substr(sp, in.size()-sp);
}
bool isLargeCoin(string in) {
	if(in.size() < 1) return false;
	if(cardLayout == 1) return false;
	if(in.at(0) != '$' || in.size() == 1) return false;
	for(int i = 1; i < in.size(); i++) {
		if(!isDigit(in.at(i))) return false;
	}
	return true;
}
bool isLargeVP(string in) {
	if(in.size() < 1) return false;
	if(cardLayout == 1) return false;
	for(int i = 0; i < in.size(); i++) {
		if(i == in.size()-1) if(in.at(i) != '%') return false;
		if(!isDigit(in.at(0))) return false;
	}
	return true;
}
bool isLargeSymbol(string in) {
	return isLargeCoin(in) || isLargeVP(in);
}
void bindIconFromChar(char c) {
	if(c == '$') {
		res::coin.bind();
	} else if(c == '@') {
		res::debt.bind();
	} else if(c == '^') {
		res::potion.bind();
	} else if(c == '%') {
		res::vpToken.bind();
	}
}
int textInit() {
	if(isTextLoaded) {
		return 0;
	}
	if (FT_Init_FreeType(&freetype)) {
		Log::fatal("Could not load FreeType!", true);
	}
	
	return 0;
}
int loadFont(string fontPath, string name) {
	fontPath = pathPrefix + fontPath;
	if (fontPath.empty())
	{
		Log::spicyWarning("Font path was empty! Fonts will not be rendered properly, if at all.");
	}
	
	FT_Face* font = new FT_Face;
	if (FT_New_Face(freetype, fontPath.c_str(), 0, font)) {
		Log::spicyWarning("Could not load font" + fontPath + "! Fonts will not be rendered properly, if at all.");
	} else {
		FT_Set_Pixel_Sizes(*font, 0, fontSize);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		CharSet setToPush;

		for (unsigned char c = 0; c < 128; c++) {
			if (FT_Load_Char(*font, c, FT_LOAD_RENDER))
			{
				Log::warning(string("Failed to load char ") + string(reinterpret_cast<char*>(c)) + string("! Continuing, expect font failure/rendering issues."));
				continue;
			}
			GLuint charTexture;
			glGenTextures(1, &charTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, charTexture);
			unsigned char* buffer = (*font)->glyph->bitmap.buffer;
			
			int size = (*font)->glyph->bitmap.width * (*font)->glyph->bitmap.rows * 4;
			totalSize += size;
			
			unsigned char* buff = (unsigned char*)malloc(size);
			
			for(int i = 0; i < size; i += 4) {
				char currentPixel = buffer[i/4];
				bool isFilled = currentPixel != 0;
				buff[i]   = isFilled ? 255 : 0;
				buff[i+1] = isFilled ? 255 : 0;
				buff[i+2] = isFilled ? 255 : 0;
				buff[i+3] = isFilled ? 255 : 0;
			}
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				(*font)->glyph->bitmap.width,
				(*font)->glyph->bitmap.rows,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				buff
			);
			free(buff);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			Char ch = {
				charTexture,
				(*font)->glyph->bitmap.width/(float)fontSize,
				(*font)->glyph->bitmap.rows/(float)fontSize,
				(*font)->glyph->bitmap_left/(float)fontSize,
				(*font)->glyph->bitmap_top/(float)fontSize,
				((float)(*font)->glyph->advance.x)/(fontSize*64.f),
				((float)(*font)->glyph->advance.y)/(fontSize*64.f),
				(*font)->glyph->bitmap_left/(float)fontSize,
				(*font)->glyph->bitmap_top/(float)fontSize,
				c
			};
			setToPush.insert(pair<GLchar, Char>(c, ch));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		currentFontHeight = (((*font)->size->metrics.ascender - (*font)->size->metrics.descender) / 64) / (float)fontSize;
		
		Charsets[name] = setToPush;
	}
	FT_Done_Face(*font);
	
	isTextLoaded = true;
	
	if(currentFont == "") {
		currentFont = name;
	}
	
	return 0;
}
float getStringWidthRaw(string in, float scale) {
	if(currentFont == "") return 0.f;
	float wid = 0.f;
	bool isBoldSave = isBold;
	if(isLargeSymbol(in) && isDrawingLargeIcons) return 0.24f;
	
	for(int i = 0; i < in.size(); i++) {
		char n = in.at(i);
		if(n == '\n') {
			isBold = false;
			continue;
		}
		if(n == '+') {
			isBold = true;
		}
		if(isIconSymbol(n)) {
			int l = 0;
			for(int ii = i+1; ii < in.size(); ii++) {
				if(!isDigit(in.at(ii))) {
					break;
				}
				l++;
			}
			i += l;
			if(n == '^') {
				wid += (0.06f * (100.f/156.f)) * scale;
			} else {
				wid += 0.06f * scale;
			}
			continue;
		}
		
		Char currentChar = Charsets[currentFont + (isBold ? "b" : "")][in.at(i)];
		wid += currentChar.advanceX * scale * fontDownscale;
	}
	isBold = isBoldSave;
	return wid;
}
float getStringWidth(string in, float scale) {
	in += "\n";
	vector<string> strings = split(in, "\n");
	float max = 0.f, temp = 0.f;
	for(int i = 0; i < strings.size(); i++) {
		temp = getStringWidthRaw(strings[i], scale);
		if(temp > max) max = temp;
	}
	return max;
}
float getStringYMax(string in, float scale) {
	if(currentFont == "") 0.f;
	float curr = 0.f;
	if(isLargeSymbol(in) && isDrawingLargeIcons) return 0.24f;
	for(string::const_iterator currentCharr = in.begin(); currentCharr != in.end(); currentCharr++) {
		Char currentChar = Chars[*currentCharr];
		if(currentChar.yMax > curr) curr = currentChar.yMax;
	}
	return curr * (fontDownscale * scale);
}
float getStringHeight(string in, float scale) {
	if(currentFont == "") return 0.f;
	vector<string> ingore = split(in, "\n");
	float tr = 0.f;
	
	for(int i = 0; i < ingore.size()-1; i++) {
		if(isLargeSymbol(ingore[i])) {
			tr += LARGE_ICON_SIZE;
		} else {
			tr += (currentFontHeight * scale * fontDownscale);
		}
	}
	
	return tr + getStringYMax(in, scale);
}
float getStringHeightRequired(string in, float scale) {
	if(currentFont == "") return 0.f;
	vector<string> ingore = split(in, "\n");
	float tr = 0.f;
	
	for(int i = 0; i < ingore.size()-1; i++) {
		if(isLargeSymbol(ingore[i])) {
			tr += LARGE_ICON_SIZE;
		}
	}
	
	return tr;
}
float drawLargeIcon(string text, float x, float y) {
	float scale = largeIconSize;
	bool isVP = text.at(text.size()-1) == '%';
	isBold = true;
	
	float r = 0.f, g = 0.f, b = 0.f;
	if(text.at(0) == '@') {
		r = 1.f;
		g = 1.f;
		b = 1.f;
	}
	
	string tod;
	if(!isVP) {
		tod = text.substr(1, text.size()-1);
	} else {
		tod = text.substr(0, text.size()-1);
	}
	
	isDrawingIcons = false;
	isDrawingLargeIcons = false;
	if(!isVP) {
		bindIconFromChar(text.at(0));
		drawTexturedQuad(x-0.03*scale, y-0.06*scale, 0.06*scale, 0.06*scale);
		drawCenteredStringWithMaxWidth(tod, x, y-0.03*scale, scale, 0.045f*scale, r, g, b);
	} else {
		drawCenteredString(text, x, y-0.12f, scale, r, g, b);
	}
	isDrawingIcons = true;
	isDrawingLargeIcons = true;
	
	isBold = false;
	
	return LARGE_ICON_SIZE;
}
bool shouldBeBolded(string in) {
	if(in.size() <= 2)  return false;
	if(in.at(0) != '+') return false;
	
	for(int i = 1; i < in.size(); i++) {
		if(in.at(i) == ' ') {
			string after = in.substr(i+1, in.size()-i);
			
			for(int r = 0; r < boldedWords.size(); r++) {
				if(boldedWords[r] == after) return true;
			}
			return false;
		}
		if(!isActualDigit(in.at(i))) return false;
	}
	return true;
}
void drawString(string toRender, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	
	y -= getStringYMax(toRender, scale);
	scale *= fontDownscale;
	
	int unboldIn = 0;
	
	//float currentX = x/scale;
	float currentX = x/scale;
	float currentY = y/scale;
	float col[] = {
		r, g, b,
		r, g, b,
		r, g, b,
		r, g, b
	};
	
	int numberOfContinues = 0;
	bool isFirstCharacter = true;
	
	if(toRender == "-") {
		Char currentChar = cf['-'];
		glBindTexture(GL_TEXTURE_2D, currentChar.id);
		drawColoredTexture((currentX + currentChar.bearX)*scale-0.4, (currentY - (currentChar.height - currentChar.bearY))*scale, 0.f, currentChar.width*scale+0.8f, currentChar.height*scale, col);
		return;
	}
	if(shouldBeBolded(toRender)) {
		isBold = true;
	}
	
	for(string::const_iterator currentCharr = toRender.begin(); currentCharr != toRender.end(); currentCharr++) {
		if(numberOfContinues > 0) {
			numberOfContinues--;
			continue;
		}
		if(unboldIn > 0) {
			unboldIn--;
		}
		int pos = currentCharr - toRender.begin(); // https://stackoverflow.com/questions/6136362/convert-iterator-to-int
		int len;
		if(isFirstCharacter) {
			
			isFirstCharacter = false;
		}
		
		char n = toRender.at(pos);
		if(isDrawingIcons) {
			if(isIconSymbol(n)) {
				int ctype = 1;
				if(n == '$') {
					res::coin.bind();
					ctype = 1;
				} else if(n == '@') {
					res::debt.bind();
					ctype = 2;
				} else if(n == '^') {
					res::potion.bind();
					ctype = 3;
				} else if(n == '%') {
					res::vpToken.bind();
					ctype = 4;
				}
				
				float iconSize = 0.06f * (scale / fontDownscale);
				float iconScale= scale / fontDownscale;
				
				if(ctype == 3) {
					drawTexturedQuad(currentX*scale, currentY*scale-0.015*iconScale, iconSize*(100.f/156.f), iconSize);
				} else {
					drawTexturedQuad(currentX*scale, currentY*scale-0.015*iconScale, iconSize, iconSize);
				}
				int l = 0;
				for(int i = pos+1; i < toRender.size(); i++) {
					if(!isDigit(toRender.at(i))) {
						break;
					}
					l++;
				}
				numberOfContinues = l;
				isBold = false;
				//isDrawingIcons = false;
				string tod = toRender.substr(pos+1, l);
				float tods = scale/fontDownscale;
				float ttods;
				if((ttods = getStringWidth(tod, tods)) > 0.04f*(scale/fontDownscale)) {
					tods *= (0.04f*(scale/fontDownscale)) / ttods;
				}
				setFont("tnr");
				isBold = true;
				switch(ctype) {
					case 1:
						drawCenteredString(tod, currentX*scale+0.0285f*iconScale, currentY*scale+0.015f*iconScale, tods);
						break;
					case 2:
						drawCenteredString(tod, currentX*scale+0.0285f*iconScale, currentY*scale+0.015f*iconScale, tods, 1.f, 1.f, 1.f);
						break;
					case 3:
						drawCenteredString(tod, currentX*scale+0.018269231f*iconScale, currentY*scale+0.005f*iconScale, tods/1.5, 1.f, 1.f, 1.f);
						break;
					case 4:
						drawCenteredString(tod, currentX*scale+0.0285f*iconScale, currentY*scale+0.015f*iconScale, tods, 1.f, 1.f, 1.f);
						break;
					default:
						drawCenteredString(tod, currentX*scale+0.0285f*iconScale, currentY*scale+0.015f*iconScale, tods);
						break;
				};
				isDrawingIcons = true;
				if(ctype == 3) {
					currentX += (0.06f*(100.f/156.f)) / fontDownscale;
				} else {
					currentX += 0.06f / fontDownscale;
				}
				isBold = false;
				continue;
			}
		}
		if(n == '%') {
			res::vpToken.bind();
			float iconSize = 0.06f * (scale / fontDownscale);
			float iconScale= scale / fontDownscale;
			
			drawTexturedQuad(currentX*scale, currentY*scale-0.015*iconScale, iconSize, iconSize);
			
			currentX += 0.06f / fontDownscale;
			continue;
		}
		Char currentChar = cf[*currentCharr];
		if(currentChar.represents == '\n') {
			currentX  = x/scale;
			currentY -= currentFontHeight;
			isBold = false;
			isFirstCharacter = true;
			continue;
		}
		glBindTexture(GL_TEXTURE_2D, currentChar.id);
		drawColoredTexture((currentX + currentChar.bearX)*scale, (currentY - (currentChar.height - currentChar.bearY))*scale, 0.f, currentChar.width*scale, currentChar.height*scale, col);
		currentX += currentChar.advanceX;
	}
	isBold = false;
}
void drawString(string text, float x, float y, float scale) {
	drawString(text, x, y, scale, 0.f, 0.f, 0.f);
}
void drawCenteredStringSingleLine(string textt, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	
	y += getStringHeight(textt, scale)/2;
	
	drawString(textt, x - getStringWidth(textt, scale)/2, y, scale, r, g, b);
}
void drawCenteredString(string textt, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	
	y += getStringHeight(textt, scale)/2;
	
	vector<string> parts = split(strip(textt), "\n");
	
	for(int i = 0; i < parts.size(); i++) {
		if(isDrawingLargeIcons && isLargeSymbol(parts[i])) {
			string s = parts[i];
			
			y -= drawLargeIcon(parts[i], x, y);
			continue;
		}
		drawString(parts[i], x - getStringWidth(parts[i], scale)/2, y, scale, r, g, b);
		y -= currentFontHeight * scale * fontDownscale;
	}
	//drawString(textt, x, y, scale, r, g, b);
}
void drawCenteredString(string text, float x, float y, float scale) {
	drawCenteredString(text, x, y, scale, 0.f, 0.f, 0.f);
}
void drawVerticallyCenteredText(string in, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	string text = in + "\n";
	vector<string> parts;
	int pos;
	y += getStringYMax(in, scale)/2;
	while ((pos = text.find("\n")) != string::npos) {
		parts.push_back(text.substr(0, pos));
		text.erase(0, pos + string("\n").length());
	}
	float currentY = y;
	for(int i = 0; i < parts.size(); i++) {
		drawString(parts[i], x, y, scale, r, g, b);
		y -= currentFontHeight * (scale * fontDownscale);
	}
}
void drawVerticallyCenteredText(string in, float x, float y, float scale) {
	drawVerticallyCenteredText(in, x, y, scale, 0.f, 0.f, 0.f);
}
void drawRightAlignedVerticallyCenteredText(string in, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	string text = in + "\n";
	vector<string> parts;
	int pos;
	y += getStringYMax(in, scale)/2;
	x -= getStringWidth(in, scale);
	while ((pos = text.find("\n")) != string::npos) {
		parts.push_back(text.substr(0, pos));
		text.erase(0, pos + string("\n").length());
	}
	float currentY = y;
	for(int i = 0; i < parts.size(); i++) {
		drawString(parts[i], x, y, scale, r, g, b);
		y -= currentFontHeight * (scale * fontDownscale);
	}
}
void drawRightAlignedVerticallyCenteredText(string in, float x, float y, float scale) {
	drawRightAlignedVerticallyCenteredText(in, x, y, scale, 0.f, 0.f, 0.f);
}
void drawRightAlignedText(string in, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	string text = in + "\n";
	vector<string> parts;
	int pos;
	y -= getStringYMax(in, scale);
	x -= getStringWidth(in, scale);
	while ((pos = text.find("\n")) != string::npos) {
		parts.push_back(text.substr(0, pos));
		text.erase(0, pos + string("\n").length());
	}
	float currentY = y;
	for(int i = 0; i < parts.size(); i++) {
		drawString(parts[i], x, y, scale, r, g, b);
		y -= currentFontHeight * (scale * fontDownscale);
	}
}
void drawRightAlignedText(string in, float x, float y, float scale) {
	drawRightAlignedText(in, x, y, scale, 0.f, 0.f, 0.f);
}
void drawLeftAlignedVerticallyCenteredText(string in, float x, float y, float scale, float r, float g, float b) {
	if(currentFont == "") return;
	string text = in + "\n";
	vector<string> parts;
	int pos;
	y += getStringYMax(in, scale)/2;
	while ((pos = text.find("\n")) != string::npos) {
		parts.push_back(text.substr(0, pos));
		text.erase(0, pos + string("\n").length());
	}
	float currentY = y;
	for(int i = 0; i < parts.size(); i++) {
		drawString(parts[i], x, y, scale, r, g, b);
		y -= currentFontHeight * (scale * fontDownscale);
	}
}
void drawLeftAlignedVerticallyCenteredText(string in, float x, float y, float scale) {
	drawLeftAlignedVerticallyCenteredText(in, x, y, scale, 0.f, 0.f, 0.f);
}
void yes() {
	
}
void setFont(string nf) {
	currentFont = nf;
}
string clampStringToWidth(string in, float width, float scale) {
	if(currentFont == "") return "";
	float cl = 0.f;
	vector<string> tor;
	string building = "";
	vector<string> words = split(in, " ");
	for(int i = 0; i < words.size(); i++) {
		if(getStringWidth(words[i], scale) >= width) { // Failsafe to prevent infinite loop
			tor.push_back(building);
			tor.push_back(words[i]);
			building = "";
			cl = 0.f;
			continue;
		}
		
		if(cl + getStringWidth(" " + words[i], scale) > width) {
			tor.push_back(building);
			building = "";
			cl = 0.f;
			i--;
			continue;
		} else {
			cl += getStringWidth(" " + words[i], scale);
			building += " " + words[i];
		}
	}
	tor.push_back(building);
	string tr = "";
	for(int i = 0; i < tor.size(); i++) {
		tr += tor[i] + (i < tor.size()-1 ? "\n" : "");
	}
	return tr;
}
void drawCenteredStringWithMaxDimensions(string in, float x, float y, float scale, float maxWidth, float maxHeight, float r, float g, float b) {
	if(currentFont == "") return;
	
	float heightTemp, widthTemp;
	
	maxWidth /= 2;
	
	in = clampStringToWidth(in, maxWidth, maxHeight);
	
	vector<string> lines = split(in, "\n");
	if(isLargeSymbol(strip(lines[0]))) {
		y += 0.12f;
		maxHeight -= LARGE_ICON_SIZE;
	}
	
	//if((heightTemp = getStringHeight(in, scale)) > maxHeight-getStringHeightRequired(in, scale)) {
	if((heightTemp = getStringHeight(in, scale)) > maxHeight) {
		scale *= maxHeight / heightTemp;
		
	}
	/*if((widthTemp = getStringWidth(in, scale)) > maxWidth) {
		scale *= maxWidth / widthTemp;
	}*/
	
	drawCenteredString(in, x, y, scale, r, g, b);
}
void drawCenteredStringWithMaxDimensions(string in, float x, float y, float scale, float maxWidth, float maxHeight) {
	drawCenteredStringWithMaxDimensions(in, x, y, scale, maxWidth, maxHeight, 0.f, 0.f, 0.f);
}
void drawCenteredStringWithMaxWidth(string in, float x, float y, float scale, float maxWidth, float r, float g, float b) {
	if(currentFont == "") return;
	
	float widthTemp;
	
	if((widthTemp = getStringWidth(in, scale)) > maxWidth) {
		scale *= maxWidth / widthTemp;
	}
	
	drawCenteredStringSingleLine(in, x, y, scale, r, g, b);
}
void drawCenteredStringWithMaxWidth(string in, float x, float y, float scale, float maxWidth) {
	drawCenteredStringWithMaxDimensions(in, x, y, scale, maxWidth, 100, 0, 0, 0);
}