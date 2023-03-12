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
private:
	void handleBulletMove();
	void fire(SDL_Renderer *);
	UINT64 mFireTime = 0;
};


#endif

