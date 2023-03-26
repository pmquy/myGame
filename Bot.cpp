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
		if (mBulletList[i]->mIsAppear != false) {
			mBulletList[i]->handleMove();
		}
	}
}


void Bot::reborn() {
	Airplane::reborn();
	setRect(SCREEN_WIDTH + rand() % 400, rand() % 400);
}

void Bot::handleState(SDL_Renderer* renderer) {

	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;

		while (!mBulletList.empty()) {
			mBulletList[0]->free();
			delete mBulletList[0];
			mBulletList[0] = nullptr;
			mBulletList.erase(mBulletList.begin());
		}
	}

	if (mRect.x <= 0 || checkIsDestroyed()) {
		reborn();
		int t = rand() % 3;
		if (t == 0) {
			loadImage(renderer, BOT1_PATHS);
		}
		else if (t == 1) {
			loadImage(renderer, BOT2_PATHS);
		}
		else {
			loadImage(renderer, BOT3_PATHS);
		}
	}

	if (mState == FIRING && mCurrentFrame == 0) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
		for (auto it = mBulletList.end() - 1; it != mBulletList.begin(); it--) {
			(*it)->mIsAppear = true;
		}
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
		newBullet->loadImage(renderer, "Image_folder/laser.png");
		newBullet->setBulletType(BulletType::NGUOC);
		newBullet->setIsMove(true);
		newBullet->mIsAppear = false;
		newBullet->setRect(mRect.x, mRect.y + mRect.h/2);
		mBulletList.push_back(newBullet);
	}
	else if (mType == SHIP2) {
		Bullet* newBullet1 = new Bullet();
		Bullet* newBullet2 = new Bullet();
		Bullet* newBullet3 = new Bullet();
		newBullet1->loadImage(renderer, "Image_folder/sphere.png");
		newBullet1->setIsMove(true);
		newBullet1->setBulletType(BulletType::CHEOLEN);
		newBullet1->setRect(mRect.x, mRect.y + mRect.h / 2);
		newBullet1->mIsAppear = false;

		newBullet2->loadImage(renderer, "Image_folder/sphere.png");
		newBullet2->setIsMove(true);
		newBullet2->setBulletType(BulletType::NGUOC);
		newBullet2->setRect(mRect.x, mRect.y + mRect.h / 2);
		newBullet1->mIsAppear = false;

		newBullet3->loadImage(renderer, "Image_folder/sphere.png");
		newBullet3->setIsMove(true);
		newBullet3->setBulletType(BulletType::CHEOXUONG);
		newBullet3->setRect(mRect.x, mRect.y + mRect.h / 2);
		newBullet3->mIsAppear = false;

		mBulletList.push_back(newBullet1);
		mBulletList.push_back(newBullet2);
		mBulletList.push_back(newBullet3);	
	}
	mState = FIRING;
	mCurrentFrame = mMaxFrames[int(FIRING)] - 1;
}