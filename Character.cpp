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
	mTextSkillList.push_back(newText);

}

Character::~Character() {
	free();
	for (auto &it : mTextSkillList) {
		it->free();
		delete it;
		it = nullptr;
	}
}


void Character::handleAction(const SDL_Event &event, SDL_Renderer* renderer) {
	
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal = -1;
			if (mState == NORMAL) {
				mState = BOOSTING;
			}
			break;
		case SDLK_DOWN:
			mYVal = 1;
			if (mState == NORMAL) {
				mState = BOOSTING;
			}
			break;
		case SDLK_RIGHT:
			if (mState == NORMAL) {
				mState = BOOSTING;
			}
			mXVal = 1;
			break;
		case SDLK_LEFT:
			if (mState == NORMAL) {
				mState = BOOSTING;
			}
			mXVal = -1;
			break;
		case SDLK_d:
			if (mState == NORMAL) {
				Bullet* newBullet = new Bullet();
				newBullet->setRect(mRect.x + mRect.w, mRect.y + mRect.h / 2);
				newBullet->loadImage(renderer, "Image_folder/Airplane/Bullet/bullet1.png");
				newBullet->setBulletType(BulletType::XUOI);
				mBulletList.push_back(newBullet);
				mCurrentFrame = 0;
				mState = FIRING;
			}
			break;
		case SDLK_f:
			if (mState == NORMAL) {
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
			mYVal = 0;
			if (mState == BOOSTING) {
				mCurrentFrame = 0;
				mState = NORMAL;
			}
			break;
		case SDLK_DOWN:
			if (mState == BOOSTING) {
				mCurrentFrame = 0;
				mState = NORMAL;
			}
			mYVal = 0;
			break;
		case SDLK_RIGHT:
			if (mState == BOOSTING) {
				mCurrentFrame = 0;
				mState = NORMAL;
			}
			mXVal = 0;
			break;
		case SDLK_LEFT:
			if (mState == BOOSTING) {
				mCurrentFrame = 0;
				mState = NORMAL;
			}
			mXVal = 0;
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
	if (mState == NORMAL || mState == BOOSTING) {
		mRect.x += mXVal;
		mRect.y += mYVal;
	}
	
	if (mRect.x <= 0) mRect.x = 0;
	if (mRect.x >= 1200 - 192) mRect.x = 1200 - 192;
	if (mRect.y <= 0) mRect.y = 0;
	if (mRect.y >= 600 - 192) mRect.y = 600 - 192;

	handleSkill();

	if (checkToMove(10)) {
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

	if (mState == FIRING && mCurrentFrame == mMaxFrames[int(FIRING)] - 1) {
		mCurrentFrame = 0;
		mState = NORMAL;
		if (!mBulletList.empty()) {
			mBulletList.back()->setIsMove(true);
		}
	}

}

	





