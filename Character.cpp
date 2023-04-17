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
	mMaxBullet = 1;
	mCurrentSkill = 0;

	Skill* newSkill = new Skill(20, SkillType::BUFF_HP_SKILL);
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
			if (mState == NORMAL || mState == BOOSTING) {
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
			}
			break;
		case SDLK_f:
			useSkill(mSkillList[0]);
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
	if (mRect.x <= 0 - mRect.h/2) mRect.x = -mRect.h/2;
	if (mRect.x >= 1200 - mRect.h/2) mRect.x = 1200 - mRect.h/2;
	if (mRect.y <= -mRect.h/2) mRect.y = -mRect.h/2;
	if (mRect.y >= 600 - mRect.h/2) mRect.y = 600 - mRect.h/2;

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
		restart();
	}
	if (mState == FIRING && mCurrentFrame == mMaxFrames[int(mState)] - 1) {
		mState = NORMAL;
		mCurrentFrame = 0;
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->setIsMove(true);
		}
	}

}
	
void Character::renderText(SDL_Renderer* renderer, TTF_Font* font) {

	for (int i = 0; i < int(mSkillList.size()); i++) {
		if (mSkillList[i]->mIsAvailable == true) {
			Text* temp = mTextList[i];
			std::string name;
			if (mSkillList[i]->mType == BUFF_HP_SKILL) {
				name = "buff hp : ";
			}
			temp->loadText(renderer, font, name + std::to_string(mSkillList[i]->mCurrentTime));
			temp->render(renderer);
		}
	}
	mTextList.back()->loadText(renderer, font, BULLET_NAMES[int(mCurrentBullet)] + " : " + std::to_string(mBulletQuatity[int(mCurrentBullet)]));
	mTextList.back()->render(renderer);

}

bool Character::checkIsDestroyed() {

	return mHeart == 0 && mCurrentFrame == mMaxFrames[int(DESTROYED)] - 1 && mState == DESTROYED;

}
void Character::restart() {
	Airplane::restart();
	setRect(0, 0);
	mXVal = mYVal = 0;
	mSkillList[0]->mCurrentTime = 0;
	mMaxBullet = 1;
	mScore = 0;
	mCurrentBullet = BulletType::GREEN_BALL;
	mCurrentSkill = 0;
	mBulletQuatity = { 100, 100, 100 };
}
int Character::getCoin() {
	return mCoin;
}
void Character::setCoin(int c) {
	mCoin = c;
}
int Character::getScore() {
	return mScore;
}
void Character::setScore(int c) {
	mScore = c;
}
BulletType Character::getCurrentBullet() {
	return mCurrentBullet;
}
void Character::setCurrentBullet(BulletType t) {
	mCurrentBullet = t;
}





