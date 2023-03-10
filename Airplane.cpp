#include "Airplane.h"

Airplane::Airplane() {
	mStartTime = 0;
	mHeart = 100;
	mState = NORMAL;
	mCurrentFrame = 0;
}

Airplane::~Airplane() {
	for (auto &it : mTextures) {
		SDL_DestroyTexture(it);
		it = nullptr;
	}
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

	if (mHeart <= 0 && mState != DESTROYED) {
		mHeart = 0;
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
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


void Airplane::render(SDL_Renderer* renderer) {

	mTexture = mTextures[int(mState)];

	SDL_Rect rect = { mCurrentFrame * mRect.w, 0, mRect.w, mRect.h };
	BaseClass::render(renderer, &rect);

	renderHeart(renderer);
	renderBullet(renderer);

	if (checkToMove1()) {
		mCurrentFrame--;
	}

	if (mCurrentFrame <= 0) {
		mCurrentFrame = 0;
	}
}

bool Airplane::checkToMove() {
	UINT64 now = SDL_GetTicks64();
	if (int(now - mStartTime) >= 20) {
		mStartTime = now;
		return true;
	}
	return false;
}

bool Airplane::checkToMove2() {
	UINT64 now2 = SDL_GetTicks64();
	if (int(now2 - mStartTime2) >= 5000) {
		mStartTime = now2;
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
		else {
			
			mBulletList[i]->render(renderer);
			
		}
	}
}

std::vector<Bullet*>& Airplane::getBulletList() {
	return mBulletList;
}



void Airplane::loadImage(SDL_Renderer* renderer, std::string s1, std::string s2, std::string s3) {
	SDL_Surface* loadedSurface = nullptr;
	std::string s;

	for (int i = 1; i <= 3; i++) {
		if (i == 1) {
			s = s1;
		}
		else if (i == 2) {
			s = s2;
		}
		else if (i == 3) {
			s = s3;
		}
		loadedSurface = IMG_Load(s.c_str());
		SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (i == 1) {
			mRect.w = loadedSurface->w;
			mRect.h = loadedSurface->h;
		}

		mTextures.push_back(temp);
		mMaxFrames.push_back(loadedSurface->w / mRect.w);
	}

	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
}


bool Airplane::checkToMove1() {
	UINT64 now = SDL_GetTicks64();
	if (int(now - mStartTime1) >= 100) {
		mStartTime1 = now;
		return true;
	}
	return false;
}


void Airplane::reborn() {
	mState = NORMAL;
	mCurrentFrame = mMaxFrames[int(NORMAL)]-1;
	mHeart = 100;
}