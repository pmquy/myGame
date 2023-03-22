#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "BaseClass.h"
#include "Character.h"

enum BackgroundType {
	START,
	LEVEL_1,
	LEVEL_2,
	DEAD,
	SHOP,
	VICTORY
};

class Background : public BaseClass {
public:

	Background();
	~Background();
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void handleState(BackgroundType &, SDL_Renderer*, std::pair<int, int>&, SDL_Event &, Character* = nullptr);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string> &listName);

	BackgroundType getState() {
		return mState;
	}
	void setState(BackgroundType s) {
		mState = s;
	}

private:
	BackgroundType mState;
	UINT32 startTime;
	std::vector<SDL_Texture*> mTextures;
};


#endif