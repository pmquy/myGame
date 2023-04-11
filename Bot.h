#ifndef  BOT_
#define BOT_

#include "Airplane.h"
#include "Bullet.h"

enum BotType {
	SHIP1,
	SHIP2,
	SHIP3
};

class Bot : public Airplane {
public:
	Bot();
	~Bot();
	void handleMove();
	void handleState(SDL_Renderer*);
	void handleAction(SDL_Renderer *);
	
	bool checkIsDestroyed() {
		return mHeart == 0 && mCurrentFrame == 0 && mState == DESTROYED;
	}
	void reborn(SDL_Renderer*);

	void setBotType(const BotType& t) {
		mType = t;
	}

private:
	BotType mType;
	void handleBulletMove();
	void fire(SDL_Renderer*);
};


#endif

