#include "Character.h"

Character::Character() {
	
	mXVal = 0;
	mYVal = 0;
	mHp = mMaxHp = 50;
	mAtk = mMaxAtk = 5;
	mDef = mMaxDef = 0;
	mCoin = 100;
	
	mRect.x = 0;
	mRect.y = 200;
	mScore = 0;
	mMaxBullet = 1;
	mCurrentSkill = 0;

	Skill* newSkill = new Skill(20, SkillType::BUFF_HP_SKILL);
	newSkill->mIsAvailable = true;
	mSkillList.push_back(newSkill);

	newSkill = new Skill(20, SkillType::BUFF_ATK_SKILL);
	newSkill->mIsAvailable = true;
	mSkillList.push_back(newSkill);

	Text* newText = new Text();
	newText->setRect(1050, 0);
	mTextList.push_back(newText);

	Text* newText1 = new Text();
	newText1->setRect(1050, 0);
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
		case SDLK_c:
			mCurrentSkill += 1;
			if (mCurrentSkill == mSkillList.size()) {
				mCurrentSkill = 0;
			}
			break;
		case SDLK_d:
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
			useSkill(mSkillList[mCurrentSkill]);
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

	if (mHp == 0 && mState != DESTROYED) {
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

	if (mSkillList[mCurrentSkill]->mIsAvailable == true) {
		Text* temp = mTextList[mCurrentSkill];
		std::string name;
		if (mSkillList[mCurrentSkill]->mType == BUFF_HP_SKILL) {
			name = "buff hp : ";
		}
		else if (mSkillList[mCurrentSkill]->mType == BUFF_ATK_SKILL) {
			name = "buff atk : ";
		}
		temp->loadText(renderer, font, name + std::to_string(mSkillList[mCurrentSkill]->mCurrentTime));
		temp->render(renderer);
	}

}

bool Character::checkIsDestroyed() {

	return mHp == 0 && mCurrentFrame == mMaxFrames[int(DESTROYED)] - 1 && mState == DESTROYED;

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





