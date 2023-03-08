#ifndef AIRPLANE_
#define AIRPLANE_

#include "BaseClass.h"
#include "Bullet.h"

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
	virtual void handleMove() = 0;
	void render(SDL_Renderer* renderer);
	std::vector<Bullet*>& getBulletList();

protected:
	bool checkToMove();
	void renderHeart(SDL_Renderer *renderer);
	void renderBullet(SDL_Renderer *renderer);

	int mHeart = 100;
	int mAttack = 0;
	int mAmor = 0;
	UINT64 mStartTime = 0;
	std::vector<Bullet*> mBulletList;
};


#endif