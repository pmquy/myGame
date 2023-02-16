#ifndef  CHARATER_H_
#define CHARACTER_H_

#include "BaseClass.h"
class Character : public BaseClass {
public:
	Character();
	~Character();
	void handleAction(SDL_Event event);
	void handleMove();
private:
	int mXVal;
	int mYVal;
};

#endif 
