#ifndef  BOT_H
#define BOT_H

#include "Airplane.h"
#include "Bullet.h"


class Bot : public Airplane {
public:
	Bot();
	~Bot();
	void handleMove();
	void handleState(SDL_Renderer*);
	void handleAction(SDL_Renderer *);
	void restart(SDL_Renderer*);

protected:
	Uint64 mTurnTime = 0;
	bool checkToTurn(long long);
	void changeDirection();
	void fire(SDL_Renderer*, BulletType);
};


#endif

