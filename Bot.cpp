#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH;
	mRect.y = rand() % 400;
	mAttack = 1;
};

Bot::~Bot() {
	free();
}


void Bot::handleMove() {
	if (checkToMove(20)) {
		mRect.x -= 2;
		if (mType == SHIP2 && mRect.x <= 700) {
			mRect.x = 700;
		}
		handleBulletMove();
	}
}


void Bot::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		mBulletList[i]->handleMove();
	}
}


void Bot::reborn() {
	Airplane::reborn();
	setRect(SCREEN_WIDTH, rand() % 400);
}

void Bot::handleState() {

	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}

	if (mRect.x <= 0 || checkIsDestroyed()) {
		reborn();
	}

}



void Bot::handleAction(SDL_Renderer *renderer) {
	if (checkToFire(3000)) {
		fire(renderer);
	}
}


void Bot::fire(SDL_Renderer* renderer) {
	
	if (mType == SHIP1) {
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, "Image_folder/Airplane/Bomber/Charge_1.png");
		newBullet->setType(Type::NGUOC);
		newBullet->setIsMove(true);
		newBullet->setRect(mRect.x, mRect.y + mRect.h/2);
		mBulletList.push_back(newBullet);
	}
	else if (mType == SHIP2) {
		Bullet* newBullet1 = new Bullet();
		Bullet* newBullet2 = new Bullet();
		Bullet* newBullet3 = new Bullet();
		newBullet1->loadImage(renderer, "Image_folder/sphere.png");
		newBullet1->setIsMove(true);
		newBullet1->setType(Type::CHEOLEN);
		newBullet1->setRect(mRect.x, mRect.y + mRect.h / 2);

		newBullet2->loadImage(renderer, "Image_folder/sphere.png");
		newBullet2->setIsMove(true);
		newBullet2->setType(Type::NGUOC);
		newBullet2->setRect(mRect.x, mRect.y + mRect.h / 2);

		newBullet3->loadImage(renderer, "Image_folder/sphere.png");
		newBullet3->setIsMove(true);
		newBullet3->setType(Type::CHEOXUONG);
		newBullet3->setRect(mRect.x, mRect.y + mRect.h / 2);

		mBulletList.push_back(newBullet1);
		mBulletList.push_back(newBullet2);
		mBulletList.push_back(newBullet3);	
	}
}