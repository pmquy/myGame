#include "Bullet.h"

Bullet::Bullet() {
	mIsMove = false;
};


Bullet::~Bullet() {

}


void Bullet::handleMove() {
	mRect.x += 1;
	if (mRect.x >= 400) {
		mIsMove = false;
	}
}
void Bullet::setIsMove(bool state) {
	mIsMove = state;
}

bool Bullet::getIsMove() {
	return mIsMove;
}