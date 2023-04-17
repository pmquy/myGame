#ifndef GAME_H_
#define GAME_H_

#include "BaseClass.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"
#include "Item.h"
#include "Boss.h"

enum GameType {
	HOME,
	HOME1,
	START,
	START1,
	START2,
	START3,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LOSE,
	LOSE1,
	LOSE2,
	SHOP,
	SHOP1, 
	SHOP2,
	SHOP3,
	SHOP4,
	WIN,
	WIN1,
	WIN2,
	WIN3,
	UPGRADE,
	UPGRADE1,
	UPGRADE2,
	UPGRADE3,
	UPGRADE4,
	HOME2,
};

static std::vector<std::string> GAME_PATHS = {"Image_Folder/Background/Home/0.png", "Image_Folder/Background/Home/1.png","Image_Folder/Background/Start/0.png", "Image_Folder/Background/Start/1.png", "Image_Folder/Background/Start/2.png", "Image_Folder/Background/Start/3.png",  "Image_Folder/Background/Level/1.png", "Image_Folder/Background/Level/2.png", "Image_Folder/Background/Level/3.png", "Image_Folder/Background/Level/4.png", "Image_Folder/Background/Level/5.png", "Image_Folder/Background/Lose/0.png", "Image_Folder/Background/Lose/1.png", "Image_Folder/Background/Lose/2.png", "Image_Folder/Background/Shop/0.png", "Image_Folder/Background/Shop/1.png", "Image_Folder/Background/Shop/2.png", "Image_Folder/Background/Shop/3.png", "Image_Folder/Background/Shop/4.png", "Image_Folder/Background/Win/0.png", "Image_Folder/Background/Win/1.png", "Image_Folder/Background/Win/2.png", "Image_Folder/Background/Win/3.png", "Image_Folder/Background/Upgrade/0.png", "Image_Folder/Background/Upgrade/1.png", "Image_Folder/Background/Upgrade/2.png", "Image_Folder/Background/Upgrade/3.png", "Image_Folder/Background/Upgrade/4.png" };

class Game : public BaseClass {
public:
	Character *hero = nullptr;
	Boss* boss = nullptr;
	std::vector<Bot*> bots;
	std::vector<Item*> items;
	GameType mState, oldState;
	std::vector<SDL_Texture*> mTextures;
	std::vector<Text*> texts;
	Mix_Chunk* mBonkMusic = nullptr;
	Mix_Music* mGameMusic = nullptr;
	TTF_Font* font = nullptr;
	SDL_Color color;

	void loadResource(SDL_Renderer*);
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	void handleState(SDL_Renderer*, SDL_Event);
	void handleObject(SDL_Renderer*);
	void restart(SDL_Renderer*);
	Game();
	~Game();

	GameType getState() {
		return mState;
	}
private:
	void handleCollision(SDL_Renderer*);
};


#endif
