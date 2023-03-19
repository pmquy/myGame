#include "Bullet.h"

Bullet::Bullet() {
	mIsMove = true;
};


Bullet::~Bullet() {
	free();
}

void Bullet::free() {
	BaseClass::free();
	mIsMove = false;
}


void Bullet::handleMove() {
	if (mType == XUOI) {
		mRect.x += 5;
	}
	else if (mType == NGUOC) {
		mRect.x -= 5;
	}
	else if (mType == CHEOLEN) {
		mRect.x -= 5;
		mRect.y -= 1;
	}
	else if (mType == CHEOXUONG) {
		mRect.x -= 5;
		mRect.y += 1;
	}

	if (mRect.x <= 0 || mRect.x >= 1200 || mRect.y <= 0 || mRect.y >= 600) {
		mIsMove = false;
	}
}
void Bullet::setIsMove(bool state) {
	mIsMove = state;
}

bool Bullet::getIsMove() {
	return mIsMove;
}

Type Bullet::getType() {
	return mType;
}

void Bullet::setType(const Type& t) {
	mType = t;
}