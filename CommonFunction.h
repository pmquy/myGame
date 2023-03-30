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

static Mix_Chunk* backgroundMusic = nullptr;
static Mix_Chunk* collisionMusic = nullptr;


SDL_Texture* loadTexture(SDL_Renderer*, std::string);

static std::vector<std::string> HERO_PATHS1 = { "Image_Folder/Airplane/Hero/Fighter/Idle.png", "Image_Folder/Airplane/Hero/Fighter/Destroyed.png", "Image_Folder/Airplane/Hero/Fighter/Attack_1.png","Image_Folder/Airplane/Hero/Fighter/Boost.png"  };
static std::vector<std::string> HERO_PATHS2 = { "Image_Folder/Airplane/Hero/Bomber/Idle.png", "Image_Folder/Airplane/Hero/Bomber/Destroyed.png", "Image_Folder/Airplane/Hero/Bomber/Attack_1.png","Image_Folder/Airplane/Hero/Bomber/Boost.png" };
static std::vector<std::string> HERO_PATHS3 = { "Image_Folder/Airplane/Hero/Corvette/Idle.png", "Image_Folder/Airplane/Hero/Corvette/Destroyed.png", "Image_Folder/Airplane/Hero/Corvette/Attack_1.png","Image_Folder/Airplane/Hero/Corvette/Boost.png" };

static std::vector<std::string> BOT1_PATHS = { "Image_Folder/Airplane/Bot/Bomber/Idle.png", "Image_Folder/Airplane/Bot/Bomber/Destroyed.png", "Image_Folder/Airplane/Bot/Bomber/Attack_1.png" };
static std::vector<std::string> BOT2_PATHS = { "Image_Folder/Airplane/Bot/Fighter/Idle.png", "Image_Folder/Airplane/Bot/Fighter/Destroyed.png", "Image_Folder/Airplane/Bot/Fighter/Attack_1.png" };
static std::vector<std::string> BOT3_PATHS = { "Image_Folder/Airplane/Bot/Corvette/Idle.png", "Image_Folder/Airplane/Bot/Corvette/Destroyed.png", "Image_Folder/Airplane/Bot/Corvette/Attack_1.png" };

static std::vector<std::string> BACKGROUND_PATHS = { "Image_Folder/Background/Start.png", "Image_Folder/Background/Level_1.jpg", "Image_Folder/Background/Level_2.png" , "Image_Folder/Background/Lose.png", "Image_Folder/Background/Shop.png", "Image_Folder/Background/Victory.png", "Image_Folder/Background/Upgrade.png" };




#endif 

