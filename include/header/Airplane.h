#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "BaseClass.h"
#include "Bullet.h"
#include "Item.h"

static std::vector<std::string> HERO1_PATHS = { "Image_Folder/Airplane/Hero/Fighter/Idle.png", "Image_Folder/Airplane/Hero/Fighter/Destroyed.png", "Image_Folder/Airplane/Hero/Fighter/Attack_Red.png", "Image_Folder/Airplane/Hero/Fighter/Attack_Green.png","Image_Folder/Airplane/Hero/Fighter/Attack_Blue.png","Image_Folder/Airplane/Hero/Fighter/Boost.png" };
static std::vector<std::string> HERO2_PATHS = { "Image_Folder/Airplane/Hero/Bomber/Idle.png", "Image_Folder/Airplane/Hero/Bomber/Destroyed.png", "Image_Folder/Airplane/Hero/Bomber/Attack_Red.png", "Image_Folder/Airplane/Hero/Bomber/Attack_Green.png", "Image_Folder/Airplane/Hero/Bomber/Attack_Blue.png","Image_Folder/Airplane/Hero/Bomber/Boost.png" };
static std::vector<std::string> HERO3_PATHS = { "Image_Folder/Airplane/Hero/Corvette/Idle.png", "Image_Folder/Airplane/Hero/Corvette/Destroyed.png", "Image_Folder/Airplane/Hero/Corvette/Attack_Red.png", "Image_Folder/Airplane/Hero/Corvette/Attack_Green.png", "Image_Folder/Airplane/Hero/Corvette/Attack_Blue.png","Image_Folder/Airplane/Hero/Corvette/Boost.png" };
static std::vector<std::vector<std::string>> HEROES_PATHS = { HERO1_PATHS, HERO2_PATHS, HERO3_PATHS };

static std::vector<int> PLANE_ATK = { 3, 4, 5 };
static std::vector<int> PLANE_HP = { 50, 60, 70 };
static std::vector<int> PLANE_DEF = { 1, 2, 3 };

static std::vector<std::string> BOT1_PATHS = { "Image_Folder/Airplane/Bot/Fighter/Idle.png", "Image_Folder/Airplane/Bot/Fighter/Destroyed.png", "Image_Folder/Airplane/Bot/Fighter/Attack_Red.png", "Image_Folder/Airplane/Bot/Fighter/Attack_Green.png","Image_Folder/Airplane/Bot/Fighter/Attack_Blue.png" , "Image_Folder/Airplane/Bot/Fighter/Boost.png" };
static std::vector<std::string> BOT2_PATHS = { "Image_Folder/Airplane/Bot/Bomber/Idle.png", "Image_Folder/Airplane/Bot/Bomber/Destroyed.png", "Image_Folder/Airplane/Bot/Bomber/Attack_Red.png", "Image_Folder/Airplane/Bot/Bomber/Attack_Green.png", "Image_Folder/Airplane/Bot/Bomber/Attack_Blue.png", "Image_Folder/Airplane/Bot/Bomber/Boost.png" };
static std::vector<std::string> BOT3_PATHS = { "Image_Folder/Airplane/Bot/Corvette/Idle.png", "Image_Folder/Airplane/Bot/Corvette/Destroyed.png", "Image_Folder/Airplane/Bot/Corvette/Attack_Red.png" , "Image_Folder/Airplane/Bot/Corvette/Attack_Green.png" , "Image_Folder/Airplane/Bot/Corvette/Attack_Blue.png" , "Image_Folder/Airplane/Bot/Corvette/Boost.png" };
static std::vector<std::vector<std::string>> BOTS_PATHS = { BOT1_PATHS, BOT2_PATHS, BOT3_PATHS };

enum State {
	NORMAL,
	DESTROYED,
	FIRING_RED,
	FIRING_GREEN,
	FIRING_BLUE,
	BOOSTING
};

enum SkillType {
	BUFF_HP_SKILL,
	BUFF_ATK_SKILL,
	SUPER_SKILL,
};

struct Skill {
	int mMaxTime;
	int mCurrentTime;
	Uint64 mTime;
	SkillType mType;
	bool mIsAvailable;

	Skill(int t, SkillType tp) {
		mMaxTime = t;
		mType = tp;
		mCurrentTime = 0;
		mIsAvailable = true;
		mTime = SDL_GetTicks64();
	}
};

class Airplane :public BaseClass {
public:
	Airplane();
	~Airplane();
	void getDamage(int damage);
	int getHp();
	int getNormalHp();
	void setHp(int Hp);
	void setNormalAtk(int);
	void setNormalDef(int);
	void setNormalHp(int mh);
	int getAtk();
	int getNormalAtk();
	int getNormalDef();
	void setAtk(int Atk);
	int getDef();
	void setDef(int Def);
	bool getIsAppear();
	void setIsAppear(bool t);
	int getNormalBullet();
	void setNormalBullet(int);
	bool checkIsDestroyed();
	int getCurrentFrame();
	State getCurrentState();
	void setCurrentFrame(int );
	void setCurrentState(State);

	std::vector<Skill*>& getSkillList();	
	std::vector<Bullet*>& getBulletList();
	void handleSkill();
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	void addSkill(SkillType, int = 20);
	virtual void handleState(SDL_Renderer*);
	virtual void handleMove();
	virtual void render(SDL_Renderer* renderer);
	virtual void restart(SDL_Renderer*);
	virtual void handleBulletMove();
	friend void handleCollide(Airplane* a, Airplane* b, int , int);
protected:
	void free();
	void renderHp(SDL_Renderer *renderer);
	void renderBullet(SDL_Renderer *renderer);
	bool checkToNextFrame(int);
	bool checkToFire(int t);
	void useSkill(Skill*);
	int mNormalBullet;
	std::vector<Skill*> mSkillList = {};
	std::vector<Bullet*> mBulletList = {};
	std::vector<SDL_Texture*> mTextures = {};
	std::vector<int> mMaxFrames = {};
	bool frame; // xác định frame đầu tiên ở vị trí đầu hay cuối ảnh
	Uint64 mFrameTime = 0;
	Uint64 mFireTime = 0;
	State mState;
	int mCurrentFrame = 0;
	int mHp;
	int mNormalHp;
	int mAtk;
	int mNormalAtk;
	int mDef;
	int mNormalDef;
	int mNormalXVal;
	int mNormalYVal;
	bool mIsAppear;
};

#endif