#ifndef TEXTURECLASS_H_
#define TEXTURECLASS_H_

#include "CommonFunction.h"


class BaseClass {

	public:
		BaseClass();
		~BaseClass();
		void setRect(const int& x, const int& y, const int& w = 0, const int& h = 0);
		SDL_Rect getRect();
		SDL_Texture* getTexture();
		void loadImage(SDL_Renderer* renderer, std::string path);
		void render(SDL_Renderer* renderer, const SDL_Rect *clip = nullptr);
		void free();
	protected:
		SDL_Texture* mTexture;
		SDL_Rect mRect;
};


#endif 

