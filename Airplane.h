#ifndef AIRPLANE_
#define AIRPLANE_

#include "BaseClass.h"
#include "Bullet.h"


enum State {
	NORMAL,
	DESTROYED,
	FIRING,
};


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
	virtual void handleBulletMove() = 0;
	virtual void render(SDL_Renderer* renderer);
	std::vector<Bullet*>& getBulletList();
	void loadImage(SDL_Renderer* renderer, std::string s1, std::string s2, std::string s3);
	virtual void handleState() = 0;


protected:
	bool checkToMove();
	bool checkToMove1();
	bool checkToMove2();
	void renderHeart(SDL_Renderer *renderer);
	void renderBullet(SDL_Renderer *renderer);


	int mHeart = 100;
	int mAttack = 0;
	int mAmor = 0;
	UINT64 mStartTime = 0;
	UINT64 mStartTime1 = 0;
	UINT64 mStartTime2 = 0;

	std::vector<Bullet*> mBulletList;
	std::vector<SDL_Texture*> mTextures;
	std::vector<int> mMaxFrames;
	State mState;
	int mCurrentFrame = 0;
};


#endif