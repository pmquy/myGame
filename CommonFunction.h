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
static SDL_Color gTextColor = { 100, 100, 100 };


SDL_Texture* loadTexture(SDL_Renderer*, std::string);

const std::vector<std::string> HERO_PATHS = { "Image_Folder/Airplane/Fighter/Idle.png", "Image_Folder/Airplane/Fighter/Destroyed.png", "Image_Folder/Airplane/Fighter/Attack_1.png","Image_Folder/Airplane/Fighter/Boost.png"  };
const std::vector<std::string> BOT1_PATHS = { "Image_Folder/Airplane/Bomber/Idle.png", "Image_Folder/Airplane/Bomber/Destroyed.png", "Image_Folder/Airplane/Bomber/Attack_1.png" };
const std::vector<std::string> BOT2_PATHS = { "Image_Folder/Airplane/Bomber/Idle.png", "Image_Folder/Airplane/Bomber/Destroyed.png", "Image_Folder/Airplane/Bomber/Attack_1.png" };
const std::vector<std::string> BOT3_PATHS = { "Image_Folder/Airplane/Corvette/Idle.png", "Image_Folder/Airplane/Corvette/Destroyed.png", "Image_Folder/Airplane/Corvette/Attack_1.png" };
const std::vector<std::string> BACKGROUND_PATHS = { "Image_Folder/Background/Start.png", "Image_Folder/Background/Level_1.jpg", "Image_Folder/Level_2.png" , "Image_Folder/Background/Lose.png", "Image_Folder/Background/Shop.png", "Image_Folder/Background/Victory.png" };




#endif 

