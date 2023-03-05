#ifndef  BOT_
#define BOT_

#include "Airplane.h"
#include "Bullet.h"

class Bot : public Airplane {
public:
	Bot();
	~Bot();
	void handleMove();
private:
	Bullet *mBullet = nullptr;
};


#endif

