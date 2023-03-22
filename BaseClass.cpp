#include "BaseClass.h"


BaseClass::BaseClass() {
	mTexture = nullptr;
	mRect = { 0, 0, 0, 0 };
}

BaseClass::~BaseClass() {
	free();
}

void BaseClass::setRect(const int& x, const int& y, const int& w, const int& h) {
	mRect.x = x;
	mRect.y = y;
	if (w != 0) mRect.w = w;
	if (h != 0) mRect.h = h;
}


void BaseClass::loadImage(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	mRect.w = loadedSurface->w;
	mRect.h = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
}


void BaseClass::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	SDL_Rect renderQuad = { mRect.x, mRect.y, mRect.w, mRect.h };
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}


void BaseClass::free() {
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mRect.x = mRect.y = mRect.w = mRect.h = 0;
	}
}

SDL_Rect BaseClass::getRect() {
	return mRect;
}

SDL_Texture* BaseClass::getTexture() {
	return mTexture;
}