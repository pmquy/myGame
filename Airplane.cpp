#include "Airplane.h"

Airplane::Airplane() {
	mHp = mMaxHp = 50;
	mDef = mMaxDef = 0;
	mAtk = mMaxAtk = 2;
	mFireTime = mFrameTime = mMoveTime = 0;
	mMaxBullet = 3;
	mState = NORMAL;
	mCurrentFrame = 0;
	mIsAppear = true;
	mDx = 50;
	mDy = 70;
	mWidth = 100;
	mHeight = 50;
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
	mTextures = {};
	mBulletList = {};
	mMaxFrames = {};
}

void Airplane::renderHp(SDL_Renderer *renderer) {
	SDL_Rect rectBg = { mRect.x, mRect.y + mRect.h - 50, mRect.w, 5 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rectBg);

	SDL_Rect rectHp = { mRect.x, mRect.y + mRect.h - 50, mHp * mRect.w / mMaxHp , 5 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &rectHp);
}

void Airplane::render(SDL_Renderer* renderer, int i) {
	mTexture = mTextures[int(mState)];
	SDL_Rect rect = { mCurrentFrame * mRect.w, 0, mRect.w, mRect.h };
	BaseClass::render(renderer, &rect);
	renderHp(renderer);
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
		if (mBulletList[i]->getIsAppear() == false) {
			mBulletList[i]->free();
			delete mBulletList[i];
			mBulletList[i] = nullptr;
			mBulletList.erase(mBulletList.begin() + i);
		}
		else if (mState != DESTROYED && mBulletList[i]->getIsMove() == true) {
			mBulletList[i]->render(renderer);
		}
	}
}

void Airplane::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	free();
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

void Airplane::restart() {

	while(!mBulletList.empty()) {
		mBulletList.back()->free();
		delete mBulletList.back();
		mBulletList.pop_back();
	}
	
	for (auto it : mSkillList) {
		it->mCurrentTime = 0;
	}

	mXVal = mYVal = 0;
	mHp = mMaxHp;
	mAtk = mMaxAtk;
	mDef = mMaxDef;
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


bool Airplane::checkToNextFrame(int t) {
	Uint64 now = SDL_GetTicks64();
	if (int(now - mFrameTime) >= t) {
		mFrameTime = now;
		return true;
	}
	return false;
}


void Airplane::getDamage(int damage) {
	if (mState != DESTROYED) {
		mHp -= damage - damage * mDef / 10;
	}
	if (mHp <= 0) {
		mHp = 0;
	}
}
int Airplane::getHp() {
	return mHp;
}
int Airplane::getMaxHp() {
	return mMaxHp;
}
void Airplane::setHp(int Hp) {
	mHp = Hp;
	if (mHp >= mMaxHp) {
		mHp = mMaxHp;
	}
	if (mHp <= 0) {
		mHp = 0;
	}
}
void Airplane::setMaxHp(int mh) {
	mMaxHp = mh;
}
void Airplane::setMaxDef(int mh) {
	mMaxDef = mh;
}
void Airplane::setMaxAtk(int mh) {
	mMaxAtk = mh;
}
int Airplane::getAtk() {
	return mAtk;
}
void Airplane::setAtk(int Atk) {
	mAtk = Atk;
}
int Airplane::getDef() {
	return mDef;
}
void Airplane::setDef(int Def) {
	mDef = Def;
}
bool Airplane::getIsAppear() {
	return mIsAppear;
}
void Airplane::setIsAppear(bool t) {
	mIsAppear = t;
}
int Airplane::getMaxDef() {
	return mMaxDef;
}
int Airplane::getMaxAtk() {
	return mMaxAtk;
}

std::vector<Bullet*>& Airplane::getBulletList() {
	return mBulletList;
}
std::vector<Skill*>& Airplane::getSkillList() {
	return mSkillList;
}
int Airplane::getMaxBullet() {
	return mMaxBullet;
}
void Airplane::setMaxBullet(int t) {
	mMaxBullet = t;
}

void Airplane::useSkill(Skill* sk) {
	if (sk->mIsAvailable && sk->mCurrentTime == 0) {
		switch (sk->mType) {
		case BUFF_HP_SKILL:
			if (mHp > 0) {
				mHp += int(0.25 * mMaxHp);
				if (mHp >= mMaxHp) {
					mHp = mMaxHp;
				}
			}
			break;
		case BUFF_ATK_SKILL:
			if (mHp > 0) {
				mAtk += 10;
			}
			break;
		case SUPER:
			if (mHp > 0) {
				mMaxBullet += 3;
			}
			break;
		}
		sk->mCurrentTime = sk->mMaxTime;
	}
}

void Airplane::handleSkill() {
	for (auto& it : mSkillList) {
		if (it->mIsAvailable) {
			if (SDL_GetTicks64() - it->mTime > 1000) {
				it->mTime = SDL_GetTicks64();
				it->mCurrentTime -= 1;
				if (it->mCurrentTime <= 0) {
					it->mCurrentTime = 0;
				}
				if (it->mCurrentTime == 15 && it->mType == BUFF_ATK_SKILL) {
					mAtk /= 10;
				}
				if (it->mCurrentTime == 15 && it->mType == SUPER) {
					mMaxBullet -= 3;
				}
			}
		}
	}
}