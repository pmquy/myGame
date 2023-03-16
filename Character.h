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
