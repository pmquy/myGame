#include "Item.h"

void Item::loadImage(SDL_Renderer* renderer, ItemType t) {
	mItemType = t;
	BaseClass::loadImage(renderer, ITEM_PATHS[int(t)]);
}

void Item::handleMove() {
	if (checkToMove(10)) {
		BaseClass::handleMove();
	}
}

Item::Item() {
	mHeight = mWidth = 0;
	mXVal = -2;
	mYVal = 0;
}