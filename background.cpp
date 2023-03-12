#include "background.h"


Background::Background() {
	startTime = 0;
	mRect.x = mRect.y = mRect.w = mRect.h = 0;
	mState = LEVEL_1;
}

Background::~Background() {
	free();
}

void Background::handleMove() {
	int duration = SDL_GetTicks() - startTime;
	if (duration >= 20 && mState != LOSE) {
		mRect.x--;
		if (mRect.x <= -1200) mRect.x = 0;
		startTime = SDL_GetTicks();
	}
}

void Background::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	mTexture = mTextures[int(mState)];
	BaseClass::render(renderer);
	mRect.x += 1200;
	BaseClass::render(renderer);
	mRect.x -= 1200;
}

void Background::loadImage(SDL_Renderer* renderer, std::string s1, std::string s2) {
	SDL_Texture* loadedTexture1 = nullptr;
	SDL_Texture* loadedTexture2 = nullptr;
	loadedTexture1 = loadTexture(renderer, s1);
	loadedTexture2 = loadTexture(renderer, s2);
	mTextures.push_back(loadedTexture1);
	mTextures.push_back(loadedTexture2);
}

void Background::handleState(bool isLose) {
	if (isLose) {
		mState = LOSE;
		mTexture = mTextures[int(mState)];
		setRect(0, 0);
	}
	else {
		mState = LEVEL_1;
		mTexture = mTextures[int(mState)];
	}
}