#include "background.h"


Background::Background() {
	startTime = 0;
	mRect.x = mRect.y = mRect.w = mRect.h = 0;
}

Background::~Background() {
	
}

void Background::handleMove() {
	int duration = SDL_GetTicks() - startTime;
	if (duration >= 20) {
		mRect.x--;
		std::cout << mRect.x << "\n";
		if (mRect.x <= -1200) mRect.x = 0;
		startTime = SDL_GetTicks();
	}
}

void Background::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	BaseClass::render(renderer);
	mRect.x += 1200;
	BaseClass::render(renderer);
	mRect.x -= 1200;
}

