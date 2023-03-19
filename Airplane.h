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

	void getDamage(int damage) {
		if (mState != DESTROYED) {
			mHeart -= damage;
		}
		if (mHeart <= 0) {
			mHeart = 0;
		}
	}
	int getHeart() {
		return mHeart;
	}
	void setHeart(int heart) {
		mHeart = heart;
	}
	int getAttack() {
		return mAttack;
	}
	void setAttack(int attack) {
		mAttack = attack;
	}
	int getAmor() {
		return mAmor;
	}
	void setAmor(int amor) {
		mAmor = amor;
	}
	std::vector<Bullet*>& getBulletList() {
		return mBulletList;
	}
	

	virtual void handleState() = 0;
	virtual void handleMove() = 0;
	virtual void handleBulletMove() = 0;
	virtual void render(SDL_Renderer* renderer, int i);
	virtual void reborn();
	void free();


	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	

public:
	void renderHeart(SDL_Renderer *renderer);
	void renderBullet(SDL_Renderer *renderer);



	std::vector<Bullet*> mBulletList;
	std::vector<SDL_Texture*> mTextures;
	std::vector<int> mMaxFrames;
	
	virtual bool checkIsDestroyed();



	bool checkToMove(int);
	bool checkToNextFrame(int);
	bool checkToFire(int t);

	UINT64 mMoveTime = 0;
	UINT64 mFrameTime = 0;
	UINT64 mFireTime = 0;

	State mState;
	int mCurrentFrame = 0;

	int mHeart = 100;
	int mAttack = 2;
	int mAmor = 0;
};


#endif