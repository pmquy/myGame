#ifndef  CHARATER_H_
#define CHARACTER_H_

#include "Airplane.h"
class Character : public Airplane {
public:
	Character();
	~Character();
	void handleAction(const SDL_Event &event, SDL_Renderer* renderer);
	void handleMove();
	void handleState();

	bool checkIsDestroyed() {
		return mHeart == 0 && mCurrentFrame == mMaxFrames[int(DESTROYED)] - 1 && mState == DESTROYED;
	}
	void reborn() {
		Airplane::reborn();
		setRect(0, 0);
	}

	int getCoin() {
		return mCoin;
	}
	void setCoin(int c) {
		mCoin = c;
	}

private:
	void handleBulletMove();
	int mXVal;
	int mYVal;
	int mCoin = 0;
};

#endif 
