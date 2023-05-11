#ifndef ITEM_H
#define ITEM_H

#include "BaseClass.h"
enum ItemType {
	RED_BULLET_ITEM,
	GREEN_BULLET_ITEM,
	BLUE_BULLET_ITEM,
	HP_ITEM,
	BULLET_ITEM,
	COIN_ITEM,
	MAGNET_ITEM,
	SPEED_UP_ITEM,
	SPEED_DOWN_ITEM,
	ARMOR_ITEM,
};

static std::vector<std::string> ITEM_PATHS = {"Image_Folder/Item/Red_Bonus.png",  "Image_Folder/Item/Green_Bonus.png" , "Image_Folder/Item/Blue_Bonus.png", "Image_Folder/Item/Hp_Bonus.png", "Image_Folder/Item/Bullet_Bonus.png", "Image_Folder/Item/Coin_Bonus.png", "Image_Folder/Item/Magnet_Bonus.png", "Image_Folder/Item/Speed_Bonus.png", "Image_Folder/Item/Speed_Debuff.png", "Image_Folder/Item/Armor_Bonus.png"};

class Item : public BaseClass {
public:
	void loadImage(SDL_Renderer*, ItemType);
	void handleMove();
	ItemType getItemType();
	Item();
	~Item();
private:
	ItemType mItemType;
};

#endif
