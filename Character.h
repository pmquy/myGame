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
	void renderText(SDL_Renderer* renderer, TTF_Font* font);
	bool checkIsDestroyed();
	void reborn();
	void setCoin(int c);
	int getScore();
	void setScore(int c);
	BulletType getCurrentBullet();
	void setCurrentBullet(BulletType t);
	int getCoin();
	int mMaxBullet = 1;

private:
	void handleBulletMove();
	int mCoin;
	int mScore;
	BulletType mCurrentBullet = BulletType::GREEN_BALL;
	std::vector<Text*> mTextList;
	std::vector<int> mBulletQuatity = { 100, 100, 100 };
};

#endif 
