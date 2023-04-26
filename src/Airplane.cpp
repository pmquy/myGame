#include "Airplane.h"

Airplane::Airplane() {
	frame = 0;
	mHp = mNormalHp = 50;
	mDef = mNormalDef = 0;
	mAtk = mNormalAtk = 2;
	mFireTime = mFrameTime = mMoveTime = 0;
	mNormalBullet = 3;
	mState = NORMAL;
	mCurrentFrame = 0;
	mIsAppear = true;
	mDx = 50;
	mDy = 70;
	mWidth = 100;
	mHeight = 50;
}

Airplane::~Airplane() {
	free();
	for(auto &it : mSkillList) {
		if(it != nullptr) {
			delete it;
			it = nullptr;
		}
	}
	mSkillList = {};
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
			delete it;
			it = nullptr;
		}
	}
	mTextures = {};
	mBulletList = {};
	mMaxFrames = {};
}

void Airplane::renderHp(SDL_Renderer *renderer) {
	// render ra vùng chứa hp
	SDL_Rect rectBg = { mRect.x, mRect.y + mRect.h - 50, mRect.w, 5 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rectBg);
	// render ra hp
	SDL_Rect rectHp = { mRect.x, mRect.y + mRect.h - 50, (mHp * mRect.w) / mNormalHp , 5 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &rectHp);
}

void Airplane::render(SDL_Renderer* renderer) {
	mTexture = mTextures[int(mState)];
	SDL_Rect rect = { mCurrentFrame * mRect.w, 0, mRect.w, mRect.h };
	BaseClass::render(renderer, &rect);
	renderHp(renderer);
	renderBullet(renderer);

	if (checkToNextFrame(100)) {
		mCurrentFrame += 1 - 2*frame;
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

void Airplane::restart(SDL_Renderer* renderer) {
	while(!mBulletList.empty()) {
		mBulletList.back()->free();
		delete mBulletList.back();
		mBulletList.pop_back();
	}
	for (auto &it : mSkillList) {
		it->mCurrentTime = 0;
	}
	setRect(0,0);
	mXVal = mYVal = 0;
	mHp = mNormalHp;
	mAtk = mNormalAtk;
	mDef = mNormalDef;
	mState = NORMAL;
	mCurrentFrame = 0;
}

void Airplane::addSkill(SkillType t, int tm) {
	mSkillList.push_back(new Skill(tm, t));
}

void Airplane::handleState(SDL_Renderer* renderer) {
	// nếu frame == true thì frame bắt đầu từ cuối và kết thúc ở đầu ảnh
	if (mHp == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = frame*(mMaxFrames[int(mState)] - 1);
	}
	if (mState == FIRING && mCurrentFrame == (1-frame)*(mMaxFrames[int(mState)] - 1)) {
		for (int i = 0; i < int(mBulletList.size()); i++) {
			if(mBulletList[i]->getIsMove() == false) {
				mBulletList[i]->setIsMove(true);
				mBulletList[i]->setRect((1-frame)*(mRect.x + mRect.w) + frame*mRect.x, mRect.y + mRect.h / 2);
			}
		}
		mState = NORMAL;
		mCurrentFrame = frame*(mMaxFrames[int(mState)] - 1);
	}
	if (mState == DESTROYED && mCurrentFrame == (1-frame)*(mMaxFrames[int(mState)] - 1)) {
		restart(renderer);
	}
	if (mState == NORMAL && (mXVal || mYVal)) {
		mState = BOOSTING;
		mCurrentFrame = frame*(mMaxFrames[int(mState)] - 1);
	}
	if (mState == BOOSTING && !mXVal && !mYVal) {
		mState = NORMAL;
		mCurrentFrame = frame*(mMaxFrames[int(mState)] - 1);
	}
}

bool Airplane::checkIsDestroyed() {
	// nếu frame == true thì frame bắt đầu từ cuối và kết thúc ở đầu ảnh
	return mState == DESTROYED && mCurrentFrame == (1-frame)*(mMaxFrames[int(mState)] - 1);
}

void Airplane::handleMove() {
	if(mState != DESTROYED) {
		BaseClass::handleMove();
		handleBulletMove();
	}
}

void Airplane::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		if (mBulletList[i]->getIsMove()) {
			mBulletList[i]->handleMove();
		}
		if(!mBulletList[i]->getIsAppear()) {
			mBulletList.erase(mBulletList.begin() + i);
		}
	}
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
	return mNormalHp;
}
void Airplane::setHp(int Hp) {
	mHp = Hp;
	if (mHp >= mNormalHp) {
		mHp = mNormalHp;
	}
	if (mHp <= 0) {
		mHp = 0;
	}
}
void Airplane::setMaxHp(int mh) {
	mNormalHp = mh;
}
void Airplane::setMaxDef(int mh) {
	mNormalDef = mh;
}
void Airplane::setMaxAtk(int mh) {
	mNormalAtk = mh;
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
	return mNormalDef;
}
int Airplane::getMaxAtk() {
	return mNormalAtk;
}
State& Airplane::getCurrentState() {
	return mState; 
}
int Airplane::getCurrentFrame() {
	return mCurrentFrame;
}
std::vector<Bullet*>& Airplane::getBulletList() {
	return mBulletList;
}
std::vector<Skill*>& Airplane::getSkillList() {
	return mSkillList;
}
int Airplane::getMaxBullet() {
	return mNormalBullet;
}
void Airplane::setMaxBullet(int t) {
	mNormalBullet = t;
}

void Airplane::useSkill(Skill* sk) {
	if (sk->mIsAvailable && sk->mCurrentTime == 0) {
		switch (sk->mType) {
		case BUFF_HP_SKILL:
			if (mHp > 0) {
				mHp += int(0.25 * mNormalHp);
				if (mHp >= mNormalHp) {
					mHp = mNormalHp;
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
				mNormalBullet += 3;
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
					mAtk -= 10;
				}
				if (it->mCurrentTime == 15 && it->mType == SUPER) {
					mNormalBullet -= 3;
				}
			}
		}
	}
}


void handleCollide(Airplane* a, Airplane* b, int hpAGet = 1000, int hpBGet = 1000) {
	if(a->getHp() <= 0 || b->getHp() <= 0) {
		return;
	}
	if (checkConllision(a, b)) {
		a->getDamage(hpAGet);
		b->getDamage(hpBGet);
	}
	for (int i = 0; i < int(a->getBulletList().size()); i++) {
		if (checkConllision(a->getBulletList()[i], b)) {
			b->getDamage(a->getAtk());
			a->getBulletList()[i]->setIsAppear(false);
		}
	}
	for (int i = 0; i < int(b->getBulletList().size()); i++) {
		if (checkConllision(b->getBulletList()[i], a)) {
			a->getDamage(b->getAtk());
			b->getBulletList()[i]->setIsAppear(false);
		}
	}
}