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

		friend bool checkConllision(BaseClass *a, BaseClass *b) {
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
	protected:
		SDL_Texture* mTexture;
		SDL_Rect mRect;
		UINT64 mMoveTime = 0;
		bool checkToMove(int);
		int mDx;
		int mDy;
		int mHeight;
		int mWidth;
};


#endif 

