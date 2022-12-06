#pragma once
#include <vector>

#include "Image.h"
#include "utils.h"

using namespace std;

typedef int IMAGE_TYPE;

extern IMAGE_TYPE IMAGE_ALWAYS_LOADED;
extern IMAGE_TYPE IMAGE_GENERIC_MENU;
extern IMAGE_TYPE IMAGE_PLAYING;
extern IMAGE_TYPE IMAGE_GAME_CHOOSER;

#define NUMBER_OF_IMAGE_SLOTS images.size()

namespace res {
	extern vector<Image*> images;
	extern Image container, ball, allWhite, circle, baseCard, baseOutline, desciptionFocus, coin, debt, cardGrey, bg, cardBase, secondaryCard, secondaryNight, tempIcon, eventOutline, eventSide, eventBase, eventSecondary, vpToken, potion, baseCardOutline, baseCardColor, baseCardSide, traveler;
	string getAvalible();
	int reserveNextSpot();
	void initial();
	void unloadAll();
	void unload(IMAGE_TYPE type);
	void load(IMAGE_TYPE type);
	void unloadAndLoad(IMAGE_TYPE type);
	Image setupImage(string path, bool hasTrans, IMAGE_TYPE typee);
}
