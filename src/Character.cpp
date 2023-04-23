#include "Character.h"

Character::Character() {
	frame = 0;
	
	mXVal = 0;
	mYVal = 0;
	mHp = mMaxHp = 50;
	mAtk = mMaxAtk = 5;
	mDef = mMaxDef = 0;
	mCoin = 300;
	mRect.x = 0;
	mRect.y = 200;
	mScore = 0;
	mMaxBullet = 1;
	mCurrentSkill = 0;
	mCurrentBullet = BulletType::GREEN_BALL;

	mScoreText = new Text(); mScoreText->setRect(0, 0);
	mCoinText = new Text(); mCoinText->setRect(0, 50);
	mSkillText = new Text(); mSkillText->setRect(0, 550);
}

Character::~Character() {
	free();
	delete mScoreText;
	delete mCoinText;
	delete mSkillText;
}

void Character::addSkill(SkillType t) {
	mSkillList.push_back(new Skill(20, t));
}

void Character::handleAction(const SDL_Event &event, SDL_Renderer* renderer) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			if (mState != DESTROYED) {
				mYVal = -5;
			}
			break;
		case SDLK_DOWN:
			if (mState != DESTROYED) {
				mYVal = 5;
			}
			break;
		case SDLK_RIGHT:
			if (mState != DESTROYED) {
				mXVal = 5;
			}
			break;
		case SDLK_LEFT:
			if (mState != DESTROYED) {
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
				fire(renderer);
				mState = FIRING;
				mCurrentFrame = 0;
			}
			break;
		case SDLK_f:
			if(mCurrentSkill < int(mSkillList.size())) {
				useSkill(mSkillList[mCurrentSkill]);
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

void Character::restart(SDL_Renderer* renderer) {
	Airplane::restart(renderer);
	setRect(0, 0);
	mXVal = mYVal = 0;
	for (auto& it : mSkillList) {
		it->mCurrentTime = 0;
	}
	mMaxBullet = 1;
	mScore = 0;
	mCurrentBullet = BulletType::GREEN_BALL;
	mCurrentSkill = 0;
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

void Character::renderCoin(SDL_Renderer* renderer, TTF_Font* font) {
	mCoinText->loadText(renderer, font, "Coin : " + std::to_string(mCoin));
	mCoinText->render(renderer);
}
void Character::renderScore(SDL_Renderer* renderer, TTF_Font* font) {
	mScoreText->loadText(renderer, font, "Score : " + std::to_string(mScore));
	mScoreText->render(renderer);
}
void Character::renderSkill(SDL_Renderer* renderer, TTF_Font* font) {
	if (int(mSkillList.size()) > 0 && mSkillList[mCurrentSkill]->mIsAvailable == true) {
		std::string name;
		if (mSkillList[mCurrentSkill]->mType == BUFF_HP_SKILL) {
			name = "buff hp : ";
		}
		else if (mSkillList[mCurrentSkill]->mType == BUFF_ATK_SKILL) {
			name = "buff atk : ";
		}
		else if (mSkillList[mCurrentSkill]->mType == SUPER) {
			name = "super : ";
		}
		mSkillText->loadText(renderer, font, name + std::to_string(mSkillList[mCurrentSkill]->mCurrentTime));
		mSkillText->render(renderer);
	}
}

void Character::fire(SDL_Renderer* renderer) {
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


