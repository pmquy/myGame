#ifndef ITEM_H_
#define ITEM_H_

#include "BaseClass.h"
enum ItemType {
	BUFF_HP = 0,
	BUFF_ATK = 10,
	BUFF_DEF = 11,
	ADD_RED_BALL = 1,
	ADD_BLUE_BALL = 2,
	ADD_GREEN_BALL = 3,
};

static std::vector<std::string> ITEM_PATHS = { "Image_Folder/Item/HP_Bonus1.png", "Image_Folder/Item/Red_Bonus.png", "Image_Folder/Item/Blue_Bonus.png" , "Image_Folder/Item/Green_Bonus.png" };

class Item : public BaseClass {
public:
	void loadImage(SDL_Renderer*, ItemType);
	void handleMove();
	ItemType getItemType();
	Item();
private:
	ItemType mItemType;
};

#endif
