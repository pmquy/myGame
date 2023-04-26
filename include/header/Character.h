#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Airplane.h"
#include "Text.h"

static std::vector<std::string> EFFECT_PATHS = {"Image_Folder/Item/Magnet_Bonus.png", "Image_Folder/Item/Speed_Bonus.png"};

enum EffectType {
	MAGNET_EFFECT,
	SPEED_UP_EFFECT,
};

struct EffectRender {
	Text* mTimeText = nullptr;
	BaseClass *mEffectImg = nullptr;
	int mCurrentTime = 0;
	Uint64 mTime = 0;
	EffectRender() {
		mEffectImg = new BaseClass();
		mTimeText = new Text();
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
	void useEffect(EffectType);
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
