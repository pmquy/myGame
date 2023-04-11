#ifndef ITEM_H_
#define ITEM_H_

#include "BaseClass.h"
enum ItemType {
	BUFF_HP,
	BUFF_ATK,
	BUFF_DEF,
	ADD_RED_BALL,
	ADD_BLUE_BALL,
	ADD_GREEN_BALL,
};

static std::vector<std::string> ITEM_PATHS = { "Image_Folder/Item/HP_Bonus.png" };

class Item : public BaseClass {
public:
	void handleMove() {
		mRect.x -= 3;
	}
	
private:
	int mXVal;
	int mYVal;
	ItemType mItemType;
};

#endif
