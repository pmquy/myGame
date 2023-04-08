#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "BaseClass.h"
#include "Character.h"
#include "Bot.h"

enum BackgroundType {
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


class Background : public BaseClass {
public:

	Background();
	~Background();
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void handleState(SDL_Renderer*, std::pair<int, int>&, SDL_Event&, Character*, BackgroundType&, std::vector<Bot*>&);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string> &listName);
	void handleLogic(SDL_Renderer*, Character*, std::vector<Bot*>&);

	BackgroundType getState() {
		return mState;
	}
	void setState(BackgroundType s) {
		mState = s;
	}

private:
	BackgroundType mState;
	std::vector<SDL_Texture*> mTextures;
};


#endif