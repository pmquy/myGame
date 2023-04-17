#ifndef  BOT_
#define BOT_

#include "Airplane.h"
#include "Bullet.h"



class Bot : public Airplane {
public:
	Bot();
	~Bot();
	virtual void handleMove();
	void handleState(SDL_Renderer*);
	void handleAction(SDL_Renderer *);
	bool checkIsDestroyed();
	void restart(SDL_Renderer*);

protected:
	Uint64 mTurnTime = 0;
	bool checkToTurn(long long);
	void changeDirection();
	void handleBulletMove();
	void fire(SDL_Renderer*);
};


#endif

