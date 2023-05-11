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
	SDL_Rect rect;
	if(!frame) {
		rect = { mCurrentFrame * mRect.w, 0, mRect.w, mRect.h };
	}
	else {
		rect = { (mMaxFrames[mState] - 1 - mCurrentFrame) * mRect.w, 0, mRect.w, mRect.h };
	}
	BaseClass::render(renderer, &rect);
	renderHp(renderer);
	renderBullet(renderer);

	if (checkToNextFrame(100) && mCurrentFrame < mMaxFrames[mState]) {
		mCurrentFrame++;
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
	SDL_Surface* loadedSurface;
	for (int i = 0; i < int(listName.size()); i++) {
		loadedSurface = IMG_Load(listName[i].c_str());
		SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (i == 0) {
			mRect.w = loadedSurface->w;
			mRect.h = loadedSurface->h;
		}
		mTextures.push_back(temp);
		mMaxFrames.push_back(loadedSurface->w / mRect.w);
		SDL_FreeSurface(loadedSurface);
	}
	loadedSurface = nullptr;
}

void Airplane::restart(SDL_Renderer* renderer) {
	for(auto &it : mBulletList) {
		if(it) {
			delete it;
			it = nullptr;
		}
	}
	mBulletList = {};
	
	for (auto &it : mSkillList) {
		it->mCurrentTime = 0;
	}

	setRect(0,0);
	mXVal = mYVal = 0;
	mHp = mNormalHp;
	mAtk = mNormalAtk;
	mDef = mNormalDef;
	setCurrentState(NORMAL);
}

void Airplane::addSkill(SkillType t, int tm) {
	mSkillList.push_back(new Skill(tm, t));
}

void Airplane::handleState(SDL_Renderer* renderer) {
	if (mHp == 0 && mState != DESTROYED) {
		setCurrentState(DESTROYED);
	}
	if (mState >= FIRING_RED && mState <= FIRING_BLUE && mCurrentFrame == mMaxFrames[int(mState)]) {
		for (int i = 0; i < int(mBulletList.size()); i++) {
			if(mBulletList[i]->getIsMove() == false) {
				mBulletList[i]->setIsMove(true);
				mBulletList[i]->setRect((1-frame)*(mRect.x + mRect.w) + frame*mRect.x, mRect.y + mRect.h / 2);
			}
		}
		setCurrentState(NORMAL);
	}
	
	if (mState == NORMAL && (mXVal || mYVal)) {
		setCurrentState(BOOSTING);
	}
	if (mState == BOOSTING && !mXVal && !mYVal) {
		setCurrentState(NORMAL);
	}
	if((mState == NORMAL || mState == BOOSTING) && mCurrentFrame == mMaxFrames[mState]) {
		mCurrentFrame = 0;
	}
}

bool Airplane::checkIsDestroyed() {
	// nếu frame == true thì frame bắt đầu từ cuối và kết thúc ở đầu ảnh
	return mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)];
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
			delete mBulletList[i];
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
int Airplane::getNormalHp() {
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
void Airplane::setNormalHp(int mh) {
	mNormalHp = mh;
}
void Airplane::setNormalDef(int mh) {
	mNormalDef = mh;
}
void Airplane::setNormalAtk(int mh) {
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
int Airplane::getNormalDef() {
	return mNormalDef;
}
int Airplane::getNormalAtk() {
	return mNormalAtk;
}
void Airplane::setCurrentState(State t) {
	mState = t;
	mCurrentFrame = 0;
}
State Airplane::getCurrentState() {
	return mState; 
}
int Airplane::getCurrentFrame() {
	return mCurrentFrame;
}
void Airplane::setCurrentFrame(int t) {
	mCurrentFrame = t;
}
std::vector<Bullet*>& Airplane::getBulletList() {
	return mBulletList;
}
std::vector<Skill*>& Airplane::getSkillList() {
	return mSkillList;
}
int Airplane::getNormalBullet() {
	return mNormalBullet;
}
void Airplane::setNormalBullet(int t) {
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
		case SUPER_SKILL:
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
				if (it->mCurrentTime == 15 && it->mType == SUPER_SKILL) {
					mNormalBullet -= 3;
					if(mNormalBullet < 1) 
						mNormalBullet = 1;
				}
			}
		}
	}
}


void handleCollide(Airplane* a, Airplane* b, int dmgAGet = 1000, int dmgBGet = 1000) {
	if(a->getHp() <= 0 || b->getHp() <= 0) {
		return;
	}
	if (checkCollision(a, b)) {
		a->getDamage(dmgAGet);
		b->getDamage(dmgBGet);
	}
	for (int i = 0; i < int(a->getBulletList().size()); i++) {
		if (checkCollision(a->getBulletList()[i], b)) {
			b->getDamage(a->getAtk());
			a->getBulletList()[i]->setIsAppear(false);
		}
	}
	for (int i = 0; i < int(b->getBulletList().size()); i++) {
		if (checkCollision(b->getBulletList()[i], a)) {
			a->getDamage(b->getAtk());
			b->getBulletList()[i]->setIsAppear(false);
		}
	}
}