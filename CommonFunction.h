#ifndef COMMON_FUNCTION_
#define COMMON_FUNCTION_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BMP = 32;

static SDL_Window* gWindow = nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Event gEvent;
//static TTF_Font* gFont = nullptr;
static SDL_Color gTextColor = { 100, 100, 100 };



#endif 

