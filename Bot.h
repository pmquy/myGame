#ifndef  BOT_
#define BOT_

#include "Airplane.h"
#include "Bullet.h"

enum ShipType {
	SHIP1,
	SHIP2,
	SHIP3
};

class Bot : public Airplane {
public:
	Bot();
	~Bot();
	void handleMove();
	void handleState();
	void handleAction(SDL_Renderer *);
	bool checkIsDestroyed() {
		return mHeart == 0 && mCurrentFrame == 0 && mState == DESTROYED;
	}
	void reborn();

	void setShipType(const ShipType& t) {
		mType = t;
	}

private:
	ShipType mType;
	void handleBulletMove();
	void fire(SDL_Renderer*);
};


#endif

