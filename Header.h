#ifndef HEADER_H_
#define HEADER_H_

#include "BaseClass.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"
#include "Item.h"

enum Game1Type {
	START,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5,
	DEAD,
	SHOP,
	VICTORY,
	UPGRADE,
};

static std::vector<std::string> GAME_PATHS = { "Image_Folder/Background/Start.png", "Image_Folder/Background/Level_1.png", "Image_Folder/Background/Level_2.png", "Image_Folder/Background/Level_3.png", "Image_Folder/Background/Level_4.png", "Image_Folder/Background/Level_5.png", "Image_Folder/Background/Lose.png", "Image_Folder/Background/Shop.png", "Image_Folder/Background/Victory.png", "Image_Folder/Background/Upgrade.png" };



class Game1 : public BaseClass {
public:
	Character *hero = nullptr;
	std::vector<Bot*> bots;
	std::vector<Item*> items;
	Game1Type mState, oldState;
	std::vector<SDL_Texture*> mTextures;
	std::vector<Text*> texts;
	Mix_Chunk* mBonkMusic = nullptr;
	Mix_Music* mGameMusic = nullptr;
	TTF_Font* font = nullptr;

	void handleLogic(SDL_Renderer*);
	void loadResource(SDL_Renderer*);
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	void handleState(SDL_Renderer*, std::pair<int, int>, SDL_Event);
	void handleCollision(SDL_Renderer*);
	void renderText(SDL_Renderer*);
	void handleObject(SDL_Renderer*);
	Game1();
	

	Game1Type getState() {
		return mState;
	}
};


#endif
