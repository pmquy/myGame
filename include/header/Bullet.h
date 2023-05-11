#ifndef  BULLET_H
#define BULLET_H
#include "BaseClass.h"

static std::vector<std::string> BULLET_PATHS = { "Image_folder/Airplane/Bullet/red_ball.png", "Image_folder/Airplane/Bullet/green_ball.png", "Image_folder/Airplane/Bullet/blue_ball.png"};
static std::vector<std::string> BULLET_NAMES = { "RED BALL", "GREEN BALL" , "BLUE BALL", };
static std::vector<int> BULLET_ATTACKS = { 0, 0, 0};

enum BulletType {
	RED_BALL,
	GREEN_BALL,
	BLUE_BALL,
};

class Bullet : public BaseClass {
public:
	Bullet();
	~Bullet();
	void handleMove();
	void setIsMove(bool state);
	bool getIsMove();
	bool getIsAppear();
	void setIsAppear(bool t);
	void setDirection(int, int);
	void loadImage(SDL_Renderer*, BulletType);
private:
	bool mIsAppear;
	bool mIsMove;
	int mXVal;
	int mYVal;
	int mAttack = 0;
	BulletType mBulletType;
};


#endif // ! BULLET_H_
