#ifndef AIRPLANE_
#define AIRPLANE_

#include "BaseClass.h"

class Airplane :public BaseClass {
public:
	Airplane();
	~Airplane();
	void getDamage(int damage);
	int getHeart();
	void setHeart(int heart);
	int getAttack();
	void setAttack(int attack);
	int getAmor();
	void setAmor(int amor);
	void renderHeart(SDL_Renderer *renderer);
	virtual void handleMove() = 0;
	void render(SDL_Renderer* renderer);
	bool checkToMove();
protected:
	int mHeart;
	int mAttack;
	int mAmor;
	UINT64 mStartTime = 0;
};


#endif