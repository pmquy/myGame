#include "Airplane.h"

Airplane::Airplane() {
	mMaxHeart = 100;
	mHeart = 100;
	mAmor = 0;
	mAttack = 2;
	mFireTime = mFrameTime = mMoveTime = 0;
	mState = NORMAL;
	mCurrentFrame = 0;
}

Airplane::~Airplane() {
	BaseClass::free();
	free();
}


void Airplane::free() {
	for (auto& it : mTextures) {
		if (it != nullptr) {
			SDL_DestroyTexture(it);
			it = nullptr;
		}
	}
	for (auto& it : mBulletList) {
		if (it != nullptr) {
			it->free();
			delete it;
			it = nullptr;
		}
	}
}



void Airplane::renderHeart(SDL_Renderer *renderer) {
	SDL_Rect rectBg = { mRect.x, mRect.y + mRect.h - 50, mRect.w, 5 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rectBg);

	SDL_Rect rectHeart = { mRect.x, mRect.y + mRect.h - 50, mHeart * mRect.w / mMaxHeart , 5 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &rectHeart);
}


void Airplane::render(SDL_Renderer* renderer, int i) {
	mTexture = mTextures[int(mState)];
	SDL_Rect rect = { mCurrentFrame * mRect.w, 0, mRect.w, mRect.h };
	BaseClass::render(renderer, &rect);
	renderHeart(renderer);
	renderBullet(renderer);

	if (checkToNextFrame(100)) {
		mCurrentFrame += i;
	}
	if (mCurrentFrame <= 0) {
		mCurrentFrame = 0;
	}
	if (mCurrentFrame == mMaxFrames[int(mState)]) {
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}
}



void Airplane::renderBullet(SDL_Renderer* renderer) {
	for (int i = 0; i < int(mBulletList.size()); i++) {
		if (mBulletList[i]->getIsMove() == false) {
			mBulletList[i]->free();
			delete mBulletList[i];
			mBulletList[i] = nullptr;
			mBulletList.erase(mBulletList.begin() + i);
		}
		else if (mState != DESTROYED && mBulletList[i]->mIsAppear == true) {
			mBulletList[i]->render(renderer);
		}
	}
}


void Airplane::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	for (int i = mTextures.size() - 1; i >= 0 ; i--) {
		if (mTextures[i] != nullptr) {
			SDL_DestroyTexture(mTextures[i]);
			mTextures[i] = nullptr;
		}
		mTextures.pop_back();
		mMaxFrames.pop_back();
	}

	SDL_Surface* loadedSurface = nullptr;
	for (int i = 0; i < int(listName.size()); i++) {
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



void Airplane::reborn() {

	while(!mBulletList.empty()) {
		mBulletList[0]->free();
		delete mBulletList[0];
		mBulletList[0] = nullptr;
		mBulletList.erase(mBulletList.begin());
	}

	mHeart = mMaxHeart;
	mState = NORMAL;
	mCurrentFrame = 0;
}



bool Airplane::checkIsDestroyed() {
	return mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)] - 1;
}




bool Airplane::checkToFire(int t) {
	if (SDL_GetTicks64() - mFireTime >= t) {
		mFireTime = SDL_GetTicks64();
		return true;
	}
	return false;
}

bool Airplane::checkToMove(int t) {
	UINT64 now = SDL_GetTicks64();
	if (int(now - mMoveTime) >= t) {
		mMoveTime = now;
		return true;
	}
	return false;
}

bool Airplane::checkToNextFrame(int t) {
	UINT64 now = SDL_GetTicks64();
	if (int(now - mFrameTime) >= t) {
		mFrameTime = now;
		return true;
	}
	return false;
}