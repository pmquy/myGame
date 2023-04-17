#ifndef AIRPLANE_
#define AIRPLANE_

#include "BaseClass.h"
#include "Bullet.h"

static std::vector<std::string> HERO1_PATHS = { "Image_Folder/Airplane/Hero/Fighter/Idle.png", "Image_Folder/Airplane/Hero/Fighter/Destroyed.png", "Image_Folder/Airplane/Hero/Fighter/Attack_1.png","Image_Folder/Airplane/Hero/Fighter/Boost.png" };
static std::vector<std::string> HERO2_PATHS = { "Image_Folder/Airplane/Hero/Bomber/Idle.png", "Image_Folder/Airplane/Hero/Bomber/Destroyed.png", "Image_Folder/Airplane/Hero/Bomber/Attack_1.png","Image_Folder/Airplane/Hero/Bomber/Boost.png" };
static std::vector<std::string> HERO3_PATHS = { "Image_Folder/Airplane/Hero/Corvette/Idle.png", "Image_Folder/Airplane/Hero/Corvette/Destroyed.png", "Image_Folder/Airplane/Hero/Corvette/Attack_1.png","Image_Folder/Airplane/Hero/Corvette/Boost.png" };
static std::vector<std::vector<std::string>> HEROES_PATHS = { HERO1_PATHS, HERO2_PATHS, HERO3_PATHS };

static std::vector<int> PLANE_ATK = { 3, 4, 5 };
static std::vector<int> PLANE_HP = { 50, 100, 150 };
static std::vector<int> PLANE_DEF = { 1, 2, 3 };

static std::vector<std::string> BOT1_PATHS = { "Image_Folder/Airplane/Bot/Bomber/Idle.png", "Image_Folder/Airplane/Bot/Bomber/Destroyed.png", "Image_Folder/Airplane/Bot/Bomber/Attack_1.png", "Image_Folder/Airplane/Bot/Bomber/Boost.png" };
static std::vector<std::string> BOT2_PATHS = { "Image_Folder/Airplane/Bot/Fighter/Idle.png", "Image_Folder/Airplane/Bot/Fighter/Destroyed.png", "Image_Folder/Airplane/Bot/Fighter/Attack_1.png", "Image_Folder/Airplane/Bot/Fighter/Boost.png" };
static std::vector<std::string> BOT3_PATHS = { "Image_Folder/Airplane/Bot/Corvette/Idle.png", "Image_Folder/Airplane/Bot/Corvette/Destroyed.png", "Image_Folder/Airplane/Bot/Corvette/Attack_1.png" , "Image_Folder/Airplane/Bot/Corvette/Boost.png" };
static std::vector<std::vector<std::string>> BOTS_PATHS = { BOT1_PATHS, BOT2_PATHS, BOT3_PATHS };

enum State {
	NORMAL,
	DESTROYED,
	FIRING,
	BOOSTING
};

enum SkillType {
	BUFF_HP_SKILL,
	BUFF_ATK_SKILL,
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
		mIsAvailable = false;
		mTime = 0;
	}
};

class Airplane :public BaseClass {
public:
	Airplane();
	~Airplane();
	void getDamage(int damage);
	int getHp();
	int getMaxHp();
	void setHp(int Hp);
	void setMaxHp(int mh);
	int getAtk();
	void setAtk(int Atk);
	int getDef();
	void setDef(int Def);
	bool getIsAppear();
	void setIsAppear(bool t);
	std::vector<Bullet*>& getBulletList();
	std::vector<Skill*>& getSkillList();	
	virtual void handleState(SDL_Renderer*) = 0;
	virtual void handleBulletMove() = 0;
	virtual void render(SDL_Renderer* renderer, int i);
	virtual void restart();
	void free();
	void loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName);
	void handleSkill();

	friend void check(Airplane* a, Airplane* b) {
		if (b->getHp() > 0 && checkConllision(a, b)) {
			a->getDamage(a->getMaxHp() / 2);
			b->getDamage(10000);
		}
		for (int i = 0; i < int(a->getBulletList().size()); i++) {
			if (checkConllision(a->getBulletList()[i], b)) {
				b->getDamage(a->getAtk());
				a->getBulletList()[i]->setIsAppear(false);
			}
		}
		for (int i = 0; i < int(b->getBulletList().size()); i++) {
			if (checkConllision(b->getBulletList()[i], a)) {
				a->getDamage(b->getAtk());
				b->getBulletList()[i]->setIsAppear(false);
			}
		}
	}

protected:
	virtual bool checkIsDestroyed();
	void renderHp(SDL_Renderer *renderer);
	void renderBullet(SDL_Renderer *renderer);
	bool checkToNextFrame(int);
	bool checkToFire(int t);
	void useSkill(Skill*);
	std::vector<Skill*> mSkillList = {};
	std::vector<Bullet*> mBulletList = {};
	std::vector<SDL_Texture*> mTextures = {};
	std::vector<int> mMaxFrames = {};
	Uint64 mFrameTime = 0;
	Uint64 mFireTime = 0;
	State mState;
	int mCurrentFrame = 0;
	int mHp;
	int mMaxHp;
	int mAtk;
	int mMaxAtk;
	int mDef;
	int mMaxDef;
	bool mIsAppear;
};



#endif