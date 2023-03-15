#ifndef  BULLET_H_
#define BULLET_H_
#include "BaseClass.h"

enum Type {
	XUOI,
	NGUOC,
	CHEOLEN,
	CHEOXUONG
};

class Bullet : public BaseClass {
public:
	
	Bullet();
	~Bullet();
	void handleMove();
	void setIsMove(bool state);
	bool getIsMove();
	Type getType();
	void setType(const Type&);
	
private:
	bool mIsMove = false;
	Type mType;
};


#endif // ! BULLET_H_
