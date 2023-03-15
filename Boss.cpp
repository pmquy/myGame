#include "Boss.h"


Boss::Boss() {
	mState = NOT_APPEAR;
	mRect.x = SCREEN_WIDTH;
	mRect.y = SCREEN_HEIGHT/2;
}
Boss::~Boss() {

}
void Boss::handleMove() {
	if (mState != NOT_APPEAR) {
		if (checkToMove(20)) {
			
			mRect.x -= 1;

			handleBulletMove();
		}
		
	}
}
void Boss::handleAction(SDL_Renderer *renderer) {
	if (mState == NORMAL) {
		fire(renderer);
	}
}



void Boss::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		mBulletList[i]->handleMove();
	}
}

void Boss::handleState() {
	if (mState == NOT_APPEAR && checkToAppear(10000)) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] -1;
		std::cout << 1;
	}

	if (mState != NOT_APPEAR) {
		if (mHeart == 0 && mState != DESTROYED) {
			mState = DESTROYED;
			mCurrentFrame = mMaxFrames[int(mState)] - 1;
		}

		if ((mState == DESTROYED && mCurrentFrame == 0)) {
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
}



bool Boss::checkToAppear(int t) {
	if (SDL_GetTicks64() - mAppearTime >= t) {
		mAppearTime = SDL_GetTicks64();
		return true;
	}
	return false;
}
void Boss::fire(SDL_Renderer* renderer) {
	if (checkToFire(3000)) {
		Bullet* newBullet1 = new Bullet();
		Bullet* newBullet2 = new Bullet();
		Bullet* newBullet3 = new Bullet();
		newBullet1->loadImage(renderer, "Image_folder/sphere.png");
		newBullet1->setIsMove(true);
		newBullet1->setType(Type::CHEOLEN);
		newBullet1->setRect(mRect.x, mRect.y + mRect.h/2);

		newBullet2->loadImage(renderer, "Image_folder/sphere.png");
		newBullet2->setIsMove(true);
		newBullet2->setType(Type::NGUOC);
		newBullet2->setRect(mRect.x, mRect.y + mRect.h/2);

		newBullet3->loadImage(renderer, "Image_folder/sphere.png");
		newBullet3->setIsMove(true);
		newBullet3->setType(Type::CHEOXUONG);
		newBullet3->setRect(mRect.x, mRect.y + mRect.h/2);

		mBulletList.push_back(newBullet1);
		mBulletList.push_back(newBullet2);
		mBulletList.push_back(newBullet3);
	}
}

void Boss::render(SDL_Renderer *renderer, int i) {
	if (mState != NOT_APPEAR) {
		Airplane::render(renderer, i);
	}
}