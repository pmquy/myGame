#include "Airplane.h"

Airplane::Airplane() {
	mStartTime = 0;
}

Airplane::~Airplane() {

}

int Airplane::getAmor() {
	return mAmor;
}

void Airplane::setAmor(int amor) {
	mAmor = amor;
}

int Airplane::getAttack() {
	return mAttack;
}

void Airplane::setAttack(int attack) {
	mAttack = attack;
}

int Airplane::getHeart() {
	return mHeart;
}

void Airplane::setHeart(int heart) {
	mHeart = heart;
}

void Airplane::getDamage(int damage) {
	mHeart -= damage;
}

void Airplane::renderHeart(SDL_Renderer *renderer) {

	SDL_Rect rectBg = { mRect.x, mRect.y + mRect.h + 10, mRect.w, 20 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rectBg);

	SDL_Rect rectHeart = { mRect.x, mRect.y + mRect.h + 10, mHeart * mRect.w / 100 , 20 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &rectHeart);
}

void Airplane::render(SDL_Renderer* renderer) {
	BaseClass::render(renderer);
	renderHeart(renderer);
}

bool Airplane::checkToMove() {
	UINT64 now = SDL_GetTicks64();
	if (now - mStartTime >= 20) {
		mStartTime = now;
		return true;
	}
	return false;
}