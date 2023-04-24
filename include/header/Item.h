#ifndef ITEM_H_
#define ITEM_H_

#include "BaseClass.h"
enum ItemType {
	ADD_RED_BALL,
	ADD_GREEN_BALL,
	ADD_BLUE_BALL,
	BUFF_HP,
	ADD_BULLET,
	ADD_COIN,
};

static std::vector<std::string> ITEM_PATHS = {"Image_Folder/Item/Red_Bonus.png",  "Image_Folder/Item/Green_Bonus.png" , "Image_Folder/Item/Blue_Bonus.png", "Image_Folder/Item/Hp_Bonus.png", "Image_Folder/Item/Bullet_Bonus.png", "Image_Folder/Item/Coin_Bonus.png"};

class Item : public BaseClass {
public:
	void loadImage(SDL_Renderer*, ItemType);
	void handleMove();
	ItemType getItemType();
	Item();
private:
	ItemType mItemType = BUFF_HP;
};

#endif
