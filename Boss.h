#ifndef BOSS_H_
#define BOSS_H_
#include "Bot.h"

class Boss : public Bot {

public:
	Boss();
	void handleMove();
	void restart(SDL_Renderer*);
	void handleSkill();
private:

};

#endif