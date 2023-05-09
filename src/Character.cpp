#include "Character.h"

Character::Character() {
	frame = 0;
	mXVal = 0; mNormalXVal = 5;
	mYVal = 0; mNormalYVal = 5;
	mHp = mNormalHp = 50;
	mAtk = mNormalAtk = 20;
	mDef = mNormalDef = 0;
	mCoin = 1000;
	mRect.x = 0;
	mRect.y = 200;
	mScore = 0;
	mNormalBullet = 1;
	mCurrentSkill = 0;
	mCurrentBullet = BulletType::GREEN_BALL;

	mScoreText = new Text(); mScoreText->setRect(0, 0);
	mCoinText = new Text(); mCoinText->setRect(0, 50);
	mSkillText = new Text(); mSkillText->setRect(0, 550);

	for(int i = 0; i < int(EFFECT_PATHS.size()); i++) {
		EffectRender* temp = new EffectRender();
		mEffectList.push_back(temp);
	}

}

Character::~Character() {
	delete mScoreText;
	delete mCoinText;
	delete mSkillText;
	for(auto &it : mEffectList) {
		if(it) {
			delete it;
			it = nullptr;
		}
	}
	mEffectList = {};
}

void Character::handleAction(const SDL_Event &event, SDL_Renderer* renderer) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			if (mState != DESTROYED) {
				mYVal = -mNormalYVal;
			}
			break;
		case SDLK_DOWN:
			if (mState != DESTROYED) {
				mYVal = mNormalYVal;
			}
			break;
		case SDLK_RIGHT:
			if (mState != DESTROYED) {
				mXVal = mNormalXVal;
			}
			break;
		case SDLK_LEFT:
			if (mState != DESTROYED) {
				mXVal = -mNormalXVal;
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
				setCurrentState(static_cast<State>(FIRING_RED + mCurrentBullet));
				fire(renderer);
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
			break;
		case SDLK_LEFT:
		case SDLK_RIGHT:
			mXVal = 0;
			break;
		}
	}
}

void Character::handleMove() {
	if (checkToMove(10)) {
		Airplane::handleMove();
	}
	if (mRect.x <= 0 - mRect.h/2) 
		mRect.x = -mRect.h/2;
	if (mRect.x >= SCREEN_WIDTH - mRect.h/2) 
		mRect.x = SCREEN_WIDTH - mRect.h/2;
	if (mRect.y <= -mRect.h/2) 
		mRect.y = -mRect.h/2;
	if (mRect.y >= 600 - mRect.h/2) 
		mRect.y = 600 - mRect.h/2;
}

void Character::restart(SDL_Renderer* renderer) {
	Airplane::restart(renderer);
	for(auto &it : mEffectList) {
		it->mCurrentTime = 0;
	}
	mNormalXVal = mNormalYVal = 5;
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
	mCoinText->loadText(renderer, font, "Coin : " + std::to_string(mCoin), {255, 255, 255});
	mCoinText->render(renderer);
}
void Character::renderScore(SDL_Renderer* renderer, TTF_Font* font) {
	mScoreText->loadText(renderer, font, "Score : " + std::to_string(mScore), {255, 255, 255});
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
		else if (mSkillList[mCurrentSkill]->mType == SUPER_SKILL) {
			name = "super : ";
		}
		mSkillText->loadText(renderer, font, name + std::to_string(mSkillList[mCurrentSkill]->mCurrentTime));
		mSkillText->render(renderer);
	}
}

void Character::fire(SDL_Renderer* renderer) {
	for (int i = -mNormalBullet / 2; i <= mNormalBullet / 2; i++) {
		if (i == 0 && mNormalBullet % 2 == 0)
			continue;
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, mCurrentBullet);
		newBullet->setDirection(5, i);
		mBulletList.push_back(newBullet);
	}
}

void Character::loadImage(SDL_Renderer* renderer, std::vector<std::string> &path) {
	Airplane::loadImage(renderer, path);
	for(int i = 0; i < int(EFFECT_PATHS.size()); i++) {
		mEffectList[i]->mEffectImg->loadImage(renderer, EFFECT_PATHS[i]);
	}
} 


void Character::handleEffect() {
	for(int i = 0; i < int(mEffectList.size()); i++) {
		if (SDL_GetTicks64() - mEffectList[i]->mTime > 1000) {
			mEffectList[i]->mCurrentTime--;
			mEffectList[i]->mTime = SDL_GetTicks64();			
			if(mEffectList[i]->mCurrentTime <= 0) {
				mEffectList[i]->mCurrentTime = 0;
			}
		}
	}

	if(mEffectList[SPEED_DOWN_EFFECT]->mCurrentTime == 0 && mEffectList[SPEED_UP_EFFECT]->mCurrentTime == 0) {
		mNormalXVal = mNormalYVal = 5;
	}

	if(mEffectList[ARMOR_EFFECT]->mCurrentTime == 0) {
		mDef = mNormalDef;
	}	
}

void Character::useEffect(EffectType t, int time) {
	mEffectList[int(t)]->mCurrentTime = time;
	if(t == SPEED_UP_EFFECT) {
		mNormalXVal = mNormalYVal = 7;
		mEffectList[SPEED_DOWN_EFFECT]->mCurrentTime = 0;
	}
	if(t == SPEED_DOWN_EFFECT) {
		mNormalXVal = mNormalYVal = 3;
		mEffectList[SPEED_UP_EFFECT]->mCurrentTime = 0;
	}
	if(t == ARMOR_EFFECT) {
		mDef = 10;
	}
}

void Character::renderEffect(SDL_Renderer* renderer, TTF_Font* font) {
	int i = 0;
	for(auto it : mEffectList) {
		if(it->mCurrentTime != 0) {
			it->mEffectImg->setRect(1000, i*70); it->mEffectImg->render(renderer);
			it->mTimeText->setRect(1100, i * 70 + 10);
			it->mTimeText->loadText(renderer, font, std::to_string(it->mCurrentTime)); it->mTimeText->render(renderer);
			i++;
		}
	}
}