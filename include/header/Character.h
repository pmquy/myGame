#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Airplane.h"
#include "Text.h"


class Character : public Airplane {
public:
	Character();
	~Character();
	void handleAction(const SDL_Event &event, SDL_Renderer* renderer);
	void handleMove();
	void handleState(SDL_Renderer*);
	bool checkIsDestroyed();
	void restart();
	void setCoin(int c);
	int getScore();
	void setScore(int c);
	void setCurrentBullet(BulletType t);
	int getCoin();
	void renderScore(SDL_Renderer*, TTF_Font*);
	void renderSkill(SDL_Renderer*, TTF_Font*);
	void renderCoin(SDL_Renderer*, TTF_Font*);
	void addSkill(SkillType);
	BulletType getCurrentBullet();

private:
	void fire(SDL_Renderer* renderer);
	void handleBulletMove();
	int mCoin;
	int mScore;
	int mCurrentSkill;
	BulletType mCurrentBullet;
	Text* mScoreText;
	Text* mSkillText;
	Text* mCoinText;
};

#endif 
