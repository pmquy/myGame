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
				Text* temp = mTextList[i];
				temp->loadText(renderer, font, mSkillList[i]->mName + " : " + std::to_string(mSkillList[i]->mCurrentTime));
				temp->render(renderer);
			}
		}

		mTextList.back()->loadText(renderer, font, BULLET_NAMES[int(mCurrentBullet)] + " : " + std::to_string(mBulletQuatity[int(mCurrentBullet)]));
		mTextList.back()->render(renderer);
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
		mBulletQuatity = { 100, 100, 100 };
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
	int mCoin;
	int mScore;
	BulletType mCurrentBullet = BulletType::GREEN_BALL;
	std::vector<Text*> mTextList;
	std::vector<int> mBulletQuatity = { 100, 100, 100 };
};

#endif 
