#ifndef  BULLET_H_
#define BULLET_H_
#include "BaseClass.h"
#include <math.h>

static std::vector<std::string> mPath = { "Image_folder/Airplane/Bullet/red_ball.png", "Image_folder/Airplane/Bullet/green_ball.png", "Image_folder/Airplane/Bullet/blue_ball.png", "Image_folder/Airplane/Bullet/blue_laser.png", "Image_folder/Airplane/Bullet/red_laser.png" , "Image_folder/Airplane/Bullet/orange_laser.png" };

enum BulletType {
	RED_BALL,
	GREEN_BALL,
	BLUE_BALL,
	BLUE_LASER,
	RED_LASER,
	ORANGE_LASER
};

class Bullet : public BaseClass {
public:
	void free();
	Bullet();
	~Bullet();
	void handleMove();
	void setIsMove(bool state);
	bool getIsMove();
	bool getIsAppear() {
		return mIsAppear;
	}
	void setIsAppear(bool t) {
		mIsAppear = t;
	}
	void setDirection(int, int);
	void loadImage(SDL_Renderer*, BulletType);

private:
	bool mIsAppear;
	bool mIsMove;
	int mXVal;
	int mYVal;
};


#endif // ! BULLET_H_
