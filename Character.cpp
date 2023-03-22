#include "Character.h"

Character::Character() {
	mXVal = 0;
	mYVal = 0;
	mHeart = 100;
	mAttack = 3;
	mCoin = 0;
}

Character::~Character() {
	free();
}


void Character::handleAction(const SDL_Event &event, SDL_Renderer* renderer) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal = -3;
			break;
		case SDLK_DOWN:
			mYVal = 3;
			break;
		case SDLK_RIGHT:
			mXVal = 3;
			break;
		case SDLK_LEFT:
			mXVal = -3;
			break;
		}
		if (mState == NORMAL) {
			mState = BOOSTING;
		}
	}

	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal = 0;
			break;
		case SDLK_DOWN:
			mYVal = 0;
			break;
		case SDLK_RIGHT:
			mXVal = 0;
			break;
		case SDLK_LEFT:
			mXVal = 0;
			break;
		}
		if (mState == BOOSTING) {
			mCurrentFrame = 0;
			mState = NORMAL;
		}

	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (mState == NORMAL) {
			Bullet *newBullet = new Bullet();
			newBullet->setRect(mRect.x + mRect.w, mRect.y + mRect.h/2);
			newBullet->setIsMove(true);
			newBullet->mIsAppear = false;
		
			if (event.button.button == SDL_BUTTON_LEFT) {
				newBullet->loadImage(renderer, "Image_folder/green.png");
				newBullet->setBulletType(BulletType::XUOI);
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				newBullet->loadImage(renderer, "Image_folder/sphere.png");
				newBullet->setBulletType(BulletType::XOAY);
			}

			mBulletList.push_back(newBullet);
			mCurrentFrame = 0;
			mState = FIRING;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {

	}
	else {

	}
}

void Character::handleMove() {
	if (mState == NORMAL || mState == BOOSTING) {
		mRect.x += mXVal;
		mRect.y += mYVal;
	}
	
	if (mRect.x <= 0) mRect.x = 0;
	if (mRect.x >= 1200 - 192) mRect.x = 1200 - 192;
	if (mRect.y <= 0) mRect.y = 0;
	if (mRect.y >= 600 - 192) mRect.y = 600 - 192;

	if (checkToMove(10)) {
		handleBulletMove();
	}
	
}

void Character::handleBulletMove() {
	for (int i = 0; i < int(mBulletList.size()); i++) {
		mBulletList[i]->handleMove();
	}
}

void Character::handleState() {

	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = 0;
	}

	if (mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)] - 1) {
		reborn();
	}

	if (mState == FIRING && mCurrentFrame == mMaxFrames[int(FIRING)] - 1) {
		mCurrentFrame = 0;
		mState = NORMAL;
		if (!mBulletList.empty()) {
			mBulletList.back()->mIsAppear = true;
		}
	}
}


