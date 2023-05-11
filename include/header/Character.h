#ifndef CHARACTER_H
#define CHARACTER_H
#include "Airplane.h"
#include "Text.h"

static std::vector<std::string> EFFECT_PATHS = {"Image_Folder/Item/Magnet_Bonus.png", "Image_Folder/Item/Speed_Bonus.png", "Image_Folder/Item/Speed_Debuff.png", "Image_Folder/Item/Armor_Bonus.png"};

enum EffectType {
	MAGNET_EFFECT,
	SPEED_UP_EFFECT,
	SPEED_DOWN_EFFECT,
	ARMOR_EFFECT,
};

class EffectRender {
public:
	Text* mTimeText = nullptr;
	BaseClass *mEffectImg = nullptr;
	int mCurrentTime = 0;
	Uint64 mTime = 0;
	EffectRender() {
		mEffectImg = new BaseClass();
		mTimeText = new Text();
	}
	~EffectRender() {
		if(mEffectImg) {
			delete mEffectImg;
			mEffectImg = nullptr;
		}
		if(mTimeText) {
			delete mTimeText; 
			mTimeText = nullptr;
		}
	}
};


class Character : public Airplane {
public:
	Character();
	~Character();
	void handleAction(const SDL_Event &event, SDL_Renderer* renderer);
	void handleMove();
	void restart(SDL_Renderer*);
	void setCoin(int c);
	int getScore();
	void setScore(int c);
	void setCurrentBullet(BulletType t);
	int getCoin();
	void renderScore(SDL_Renderer*, TTF_Font*);
	void renderSkill(SDL_Renderer*, TTF_Font*);
	void renderCoin(SDL_Renderer*, TTF_Font*);
	void loadImage(SDL_Renderer*, std::vector<std::string>&);
	void handleEffect();
	void renderEffect(SDL_Renderer*, TTF_Font*);
	void useEffect(EffectType, int =30);
	BulletType getCurrentBullet();
	std::vector<EffectRender*> mEffectList;

private:
	void fire(SDL_Renderer* renderer);
	int mCoin;
	int mScore;
	int mCurrentSkill;
	BulletType mCurrentBullet;
	Text* mScoreText;
	Text* mSkillText;
	Text* mCoinText;
};

#endif 
