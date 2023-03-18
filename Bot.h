#ifndef  BOT_
#define BOT_

#include "Airplane.h"
#include "Bullet.h"

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
private:
	void handleBulletMove();
	void fire(SDL_Renderer*);
};


#endif

