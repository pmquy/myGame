#ifndef BOOS_
#define BOOS_
#include "Airplane.h"

class Boss :public Airplane {
public:
	Boss();
	~Boss();
	void handleMove();
	void handleState();
	void handleAction(SDL_Renderer*);
	void render(SDL_Renderer*, int);
private:
	void handleBulletMove();
	void fire(SDL_Renderer*);

	UINT64 mAppearTime = 0;
	bool checkToAppear(int t);
};

#endif