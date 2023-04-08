#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH + rand() % 1000;
	mRect.y = rand() % 500;
	mAttack = 2;
	mMaxHeart = 100;
	mHeart = 100;
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
		if (mBulletList[i]->getIsMove()) {
			mBulletList[i]->handleMove();
		}
	}
}


void Bot::reborn(SDL_Renderer* renderer) {
	Airplane::reborn();
	int t = rand() % 2;
	if (t == 0) {
		this->loadImage(renderer, BOT1_PATHS);
		this->setShipType(ShipType::SHIP1);
	}
	else if (t == 1) {
		this->loadImage(gRenderer, BOT2_PATHS);
		this->setShipType(ShipType::SHIP2);
	}
	t = rand() % 3;
	if (t == 0) {
		loadImage(renderer, BOT1_PATHS);
	}
	else if (t == 1) {
		loadImage(renderer, BOT2_PATHS);
	}
	else {
		loadImage(renderer, BOT3_PATHS);
	}
	setRect(SCREEN_WIDTH + rand() % 400, rand() % 400);
}

void Bot::handleState(SDL_Renderer* renderer) {

	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}

	if (mRect.x <= 0 || checkIsDestroyed()) {
		reborn(renderer);
	}

	if (mState == FIRING && mCurrentFrame == 0) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->setIsMove(true);
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
		std::string path = "Image_folder/Airplane/Bullet/bullet" + std::to_string(2 + rand()%3) + ".png";
		newBullet->loadImage(renderer, path);
		newBullet->setBulletType(BulletType::NGUOC);
		newBullet->setRect(mRect.x, mRect.y + mRect.h/2);
		mBulletList.push_back(newBullet);
	}
	else if (mType == SHIP2) {
		Bullet* newBullet1 = new Bullet();
		Bullet* newBullet2 = new Bullet();
		Bullet* newBullet3 = new Bullet();
		newBullet1->loadImage(renderer, "Image_folder/Airplane/Bullet/bullet1.png");
		newBullet1->setBulletType(BulletType::CHEOLEN);
		newBullet1->setRect(mRect.x, mRect.y + mRect.h / 2);

		newBullet2->loadImage(renderer, "Image_folder/Airplane/Bullet/bullet1.png");
		newBullet2->setBulletType(BulletType::NGUOC);
		newBullet2->setRect(mRect.x, mRect.y + mRect.h / 2);

		newBullet3->loadImage(renderer, "Image_folder/Airplane/Bullet/bullet1.png");
		newBullet3->setBulletType(BulletType::CHEOXUONG);
		newBullet3->setRect(mRect.x, mRect.y + mRect.h / 2);

		mBulletList.push_back(newBullet1);
		mBulletList.push_back(newBullet2);
		mBulletList.push_back(newBullet3);	
	}
	mState = FIRING;
	mCurrentFrame = mMaxFrames[int(FIRING)] - 1;
}