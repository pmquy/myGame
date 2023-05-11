#include "Bot.h"

Bot::Bot() {
	frame = 1;
	mRect.x = SCREEN_WIDTH + rand() % 1000;
	mRect.y = rand() % 400;
	mAtk = mNormalAtk = 2;
	mNormalHp = mHp = 50;
	mDef = mNormalDef = 0;
	mXVal = -2;
	mYVal = 0;
};

Bot::~Bot() {
	
}

void Bot::handleMove() {
	if (checkToMove(20)) {
		Airplane::handleMove();
	}
	if (mRect.y <= 0) {
		mRect.y = 0;
		mYVal = 0;
	}
	if (mRect.y >= 400) {
		mRect.y = 400;
		mYVal = 0;
	}
}

void Bot::restart(SDL_Renderer* renderer) {
	Airplane::restart(renderer);
	this->loadImage(renderer, BOTS_PATHS[rand() % 3]);
	setRect(SCREEN_WIDTH + rand()%2000, rand() % 400);
}

void Bot::handleState(SDL_Renderer* renderer) {
	Airplane::handleState(renderer);
	
	if (mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)]) {
		restart(renderer);
	}
	if (mRect.x < -10 || mRect.y < -10) {
		restart(renderer);
	}
}

void Bot::changeDirection() {
	// tang ti le
	if ((mRect.x >= 1000) || rand()%3 == 0) {
		mXVal = -2;
		mYVal = 0;
	}
	else {
		mXVal = (rand() % 5 - 2);
		mYVal = (rand() % 5 - 2);
	}
}

void Bot::handleAction(SDL_Renderer *renderer) {
	if (checkToFire(3000) && (mState == NORMAL || mState == BOOSTING)) {
		BulletType type = static_cast<BulletType>(rand()%3);
		fire(renderer, type);
		setCurrentState(static_cast<State>(FIRING_RED + int(type)));
	}
	if (checkToTurn(3000)) {
		changeDirection();
	}
}

void Bot::fire(SDL_Renderer* renderer, BulletType bulletType) {
	int max = 1 + rand() % mNormalBullet;
	for (int i = -max / 2; i <= max / 2; i++) {
		if (i == 0 && max % 2 == 0)
			continue;
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, bulletType);
		newBullet->setRect(mRect.x + 10, mRect.y + mRect.h / 2);
		newBullet->setDirection(-5, i);
		mBulletList.push_back(newBullet);
	}
}

bool Bot::checkToTurn(long long t) {
	if (SDL_GetTicks64() - mTurnTime >= int(t)) {
		mTurnTime = SDL_GetTicks64();
		return true;
	}
	return false;
}

