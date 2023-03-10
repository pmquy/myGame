#include "Bullet.h"

Bullet::Bullet() {
	mIsMove = true;
};


Bullet::~Bullet() {

}


void Bullet::handleMove() {

}
void Bullet::setIsMove(bool state) {
	mIsMove = state;
}

bool Bullet::getIsMove() {
	return mIsMove;
}