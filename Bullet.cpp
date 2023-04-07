#include "Bullet.h"

Bullet::Bullet() {
	mIsMove = false;
	mIsAppear = true;
	mBulletType = XUOI;
};


Bullet::~Bullet() {
	free();
}

void Bullet::free() {
	BaseClass::free();
	mIsMove = false;
}


void Bullet::handleMove() {
	if (mIsMove == true && mIsAppear == true) {

		if (mBulletType == XUOI) {
			mRect.x += 5;
		}
		else if (mBulletType == NGUOC) {
			mRect.x -= 5;
		}
		else if (mBulletType == CHEOLEN) {
			mRect.x -= 5;
			mRect.y -= 1;
		}
		else if (mBulletType == CHEOXUONG) {
			mRect.x -= 5;
			mRect.y += 1;
		}
		else if (mBulletType == XOAY) {
			mRect.x += 5;
			mRect.y += 3 - rand() % 7;
		}
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

BulletType Bullet::getBulletType() {
	return mBulletType;
}

void Bullet::setBulletType(const BulletType& t) {
	mBulletType = t;
}
