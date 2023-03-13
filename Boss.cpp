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
			int choice = rand() % 2;
			if (choice == 0) {
				mRect.x -= 5;
			}
			else if (choice == 1) {
				mRect.x += 5;
			}
			else if (choice == 2) {
				mRect.y -= 5;
			}
			else {
				mRect.y += 5;
			}

			if (mRect.x <= 500) {
				mRect.x = 500;
			}
			if (mRect.x >= 1000) {
				mRect.x = 1000;
			}
			if (mRect.y <= 0) {
				mRect.y = 0;
			}
			if (mRect.y >= 400) {
				mRect.y = 400;
			}

			handleBulletMove();
		}
		
	}
}
void Boss::handleAction(SDL_Renderer *renderer) {
	if (mState == NORMAL && checkToFire(1000)) {
		fire(renderer);
	}
}



void Boss::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		SDL_Rect rect = mBulletList[i]->getRect();
		rect.x = rect.x - 10;
		rect.y = mRect.y + 100;
		mBulletList[i]->setRect(rect.x, rect.y);

		if (rect.x <= 0) {
			mBulletList[i]->setIsMove(false);
		}
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


bool Boss::checkToFire(int t) {
	if (SDL_GetTicks64() - mFireTime >= t) {
		mFireTime = SDL_GetTicks64();
		return true;
	}
	return false;
}

bool Boss::checkToAppear(int t) {
	if (SDL_GetTicks64() - mAppearTime >= t) {
		mAppearTime = SDL_GetTicks64();
		return true;
	}
	return false;
}
void Boss::fire(SDL_Renderer* renderer) {
	
	Bullet* newBullet = new Bullet();
	newBullet->loadImage(renderer, "Image_folder/Airplane/Bomber/Charge_1.png");
	newBullet->setIsMove(true);
	newBullet->setRect(mRect.x, mRect.y + 100);
	mBulletList.push_back(newBullet);
	
}

void Boss::render(SDL_Renderer *renderer, int i) {
	if (mState != NOT_APPEAR) {
		Airplane::render(renderer, i);
	}
}