#ifndef GAME_H_
#define GAME_H_

#include "BaseClass.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"
#include "Item.h"
#include "Boss.h"

enum GameState {
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
	SHOP5,
	SHOP6,
	SHOP7,
	SHOP8,
	SHOP9,
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

static std::vector<std::string> GAME_PATHS = {"Image_Folder/Background/Home/0.png", "Image_Folder/Background/Home/1.png","Image_Folder/Background/Start/0.png", "Image_Folder/Background/Start/1.png", "Image_Folder/Background/Start/2.png", "Image_Folder/Background/Start/3.png",  "Image_Folder/Background/Level/1.png", "Image_Folder/Background/Level/2.png", "Image_Folder/Background/Level/3.png", "Image_Folder/Background/Level/4.png", "Image_Folder/Background/Level/5.png", "Image_Folder/Background/Lose/0.png", "Image_Folder/Background/Lose/1.png", "Image_Folder/Background/Lose/2.png", "Image_Folder/Background/Shop/0.png", "Image_Folder/Background/Shop/1.png", "Image_Folder/Background/Shop/2.png", "Image_Folder/Background/Shop/3.png", "Image_Folder/Background/Shop/4.png", "Image_Folder/Background/Shop/5.png","Image_Folder/Background/Shop/6.png","Image_Folder/Background/Shop/7.png","Image_Folder/Background/Shop/8.png","Image_Folder/Background/Shop/9.png", "Image_Folder/Background/Win/0.png", "Image_Folder/Background/Win/1.png", "Image_Folder/Background/Win/2.png", "Image_Folder/Background/Win/3.png", "Image_Folder/Background/Upgrade/0.png", "Image_Folder/Background/Upgrade/1.png", "Image_Folder/Background/Upgrade/2.png", "Image_Folder/Background/Upgrade/3.png", "Image_Folder/Background/Upgrade/4.png" };

class Game : public BaseClass {
public:
	
	Character *hero;
	Boss* boss;
	std::vector<Bot*> bots;
	std::vector<Item*> items;
	std::vector<SDL_Texture*> mTextures;
	std::vector<Text*> texts;

	GameState mState, oldState;
	
	void loadResource(SDL_Renderer*);
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	void handleState(SDL_Renderer*, SDL_Event);
	void updateObject(SDL_Renderer*);

	Game();
	~Game();

	GameState getState() {
		return mState;
	}
private:
	void restart(SDL_Renderer*);
	void setUpLevel(SDL_Renderer*, GameState);

	Mix_Chunk* mBonkMusic;
	Mix_Music* mGameMusic;
	Mix_Chunk* mWinMusic;
	Mix_Chunk* mItemMusic;
	Mix_Chunk* mGameOverMusic;
	Mix_Music* mHomeMusic;
	Mix_Music* mIntroMusic;

	TTF_Font* font;
	SDL_Color color;
	void handleCollision(SDL_Renderer*);
};


#endif
