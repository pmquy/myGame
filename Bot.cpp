#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH;
	mRect.y = 10;

	Bullet* bullet = new Bullet();
	bullet->setIsMove(true);
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
}


void Bot::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		SDL_Rect rect = mBulletList[i]->getRect();
		rect.x = rect.x - 10;
		rect.y = mRect.y + 50;
		if (rect.x <= 0)
			rect.x = mRect.x;
		mBulletList[i]->setRect(rect.x, rect.y);
	}
}


void Bot::handleState() {
	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}

	if (mRect.x <= 0 || (mState == DESTROYED && mCurrentFrame == 0)) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
		mHeart = 100;
		mRect.x = SCREEN_WIDTH;
	}
}