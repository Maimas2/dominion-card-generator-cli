#pragma once
#ifndef GL_IS_INCLUDED
#define GL_IS_INCLUDED
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include <string>

using namespace std;

extern float width;
extern float height;

extern float pixelWidth;
extern float pixelHeight;

extern GLFWwindow* window;

extern float xStretch;
extern float yStretch;

extern float windowRatio, windowInverse;

extern bool testBool;
extern bool isFullscreen;

extern int currentFps;
extern int totalFramesEver;

float getHBorder();
float getYBorder();

void resetMatrix();

extern float delta;
extern float drawDelta, updateDelta;
extern float averageDrawDelta, averageUpdateDelta;
extern float progressThroughFrame;
extern float targetFixedFps;

extern string pathPrefix;

extern char* cardTitle;
extern char* cardType;
extern char* cardText;
extern char* cardCost;
extern char* cardPreview;
extern char* cardVersion;
extern char* cardCredit;
extern int   cardColor;
extern int   cardSecondary;
extern float xMove;
extern float yMove;
extern float zoom;
extern int   cardLayout;
extern bool  isLowRes;
extern bool  isScreenshotting;
extern bool  isTraveler;

extern float customCardColor[];
extern float customEmbellishmentColor[];
extern float customSideColor[];