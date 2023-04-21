#ifndef BOSS_H_
#define BOSS_H_
#include "Bot.h"
#include "Text.h"

class Boss : public Bot {

public:
	Boss();
	void handleMove();
	void restart(SDL_Renderer*);
	void handleSkill();
	void renderText(SDL_Renderer* renderer, TTF_Font* font);
private:
	Text* mName;
};

#endif