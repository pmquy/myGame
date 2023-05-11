#ifndef BASECLASS_H
#define BASECLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BMP = 32;

static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path) {
	SDL_Texture* loadedTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		std::cout << "loaded surface failed" << path << std::endl;
	}
	else {
		loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (loadedTexture == nullptr) {
			std::cout << "loaded texture failed";
		}
		SDL_FreeSurface(loadedSurface);
	}
	return loadedTexture;
}

class BaseClass {
	public:
		BaseClass();
		~BaseClass();
		void setRect(const int& x, const int& y, const int& w = 0, const int& h = 0);
		SDL_Rect getRect();
		SDL_Texture* getTexture();
		virtual void loadImage(SDL_Renderer* renderer, std::string path);
		virtual void render(SDL_Renderer* renderer, const SDL_Rect *clip = nullptr);
		virtual void handleMove();
		void free();

		friend bool checkCollision(BaseClass *a, BaseClass *b) {
			int x11 = a->getRect().x + a->mDx;
			int y11 = a->getRect().y + a->mDy;
			int x12 = x11 + a->mWidth;
			int y12 = y11 + a->mHeight;

			int x21 = b->getRect().x + b->mDx;
			int y21 = b->getRect().y + b->mDy;
			int x22 = x21 + b->mWidth;
			int y22 = y21 + b->mHeight;

			if (x12 < x21 || x22 < x11 || y11 > y22 || y12 < y21) return false;
			return true;
		}

		int mXVal;
		int mYVal;
	protected:
		SDL_Texture* mTexture;
		SDL_Rect mRect;
		Uint64 mMoveTime = 0;
		bool checkToMove(int);
		int mDx;
		int mDy;
		int mHeight;
		int mWidth;
};


#endif 

