#include "Bullet.h"

Bullet::Bullet() {
	mIsMove = false;
	mIsAppear = true;
	mXVal = mYVal = 0;
};

Bullet::~Bullet() {
	free();
}

void Bullet::free() {
	BaseClass::free();
	mIsAppear = mIsMove = false;
}

void Bullet::handleMove() {
	if (mIsMove == true && mIsAppear == true) {
		mRect.x += mXVal;
		mRect.y += mYVal;
	}
	if (mRect.x <= 0 || mRect.x >= 1200 || mRect.y <= 0 || mRect.y >= 600) {
		mIsAppear = false;
	}
}
void Bullet::setIsMove(bool state) {
	mIsMove = state;
}

bool Bullet::getIsMove() {
	return mIsMove;
}

void Bullet::setDirection(int dx, int dy) {
	mXVal = dx;
	mYVal = dy;
}

void Bullet::loadImage(SDL_Renderer* renderer, BulletType t) {
	mBulletType = t;
	BaseClass::loadImage(renderer, BULLET_PATHS[int(t)]);
}

bool Bullet::getIsAppear() {
	return mIsAppear;
}

void Bullet::setIsAppear(bool t) {
	mIsAppear = t;
}
