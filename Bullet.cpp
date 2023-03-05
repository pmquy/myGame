#include "Bullet.h"

Bullet::Bullet() {

};

Bullet::~Bullet() {

}


void Bullet::handleMove() {
	mRect.x -= 1;
	if (mRect.x <= 30) {
		mIsMove = false;
	}
}
void Bullet::setIsMove(bool state) {
	mIsMove = state;
}

bool Bullet::getIsMove() {
	return mIsMove;
}