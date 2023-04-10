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
	BaseClass::loadImage(renderer, mPath[int(t)]);
}