#include "Airplane.h"

Airplane::Airplane() {
	mStartTime = 0;
	mHeart = 100;
	mState = State(0);
	mFrame = 20;
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
	mHeart -= damage;
	if (mHeart <= 0) {
		mHeart = 0;
		mState = DESTROYED;
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
	if (mState == NORMAL) {
		mTexture = mTextures[int(mState)];
		SDL_Rect rect = { 0,0,192, 192 };
		BaseClass::render(renderer, &rect);
		renderHeart(renderer);
		renderBullet(renderer);
	}
	else if (mState == DESTROYED) {

		mTexture = mTextures[int(mState)];
		SDL_Rect rect = { mFrame * mRect.w, 0, mRect.w, mRect.h };
		BaseClass::render(renderer, &rect);

		if (checkToMove1()) {
			mFrame--;
		}

		if (mFrame <= 0) {
			mFrame = 0;
		}

		if (mRect.x <= 20) {
			mState = NORMAL;
			mHeart = 100;
			mFrame = 20;
		}


		renderHeart(renderer);
		renderBullet(renderer);
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



void Airplane::renderBullet(SDL_Renderer* renderer) {
	for (int i = 0; i < int(mBulletList.size()); i++) {
		if (mBulletList[i]->getIsMove() == false) {
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



void Airplane::loadImage(SDL_Renderer* renderer, std::string normal, std::string destroyed) {
	SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(normal.c_str());
	SDL_Texture* temp1 = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	mTextures.push_back(temp1);
	mRect.w = loadedSurface->w;
	mRect.h = loadedSurface->h;

	loadedSurface = IMG_Load(destroyed.c_str());
	SDL_Texture* temp2 = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	mTextures.push_back(temp2);

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