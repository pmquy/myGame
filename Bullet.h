#ifndef  BULLET_H_
#define BULLET_H_
#include "BaseClass.h"

enum BulletType {
	XUOI,
	NGUOC,
	CHEOLEN,
	CHEOXUONG,
	XOAY
};

class Bullet : public BaseClass {
public:
	void free();
	Bullet();
	~Bullet();
	void handleMove();
	void setIsMove(bool state);
	bool getIsMove();
	BulletType getBulletType();
	void setBulletType(const BulletType&);
	
	bool mIsAppear = true;
private:
	bool mIsMove = true;
	BulletType mBulletType;
};


#endif // ! BULLET_H_
