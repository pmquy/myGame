#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH + rand() % 1000;
	mRect.y = rand() % 400;
	mAttack = 2;
	mMaxHeart = 100;
	mHeart = 100;
	mType = SHIP1;
	mXVal = -2;
	mYVal = 0;
};

Bot::~Bot() {
	free();
}

void Bot::handleMove() {
	if (checkToMove(20) && mState != DESTROYED) {
		BaseClass::handleMove();
		if (mType == SHIP2 && mRect.x <= 700) {
			mRect.x = 700;
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

void Bot::reborn(SDL_Renderer* renderer) {
	Airplane::reborn();
	this->loadImage(renderer, BOTS_PATHS[rand() % 3]);
	this->setBotType(static_cast<BotType>(rand() % 2));
	setRect(SCREEN_WIDTH + rand() % 1000, rand() % 400);
}

void Bot::handleState(SDL_Renderer* renderer) {

	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
	if (mRect.x <= 0 || checkIsDestroyed()) {
		reborn(renderer);
	}
	if (mState == FIRING && mCurrentFrame == 0) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->setIsMove(true);
		}
	}
	if (mState == NORMAL) {
		mState = BOOSTING;
	}

	if (mState == BOOSTING && mRect.x == 700 && mType == SHIP2) {
		mState = NORMAL;
	}
}

void Bot::handleAction(SDL_Renderer *renderer) {
	if (checkToFire(3000) && (mState == NORMAL || mState == BOOSTING)) {
		fire(renderer);
	}
}

void Bot::fire(SDL_Renderer* renderer) {
	
	int max = 1 + rand() % 3;
	for (int i = -max / 2; i <= max / 2; i++) {
		if (i == 0 && max % 2 == 0)
			continue;
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, static_cast<BulletType>(rand() % 6));
		newBullet->setRect(mRect.x + 10, mRect.y + mRect.h / 2);
		newBullet->setDirection(-5, i);
		mBulletList.push_back(newBullet);
	}
	mState = FIRING;
	mCurrentFrame = mMaxFrames[int(FIRING)] - 1;

}

void Bot::setBotType(const BotType& t) {
	mType = t;
}

bool Bot::checkIsDestroyed() {
	return mHeart == 0 && mCurrentFrame == 0 && mState == DESTROYED;
}