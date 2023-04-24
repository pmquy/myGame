#include "Item.h"

void Item::loadImage(SDL_Renderer* renderer, ItemType t) {
	mItemType = t;
	BaseClass::loadImage(renderer, ITEM_PATHS[int(t)]);
}
void Item::handleMove() {
	if (checkToMove(10)) {
		BaseClass::handleMove();
	}
	if(mRect.y <= 0 || mRect.y >= SCREEN_HEIGHT) {
		mYVal = -mYVal;
	}
}
Item::Item() {
	mHeight = mWidth = 0;
	mXVal = - (1 + rand()%3);
	mYVal = 1 - rand()%5;
	mItemType = BUFF_HP;
}
ItemType Item::getItemType() {
	return mItemType;
}