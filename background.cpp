#include "background.h"


Background::Background() {
	startTime = 0;
	mRect.x = mRect.y = mRect.w = mRect.h = 0;
	mState = START;
}

Background::~Background() {
	free();
}

void Background::handleMove() {
	int duration = SDL_GetTicks() - startTime;
	if (duration >= 20 && mState == LEVEL_1) {
		mRect.x--;
		if (mRect.x <= -1200) mRect.x = 0;
		startTime = SDL_GetTicks();
	}
}

void Background::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	mTexture = mTextures[int(mState)];
	if (mState == LEVEL_1) {
		BaseClass::render(renderer);
		mRect.x += 1200;
		BaseClass::render(renderer);
		mRect.x -= 1200;
	}
	else {
		BaseClass::render(renderer);
	}
}

void Background::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	SDL_Texture* loadedTexture = nullptr;
	for (std::string s : listName) {
		loadedTexture = loadTexture(renderer, s);
		mTextures.push_back(loadedTexture);
	}
}

void Background::handleState(SDL_Renderer* renderer, std::pair<int, int>& mouse) {
	if (mState == DEAD) {
		mState = DEAD;
		mTexture = mTextures[int(mState)];
		setRect(0, 0);
	}
	 
	if (mState == START) {
		
	}

	if (mState == LEVEL_1) {
		mState = LEVEL_1;
	}



}

