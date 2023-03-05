#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH;
	mRect.y = 10;
	mHeart = 100;
	mStartTime = 0;
};

Bot::~Bot() {
	
}



void Bot::handleMove() {
	if (checkToMove()) {
		mRect.x -= 3;
	}
	if (mRect.x <= 0) {
		mRect.x = SCREEN_WIDTH;
	}
}