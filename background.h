#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "BaseClass.h"

enum BKG {
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
	void handleState(BKG &, SDL_Renderer*, std::pair<int, int>&, SDL_Event &);
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string> &listName);

	BKG getState() {
		return mState;
	}
	void setState(BKG s) {
		mState = s;
	}

private:
	BKG mState;
	UINT32 startTime;
	std::vector<SDL_Texture*> mTextures;
};


#endif