#ifndef  BULLET_H_
#define BULLET_H_
#include "BaseClass.h"


class Bullet : public BaseClass {
public:
	Bullet();
	~Bullet();
	void handleMove();
	void setIsMove(bool state);
	bool getIsMove();
private:
	bool mIsMove = false;
};


#endif // ! BULLET_H_
