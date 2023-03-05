#ifndef  CHARATER_H_
#define CHARACTER_H_

#include "Airplane.h"
class Character : public Airplane {
public:
	Character();
	~Character();
	void handleAction(const SDL_Event &event);
	void handleMove();
private:
	int mXVal;
	int mYVal;
};

#endif 
