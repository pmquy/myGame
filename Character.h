#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Airplane.h"
#include "Text.h"


class Character : public Airplane {
public:
	Character();
	~Character();
	void handleAction(const SDL_Event &event, SDL_Renderer* renderer);
	void handleMove();
	void handleState(SDL_Renderer*);

	void renderText(SDL_Renderer* renderer, TTF_Font* font) {
		for (int i = 0; i < int(mSkillList.size()); i++) {
			if (mSkillList[i]->mIsAvailable == true) {
				Text* temp = mTextSkillList[i];
				temp->loadText(renderer, gFont, mSkillList[i]->mName + " : " + std::to_string(mSkillList[i]->mCurrentTime));
				temp->render(renderer);
			}
		}

		std::string temp;
		if (mCurrentBullet == GREEN_BALL) {
			temp = "GREEN BALL";
		}
		else if (mCurrentBullet == RED_BALL) {
			temp = "RED BALL";
		}
		else if (mCurrentBullet == BLUE_BALL) {
			temp = "BLUE BALL";
		}
		mTextSkillList.back()->loadText(renderer, gFont, temp + " : " + std::to_string(mBulletQuatity[int(mCurrentBullet)]));
		mTextSkillList.back()->render(renderer);

	}



	bool checkIsDestroyed() {
		return mHeart == 0 && mCurrentFrame == mMaxFrames[int(DESTROYED)] - 1 && mState == DESTROYED;
	}
	void reborn() {
		Airplane::reborn();
		setRect(0, 0);
		mXVal = mYVal = 0;
		mSkillList[0]->mCurrentTime = 0;
		mScore = 0;
	}
	int getCoin() {
		return mCoin;
	}
	void setCoin(int c) {
		mCoin = c;
	}
	int getScore() {
		return mScore;
	}
	void setScore(int c) {
		mScore = c;
	}
private:
	void handleBulletMove();
	int mXVal;
	int mYVal;
	int mCoin;
	int mScore;
	BulletType mCurrentBullet = BulletType::GREEN_BALL;
	std::vector<Text*> mTextSkillList;
	std::vector<int> mBulletQuatity = { 100, 100, 100 };
};

#endif 
