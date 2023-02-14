#include "TextureClass.h"


TextureClass::TextureClass() {
	mHeight = mWidth = 0;
	mTexture = nullptr;
}

TextureClass::~TextureClass() {
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
}

int TextureClass::getHeight() {
	return mHeight;
}

int TextureClass::getWidth() {
	return mWidth;
}

void TextureClass::loadFromFile(SDL_Renderer* renderer,std::string fileName) {
	SDL_Surface* loadedSurface = IMG_Load(fileName.c_str());
	mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
}

void TextureClass::render(SDL_Renderer* renderer,int x, int y, SDL_Rect* clip) {
	SDL_Rect offset = { x, y, mWidth, mHeight };
	if (clip != nullptr) {
		offset.w = clip->w;
		offset.h = clip->h;
	}
	SDL_RenderCopy(renderer, mTexture, clip, &offset);
}

void TextureClass::setHeight(int height) {
	mHeight = height;
}

void TextureClass::setWidth(int width) {
	mWidth = width;
}
