#include "Character.h"

Character::Character() {
	mXVal = 0;
	mYVal = 0;
	mHeart = 100;
}

Character::~Character() {

}


void Character::handleAction(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal -= 1;
			break;
		case SDLK_DOWN:
			mYVal += 1;
			break;
		case SDLK_RIGHT:
			mXVal += 1;
			break;
		case SDLK_LEFT:
			mXVal -= 1;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
	
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal = 0;
			break;
		case SDLK_DOWN:
			mYVal = 0;
			break;
		case SDLK_RIGHT:
			mXVal = 0;
			break;
		case SDLK_LEFT:
			mXVal = 0;
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		getDamage(10);
		if (mHeart <= 0) mHeart = 100;
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {

	}
	else {

	}
}

void Character::handleMove() {
	mRect.x += mXVal;
	mRect.y += mYVal;
	
	if (mRect.x <= 0) mRect.x = 0;
	if (mRect.x >= 1200 - 64) mRect.x = 1200 - 64;
	if (mRect.y <= 0) mRect.y = 0;
	if (mRect.y >= 600 - 91) mRect.y = 600 - 91;
}

