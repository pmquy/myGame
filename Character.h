#ifndef  CHARATER_H_
#define CHARACTER_H_

#include "Airplane.h"
class Character : public Airplane {
public:
	Character();
	~Character();
	void handleAction(const SDL_Event &event, SDL_Renderer* renderer);
	void handleMove();
	void handleBulletMove();
private:
	int mXVal;
	int mYVal;
};

#endif 
