#include "Character.h"

Character::Character() {
	
	mXVal = 0;
	mYVal = 0;
	mMaxHeart = 50;
	mHeart = 50;
	mAttack = 5;
	mCoin = 100;
	mRect.x = 0;
	mRect.y = 200;
	mScore = 0;
	mAmor = 0;

	Skill* newSkill = new Skill(20, "heal");
	newSkill->mIsAvailable = true;
	mSkillList.push_back(newSkill);

	Text* newText = new Text();
	newText->setRect(1000, 0);
	mTextList.push_back(newText);

	Text* newText1 = new Text();
	newText1->setRect(0, 500);
	mTextList.push_back(newText1);
}

Character::~Character() {
	free();
	for (auto &it : mTextList) {
		it->free();
		delete it;
		it = nullptr;
	}
}

void Character::handleAction(const SDL_Event &event, SDL_Renderer* renderer) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			if (mState == NORMAL || mState == BOOSTING) {
				mYVal = -5;
				mState = BOOSTING;
			}
			break;
		case SDLK_DOWN:
			if (mState == NORMAL || mState == BOOSTING) {
				mYVal = 5;
				mState = BOOSTING;
			}
			break;
		case SDLK_RIGHT:
			if (mState == NORMAL || mState == BOOSTING) {
				mState = BOOSTING;
				mXVal = 5;
			}
			break;
		case SDLK_LEFT:
			if (mState == NORMAL || mState == BOOSTING) {
				mState = BOOSTING;
				mXVal = -5;
			}
			break;
		case SDLK_a:
			if (mCurrentBullet == BulletType::GREEN_BALL) {
				mCurrentBullet = BulletType::RED_BALL;
			}
			else if (mCurrentBullet == BulletType::RED_BALL) {
				mCurrentBullet = BulletType::BLUE_BALL;
			}
			else {
				mCurrentBullet = BulletType::GREEN_BALL;
			}
			break;
		case SDLK_q:
			if (mState == NORMAL) {
				for (int i = -mMaxBullet / 2; i <= mMaxBullet / 2; i++) {
					if (i == 0 && mMaxBullet % 2 == 0)
						continue;
					Bullet* newBullet = new Bullet();
					newBullet->loadImage(renderer, mCurrentBullet);
					newBullet->setRect(mRect.x + mRect.w, mRect.y + mRect.h / 2);
					newBullet->setDirection(5, i);
					mBulletList.push_back(newBullet);
				}
				mCurrentFrame = 0;
				mState = FIRING;
				mBulletQuatity[mCurrentBullet] -= 3;
			}
			break;
		case SDLK_f:
			if (mState != DESTROYED) {
				if (mSkillList[0]->mIsAvailable && mSkillList[0]->mCurrentTime == 0) {
					mHeart += 0.25 * mMaxHeart;
					if (mHeart >= mMaxHeart) {
						mHeart = mMaxHeart;
					}
					mSkillList[0]->mCurrentTime = mSkillList[0]->mMaxTime;
				}
			}
			break;
		}
	}

	else if (event.type == SDL_KEYUP) {
		
		switch (event.key.keysym.sym) {

		case SDLK_UP:
		case SDLK_DOWN:
			mYVal = 0;
			if (mState != FIRING) {
				mCurrentFrame = 0;
				mState = NORMAL;
			}
			break;
		case SDLK_LEFT:
		case SDLK_RIGHT:
			mXVal = 0;
			if (mState != FIRING) {
				mCurrentFrame = 0;
				mState = NORMAL;
			}
			break;
		}
		
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {

	}
	else {

	}
}

void Character::handleMove() {
	if (mRect.x <= 0) mRect.x = 0;
	if (mRect.x >= 1200 - 192) mRect.x = 1200 - 192;
	if (mRect.y <= 0) mRect.y = 0;
	if (mRect.y >= 600 - 192) mRect.y = 600 - 192;

	if (checkToMove(10)) {
		if (mState == NORMAL || mState == BOOSTING) {
			BaseClass::handleMove();
		}
		handleBulletMove();
	}
}

void Character::handleBulletMove() {
	for (int i = 0; i < int(mBulletList.size()); i++) {
		mBulletList[i]->handleMove();
	}
}

void Character::handleState(SDL_Renderer* renderer) {

	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = 0;
	}

	if (mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)] - 1) {
		reborn();
	}

	if (mState == FIRING && mCurrentFrame == mMaxFrames[int(mState)] - 1) {
		mState = NORMAL;
		mCurrentFrame = 0;
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->setIsMove(true);
		}
	}

}

	





