#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH;
	mRect.y = 10;
	mAttack = 1;
};

Bot::~Bot() {
	
}


void Bot::handleMove() {
	if (checkToMove(20)) {
		mRect.x -= 2;
		handleBulletMove();
	}
}


void Bot::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		mBulletList[i]->handleMove();
	}
}



void Bot::handleState() {
	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}

	if (mRect.x <= 0 || (mState == DESTROYED && mCurrentFrame == 0)) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
		mHeart = 100;
		mRect.x = SCREEN_WIDTH;
		mRect.y = rand() % 400;
	}
	if (mState == DESTROYED) {
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->free();
			delete mBulletList[i];
			mBulletList[i] = nullptr;
			mBulletList.erase(mBulletList.begin() + i);
		}
	}
}



void Bot::handleAction(SDL_Renderer *renderer) {
	fire(renderer);
}


void Bot::fire(SDL_Renderer* renderer) {
	if (checkToFire(3000)) {
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, "Image_folder/Airplane/Bomber/Charge_1.png");
		newBullet->setIsMove(true);
		newBullet->setType(Type::NGUOC);
		newBullet->setRect(mRect.x, mRect.y + 100);
		mBulletList.push_back(newBullet);
	}
}