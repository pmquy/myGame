#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH;
	mRect.y = 10;

	Bullet* bullet = new Bullet();
	bullet->setIsMove(false);
	bullet->setRect(0, mRect.y + 100);
	mBulletList.push_back(bullet);
};

Bot::~Bot() {
	
}



void Bot::handleMove() {

	if (checkToMove()) {
		mRect.x -= 2;
		handleBulletMove();
	}
	if (mRect.x <= 3 || (mState == DESTROYED && mCurrentFrame == 0)) {
		reborn();
		mRect.x = SCREEN_WIDTH;
	}
}


void Bot::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		SDL_Rect rect = mBulletList[i]->getRect();
		rect.x = rect.x - 10;
		if (rect.x <= 0)
			rect.x = mRect.x;
		mBulletList[i]->setRect(rect.x, rect.y);
	}
}