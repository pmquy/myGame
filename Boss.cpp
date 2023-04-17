#include "Boss.h"

Boss::Boss() {
	mHeart = mMaxHeart = 100;
	mTurnTime = 0;
	mIsAppear = false;
	mXVal = -2;
	mAttack = 5;
	mRect.x = SCREEN_WIDTH;
	mRect.y = rand() % 400;

	Skill* newSkill = new Skill(10, SkillType::BUFF_HP_SKILL);
	newSkill->mIsAvailable = true;
	mSkillList.push_back(newSkill);
}


void Boss::handleMove() {
	Bot::handleMove();
	if (mRect.x <= 500) {
		mRect.x = 500;
	}
}

void Boss::restart(SDL_Renderer* renderer) {
	Bot::restart(renderer);
	mIsAppear = false;
	mXVal = mYVal = 0;
}


void Boss::handleSkill() {
	Airplane::handleSkill();

	for (auto it : mSkillList) {
		useSkill(it);
	}
}

