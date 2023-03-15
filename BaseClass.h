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
		virtual void loadImage(SDL_Renderer* renderer, std::string path);
		virtual void render(SDL_Renderer* renderer, const SDL_Rect *clip = nullptr);
		void free();

		friend bool checkConllision(BaseClass& a, BaseClass& b) {
			int x11 = a.getRect().x;
			int y11 = a.getRect().y;
			int x12 = a.getRect().x + a.getRect().w;
			int y12 = a.getRect().y + a.getRect().h;
			int x21 = b.getRect().x;
			int y21 = b.getRect().y;
			int x22 = b.getRect().x + b.getRect().w;
			int y22 = b.getRect().y + b.getRect().h;
			if (x12 < x21 || x22 < x11 || y11 > y22 || y12 < y21) return false;
			return true;
		}
	protected:
		SDL_Texture* mTexture;
		SDL_Rect mRect;
		
};


#endif 

