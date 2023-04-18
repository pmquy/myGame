#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH + rand() % 1000;
	mRect.y = rand() % 400;
	mAtk = mMaxAtk = 2;
	mMaxHp = mHp = 100;
	mDef = mMaxDef = 0;
	mXVal = -2;
	mYVal = 0;
};

Bot::~Bot() {
	free();
}

void Bot::handleMove() {
	if (checkToMove(20) && mState != DESTROYED) {
		BaseClass::handleMove();
		if (mRect.y <= 0) {
			mRect.y = 0;
		}
		if (mRect.y >= 400) {
			mRect.y = 400;
		}
		handleBulletMove();
	}
}

void Bot::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		if (mBulletList[i]->getIsMove()) {
			mBulletList[i]->handleMove();
		}
	}
}

void Bot::restart(SDL_Renderer* renderer) {
	Airplane::restart();
	mXVal = -2;
	mYVal = 0;
	this->loadImage(renderer, BOTS_PATHS[rand() % 3]);
	setRect(SCREEN_WIDTH + rand() % 1000, rand() % 400);
}

void Bot::handleState(SDL_Renderer* renderer) {
	
	if (mHp == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
	
	if (mRect.x < -10 || mRect.y < -10 || checkIsDestroyed()) {
		restart(renderer);
	}
	
	if (mState == FIRING && mCurrentFrame == 0) {
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->setIsMove(true);
		}
		if (mXVal == 0 && mYVal == 0) {
			mState = NORMAL;
		}
		else {
			mState = BOOSTING;
		}
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
	
	if (mState == NORMAL && (mXVal || mYVal)) {
		mState = BOOSTING;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
	if (mState == BOOSTING && !mXVal && !mYVal) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
}

void Bot::changeDirection() {
	if ((mRect.x >= 1000) || rand()%2) {
		mXVal = -2;
		mYVal = 0;
	}
	else {
		mXVal = (rand() % 3 - 1) * 2;
		mYVal = (rand() % 3 - 1) * 1;
	}
}


void Bot::handleAction(SDL_Renderer *renderer) {
	if (checkToFire(3000) && (mState == NORMAL || mState == BOOSTING)) {
		fire(renderer);
		mState = FIRING;
		mCurrentFrame = mMaxFrames[int(FIRING)] - 1;
	}
	if (checkToTurn(3000)) {
		changeDirection();
	}

}

void Bot::fire(SDL_Renderer* renderer) {
	int max = 1 + rand() % 3;
	for (int i = -max / 2; i <= max / 2; i++) {
		if (i == 0 && max % 2 == 0)
			continue;
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, static_cast<BulletType>(rand() % 3));
		newBullet->setRect(mRect.x + 10, mRect.y + mRect.h / 2);
		newBullet->setDirection(-5, i);
		mBulletList.push_back(newBullet);
	}
}


bool Bot::checkIsDestroyed() {
	return mHp == 0 && mCurrentFrame == 0 && mState == DESTROYED;
}

bool Bot::checkToTurn(long long t) {
	if (SDL_GetTicks64() - mTurnTime >= t) {
		mTurnTime = SDL_GetTicks64();
		return true;
	}
	return false;
}

