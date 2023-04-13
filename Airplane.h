#ifndef AIRPLANE_
#define AIRPLANE_

#include "BaseClass.h"
#include "Bullet.h"

enum State {
	NORMAL,
	DESTROYED,
	FIRING,
	BOOSTING
};

static std::vector<std::string> HERO1_PATHS = { "Image_Folder/Airplane/Hero/Fighter/Idle.png", "Image_Folder/Airplane/Hero/Fighter/Destroyed.png", "Image_Folder/Airplane/Hero/Fighter/Attack_1.png","Image_Folder/Airplane/Hero/Fighter/Boost.png" };
static std::vector<std::string> HERO2_PATHS = { "Image_Folder/Airplane/Hero/Bomber/Idle.png", "Image_Folder/Airplane/Hero/Bomber/Destroyed.png", "Image_Folder/Airplane/Hero/Bomber/Attack_1.png","Image_Folder/Airplane/Hero/Bomber/Boost.png" };
static std::vector<std::string> HERO3_PATHS = { "Image_Folder/Airplane/Hero/Corvette/Idle.png", "Image_Folder/Airplane/Hero/Corvette/Destroyed.png", "Image_Folder/Airplane/Hero/Corvette/Attack_1.png","Image_Folder/Airplane/Hero/Corvette/Boost.png" };
static std::vector<std::vector<std::string>> HEROES_PATHS = { HERO1_PATHS, HERO2_PATHS, HERO3_PATHS };

static std::vector<int> PLANE_ATTACKS = { 3, 4, 5 };
static std::vector<int> PLANE_HEARTS = { 100, 100, 100 };
static std::vector<int> PLANE_AMOR = { 0, 0, 0 };

static std::vector<std::string> BOT1_PATHS = { "Image_Folder/Airplane/Bot/Bomber/Idle.png", "Image_Folder/Airplane/Bot/Bomber/Destroyed.png", "Image_Folder/Airplane/Bot/Bomber/Attack_1.png", "Image_Folder/Airplane/Bot/Bomber/Boost.png" };
static std::vector<std::string> BOT2_PATHS = { "Image_Folder/Airplane/Bot/Fighter/Idle.png", "Image_Folder/Airplane/Bot/Fighter/Destroyed.png", "Image_Folder/Airplane/Bot/Fighter/Attack_1.png", "Image_Folder/Airplane/Bot/Fighter/Boost.png" };
static std::vector<std::string> BOT3_PATHS = { "Image_Folder/Airplane/Bot/Corvette/Idle.png", "Image_Folder/Airplane/Bot/Corvette/Destroyed.png", "Image_Folder/Airplane/Bot/Corvette/Attack_1.png" , "Image_Folder/Airplane/Bot/Corvette/Boost.png" };
static std::vector<std::vector<std::string>> BOTS_PATHS = { BOT1_PATHS, BOT2_PATHS, BOT3_PATHS };

struct Skill {
	int mMaxTime;
	int mCurrentTime;
	Uint64 mTime;
	std::string mName;
	bool mIsAvailable;

	Skill(int t, std::string name) {
		mMaxTime = t;
		mName = name;
		mCurrentTime = mMaxTime;
		mIsAvailable = false;
		mTime = 0;
	}
};

class Airplane :public BaseClass {
public:
	Airplane();
	~Airplane();

	void getDamage(int damage) {
		if (mState != DESTROYED) {
			mHeart -= damage - damage * mAmor / 10;
		}
		if (mHeart <= 0) {
			mHeart = 0;
		}
	}
	int getHeart() {
		return mHeart;
	}
	int getMaxHeart() {
		return mMaxHeart;
	}
	void setHeart(int heart) {
		mHeart = heart;
		if (mHeart >= mMaxHeart) {
			mHeart = mMaxHeart;
		}
		if (mHeart <= 0) {
			mHeart = 0;
		}
	}
	void setMaxHeart(int mh) {
		mMaxHeart = mh;
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
	bool getIsAppear() {
		return mIsAppear;
	}
	void setIsAppear(bool t) {
		mIsAppear = t;
	}

	std::vector<Bullet*>& getBulletList() {
		return mBulletList;
	}
	std::vector<Skill*>& getSkillList() {
		return mSkillList;
	}
	
	virtual void handleState(SDL_Renderer*) = 0;
	virtual void handleBulletMove() = 0;
	virtual void render(SDL_Renderer* renderer, int i);
	virtual void reborn();
	void free();
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	void handleSkill();

protected:
	void renderHeart(SDL_Renderer *renderer);
	void renderBullet(SDL_Renderer *renderer);

	std::vector<Skill*> mSkillList = {};
	std::vector<Bullet*> mBulletList = {};
	std::vector<SDL_Texture*> mTextures = {};
	std::vector<int> mMaxFrames = {};
	
	virtual bool checkIsDestroyed();
	bool checkToNextFrame(int);
	bool checkToFire(int t);

	Uint64 mFrameTime = 0;
	Uint64 mFireTime = 0;

	State mState;
	int mCurrentFrame = 0;

	int mHeart;
	int mMaxHeart;
	int mAttack;
	int mAmor;
	bool mIsAppear;
};



#endif