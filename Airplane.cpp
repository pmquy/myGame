#include "Airplane.h"

Airplane::Airplane() {
	mHeart = 100;
	mStartTime = 0;
	mState = NORMAL;
	mCurrentFrame = 0;
}

Airplane::~Airplane() {
	for (auto &it : mTextures) {
		SDL_DestroyTexture(it);
		it = nullptr;
	}
	free();
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

	if (mState != DESTROYED) {
		mHeart -= damage;
	}
	if (mHeart <= 0) {
		mHeart = 0;
	}
}

void Airplane::renderHeart(SDL_Renderer *renderer) {

	SDL_Rect rectBg = { mRect.x, mRect.y + mRect.h + 10, mRect.w, 5 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rectBg);
	
	SDL_Rect rectHeart = { mRect.x, mRect.y + mRect.h + 10, mHeart * mRect.w / 100 , 5 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &rectHeart);

}


void Airplane::render(SDL_Renderer* renderer, int i) {

	mTexture = mTextures[int(mState)];

	SDL_Rect rect = { mCurrentFrame * mRect.w, 0, mRect.w, mRect.h };
	BaseClass::render(renderer, &rect);

	renderHeart(renderer);
	renderBullet(renderer);

	if (checkToMove1(100)) {
		mCurrentFrame += i;
	}

	if (mCurrentFrame <= 0) {
		mCurrentFrame = 0;
	}
	if (mCurrentFrame == mMaxFrames[int(mState)]) {
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
}

bool Airplane::checkToMove(int t) {
	UINT64 now = SDL_GetTicks64();
	if (int(now - mStartTime) >= t) {
		mStartTime = now;
		return true;
	}
	return false;
}




void Airplane::renderBullet(SDL_Renderer* renderer) {
	for (int i = 0; i < int(mBulletList.size()); i++) {
		if (mBulletList[i]->getIsMove() == false) {
			mBulletList[i]->free();
			delete mBulletList[i];
			mBulletList[i] = nullptr;
			mBulletList.erase(mBulletList.begin() + i);
		}
		else if(mState != DESTROYED){
			mBulletList[i]->render(renderer);
		}
	}
}

std::vector<Bullet*>& Airplane::getBulletList() {
	return mBulletList;
}



void Airplane::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	SDL_Surface* loadedSurface = nullptr;

	for (int i = 0; i < 3; i++) {
		loadedSurface = IMG_Load(listName[i].c_str());
		SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (i == 0) {
			mRect.w = loadedSurface->w;
			mRect.h = loadedSurface->h;
		}
		mTextures.push_back(temp);
		mMaxFrames.push_back(loadedSurface->w / mRect.w);
	}

	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
}


bool Airplane::checkToMove1(int t) {
	UINT64 now = SDL_GetTicks64();
	if (int(now - mStartTime1) >= t) {
		mStartTime1 = now;
		return true;
	}
	return false;
}

void Airplane::reborn() {
	mHeart = 100;
	mState = NORMAL;
	mCurrentFrame = 0;
}



bool Airplane::checkToFire(int t) {
	if (SDL_GetTicks64() - mFireTime >= t) {
		mFireTime = SDL_GetTicks64();
		return true;
	}
	return false;
}