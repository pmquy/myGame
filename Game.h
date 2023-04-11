#ifndef GAME_H_
#define GAME_H_

#include "BaseClass.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"
#include "Item.h"


static SDL_Window* gWindow = nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Event gEvent;


static std::pair<int, int> gMouse(0, 0); 
static Character hero;
static std::vector<Bot*> bots(10, nullptr);
static std::vector<Item*> items = {};


enum GameType {
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


class Game : public BaseClass {
public:
	Game();
	~Game();

	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void handleState(SDL_Renderer*, std::pair<int, int>&, SDL_Event&, Character*, GameType&, std::vector<Bot*>&);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string> &listName);
	void handleLogic(SDL_Renderer*, Character*, std::vector<Bot*>&);

	GameType getState() {
		return mState;
	}
	void setState(GameType s) {
		mState = s;
	}

	void playMusic() {
		Mix_PlayMusic(mGameMusic, -1);
	}
	void renderText(SDL_Renderer*, TTF_Font* font);
private:
	GameType mState;
	std::vector<SDL_Texture*> mTextures;
	void handleCollision(Character*, std::vector<Bot*>);
	Mix_Music* mGameMusic;
	Mix_Chunk* mBonkMusic;
	Text mScoreText;
	Text mCoinText;
	int mHeroScore;
	int mHeroCoin;
};


#endif