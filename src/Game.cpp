#include "Game.h"
Game::Game() {
	mRect.x = mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = SCREEN_HEIGHT;
	mXVal = -1; mYVal = 0;
	mState = HOME;
	color = { 255, 255, 255 };
}

Game::~Game() {
	if (hero != nullptr) {
		delete hero;
		hero = nullptr;
	}
	for (int i = 0; i < int(bots.size()); i++) {
		if (bots[i] != nullptr) {
			delete bots[i];
			bots[i] = nullptr;
		}
	}
	bots = {};
	for (auto& it : mTextures) {
		if (it != nullptr) {
			SDL_DestroyTexture(it);
			it = nullptr;
		}
	}
	mTextures = {};
}

void Game::handleMove() {
	if (mState >= LEVEL1 && mState <= LEVEL5 && checkToMove(20)) {
		BaseClass::handleMove();
		if (mRect.x <= -1200) mRect.x = 0;
	}
	if (mState == HOME2 && checkToMove(10)) {
		BaseClass::handleMove();
	}
}

void Game::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	if (mState != HOME2) {
		mTexture = mTextures[int(mState)];
	}
	if (mState >= LEVEL1 && mState <= LEVEL5) {
		BaseClass::render(renderer);
		mRect.x += SCREEN_WIDTH;
		BaseClass::render(renderer);
		mRect.x -= SCREEN_WIDTH;
		mLevelText->render(renderer);

		
	}
	else if (mState == HOME2) {
		SDL_Rect oldRect = mRect;
		mTexture = mTextures[int(START)];
		setRect(0, 0);
		BaseClass::render(renderer);
		setRect(oldRect.x, oldRect.y);
		mTexture = mTextures[int(HOME)];
		BaseClass::render(renderer);
	}
	else {
		BaseClass::render(renderer);
	}

	if (mState >= UPGRADE && mState <= UPGRADE4) {
		SDL_Rect rectBg = { 320, 140, 600, 10 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_Rect rect = { 320, 140, (hero->getMaxHp() - 50) * 100 / 10 , 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 230, (hero->getMaxDef() - 0) * 100 / 1, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 320, (hero->getMaxAtk() - 20) * 100 / 2, 10 };
		SDL_RenderFillRect(renderer, &rect);
		hero->renderCoin(renderer, font);
	}
	
	if (mState >= SHOP && mState <= SHOP9) {
		hero->renderCoin(renderer, font);
	}	
}

void Game::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	SDL_Texture* loadedTexture;
	for (std::string s : listName) {
		loadedTexture = loadTexture(renderer, s);
		mTextures.push_back(loadedTexture);
	}
}

void Game::handleState(SDL_Renderer* renderer, SDL_Event event) {
	
	switch (mState) {
	case LEVEL1:
	case LEVEL2:
	case LEVEL3:
	case LEVEL4:
	case LEVEL5:
		if (hero->checkIsDestroyed()) {
			mState = LOSE;
			setRect(0, 0);
			Mix_PlayChannel(-1, mGameOverMusic, 0);
			Mix_PlayMusic(mHomeMusic, -1);
		}
		else {
			
			if (boss->checkIsDestroyed() && hero->getRect().x >= SCREEN_WIDTH - hero->getRect().w/2) {
				mState = WIN;
				setRect(0, 0);
				Mix_PlayMusic(mHomeMusic, -1);
				Mix_PlayChannel(-1, mWinMusic, 0);
			}
			if(!boss->checkIsDestroyed() && !hero->checkIsDestroyed()) {
				hero->handleAction(event, renderer);
			}
		}
		break;

	case HOME:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
			case SDLK_UP:
			case SDLK_LEFT:
			case SDLK_RIGHT:
				mState = HOME1;
				break;
			}
		}
		break;

	case HOME1:

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			mState = HOME2;
			Mix_PlayMusic(mIntroMusic, -1);
			mYVal = -1; mXVal = 0;
		}
		break;

	case HOME2:
		if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) || mRect.y <= -SCREEN_HEIGHT) {
			setRect(0, 0);
			mState = START;
			Mix_PlayMusic(mHomeMusic, -1);
			mXVal = -1; mYVal = 0;
		}
		break;

	case START1:

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = START2;
				break;
			case SDLK_UP:
				mState = START3;
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				setUpLevel(renderer, mLevel);
				Mix_PlayMusic(mGameMusic, -1);
				break;
			}
		}

		break;

	case START2:

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = START3;
				break;
			case SDLK_UP:
				mState = START1;
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				mState = SHOP;
				break;
			}
		}
		break;

	case START3:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = START1;
				break;
			case SDLK_UP:
				mState = START2;
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				mState = UPGRADE;
				break;
			}
		}
		break;

	case START:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = START1;
				break;
			case SDLK_UP:
				mState = START3;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			}
		}
		break;

	case LOSE1:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = LOSE2;
				break;
			case SDLK_UP:
				mState = LOSE2;
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				mLevel = 1;
				setUpLevel(renderer, mLevel);
				hero->setScore(0);
				break;
			}
		}
		break;

	case LOSE2:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = LOSE1;
				break;
			case SDLK_UP:
				mState = LOSE1;
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				hero->setScore(0);
				mState = START;
				break;
			}
		}
		break;

	case LOSE:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = LOSE1;
				break;
			case SDLK_UP:
				mState = LOSE2;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			}
		}
		break;

	case SHOP1:

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP4;
				break;
			case SDLK_UP:
				mState = SHOP4;
				break;
			case SDLK_LEFT:
				mState = SHOP5;
				break;
			case SDLK_RIGHT:
				mState = SHOP2;
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 50) {
					hero->setCoin(hero->getCoin() - 50);
					hero->loadImage(renderer, HERO1_PATHS);
				}
				break;
			}
		}
		break;

	case SHOP2:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP4;
				break;
			case SDLK_UP:
				mState = SHOP4;
				break;
			case SDLK_LEFT:
				mState = SHOP1;
				break;
			case SDLK_RIGHT:
				mState = SHOP3;
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 50) {
					hero->setCoin(hero->getCoin() - 50);
					hero->loadImage(renderer, HERO3_PATHS);
				}
				break;
			}
		}
		break;
	case SHOP3:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP4;
				break;
			case SDLK_UP:
				mState = SHOP4;
				break;
			case SDLK_LEFT:
				mState = SHOP2;
				break;
			case SDLK_RIGHT:
				mState = SHOP5;
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 50) {
					hero->setCoin(hero->getCoin() - 50);
					hero->loadImage(renderer, HERO2_PATHS);
				}
				break;
			}
		}
		break;
	case SHOP4:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP2;
				break;
			case SDLK_UP:
				mState = SHOP2;
				break;
			case SDLK_LEFT:
				mState = SHOP1;
				break;
			case SDLK_RIGHT:
				mState = SHOP3;
				break;
			case SDLK_RETURN:
				mState = START;
				break;
			}
		}
		break;

	case SHOP:

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP2;
				break;
			case SDLK_UP:
				mState = SHOP4;
				break;
			case SDLK_LEFT:
				mState = SHOP1;
				break;
			case SDLK_RIGHT:
				mState = SHOP3;
				break;
			}
		}
		break;

	case SHOP6:

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP7;
				break;
			case SDLK_UP:
				mState = SHOP9;
				break;
			case SDLK_LEFT:
				mState = SHOP;
				break;
			case SDLK_RIGHT:
				mState = SHOP;
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 20) {
					hero->setCoin(hero->getCoin() - 20);
					hero->addSkill(BUFF_HP_SKILL);
				}
				break;
			}
		}
		break;

	case SHOP7:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP8;
				break;
			case SDLK_UP:
				mState = SHOP6;
				break;
			case SDLK_LEFT:
				mState = SHOP;
				break;
			case SDLK_RIGHT:
				mState = SHOP;
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 20) {
					hero->setCoin(hero->getCoin() - 20);
					hero->addSkill(BUFF_ATK_SKILL);
				}
				break;
			}
		}
		break;

	case SHOP8:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP9;
				break;
			case SDLK_UP:
				mState = SHOP7;
				break;
			case SDLK_LEFT:
				mState = SHOP;
				break;
			case SDLK_RIGHT:
				mState = SHOP;
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 20) {
					hero->setCoin(hero->getCoin() - 20);
					hero->addSkill(SUPER);
				}
				break;
			}
		}
		break;

	case SHOP9:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP6;
				break;
			case SDLK_UP:
				mState = SHOP8;
				break;
			case SDLK_LEFT:
				mState = SHOP;
				break;
			case SDLK_RIGHT:
				mState = SHOP;
				break;
			case SDLK_RETURN:
				mState = START;
				break;
			}
		}
		break;

	case SHOP5:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = SHOP6;
				break;
			case SDLK_UP:
				mState = SHOP9;
				break;
			case SDLK_LEFT:
				mState = SHOP;
				break;
			case SDLK_RIGHT:
				mState = SHOP;
				break;
			}
		}
		break;

	case WIN1:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = WIN2;
				break;
			case SDLK_UP:
				mState = WIN3;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				mLevel++;
				setUpLevel(renderer, mLevel);
				Mix_PlayMusic(mGameMusic, -1);
				break;
			}
		}
		break;

	case WIN2:
		if (event.type == SDL_MOUSEBUTTONUP) {

		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = WIN3;
				break;
			case SDLK_UP:
				mState = WIN1;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				setUpLevel(renderer, mLevel);
				Mix_PlayMusic(mGameMusic, -1);
				break;
			}
		}
		break;
	case WIN3:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = WIN1;
				break;
			case SDLK_UP:
				mState = WIN2;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				hero->setScore(0);
				mState = START;
				break;
			}
		}
		break;

	case WIN:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = WIN1;
				break;
			case SDLK_UP:
				mState = WIN3;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			}
		}
		break;
	case UPGRADE1:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = UPGRADE2;
				break;
			case SDLK_UP:
				mState = UPGRADE4;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 20 && hero->getMaxHp() < 110) {
					hero->setCoin(hero->getCoin() - 20);
					hero->setMaxHp(hero->getMaxHp() + 20);
				}
				break;
			}
		}
		break;

	case UPGRADE2:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = UPGRADE3;
				break;
			case SDLK_UP:
				mState = UPGRADE1;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 20 && hero->getDef() < 6) {
					hero->setCoin(hero->getCoin() - 20);
					hero->setMaxDef(hero->getMaxDef() + 1);
				}
				break;
			}
		}
		break;

	case UPGRADE3:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = UPGRADE4;
				break;
			case SDLK_UP:
				mState = UPGRADE2;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				if (hero->getCoin() >= 20 && hero->getMaxAtk() < 20 + 12) {
					hero->setCoin(hero->getCoin() - 20);
					hero->setMaxAtk(hero->getMaxAtk() + 2);
				}
				break;
			}
		}

		break;

	case UPGRADE4:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = UPGRADE1;
				break;
			case SDLK_UP:
				mState = UPGRADE3;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				mState = START;
				break;
			}
		}
		break;

	case UPGRADE:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				mState = UPGRADE1;
				break;
			case SDLK_UP:
				mState = UPGRADE4;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			}
		}
		break;
	}
}



void Game::loadResource(SDL_Renderer* renderer) {
	
	this->loadImage(renderer, GAME_PATHS);
	hero = new Character(); hero->loadImage(renderer, HERO1_PATHS);
	boss = new Boss(); boss->loadImage(renderer, BOTS_PATHS[rand() % 3]);

	for (int i = 0; i < 10; i++) {
		Bot* newBot = new Bot();
		newBot->loadImage(renderer, BOTS_PATHS[rand() % 3]);
		bots.push_back(newBot);
	}

	mGameMusic = Mix_LoadMUS("Music_Folder/music.mp3");
	mHomeMusic = Mix_LoadMUS("Music_Folder/home.mp3");
	mIntroMusic = Mix_LoadMUS("Music_Folder/intro.mp3");
	mBonkMusic = Mix_LoadWAV("Music_Folder/bonk.wav");
	mItemMusic = Mix_LoadWAV("Music_Folder/item.wav");
	mWinMusic = Mix_LoadWAV("Music_Folder/win.wav");
	mGameOverMusic = Mix_LoadWAV("Music_Folder/game_over.wav");;

	font = TTF_OpenFont("Font_Folder/font2.ttf", 30);
	mLevelText = new Text(); mLevelText->setRect(500, 0);
	mLevel = 1;
	mState = GameState::HOME;
}


void Game::updateObject(SDL_Renderer* renderer) {
	if(hero->checkIsDestroyed()) {
		return;
	}

	if(boss->checkIsDestroyed()) {
		hero->mXVal = 5; hero->mYVal = 0; hero->handleMove();
		hero->render(renderer); hero->renderCoin(renderer, font); hero->renderScore(renderer, font);
		return;
	}

	hero->handleMove(); hero->handleState(renderer); hero->handleSkill(); hero->handleEffect(); 
	hero->render(renderer);hero->renderCoin(renderer, font); hero->renderScore(renderer, font); hero->renderSkill(renderer, font); hero->renderEffect(renderer, font);
	this->handleEffect();

	for (int i = 0; i < int(bots.size()); i++) {
		if (bots[i]->getIsAppear()) {
			bots[i]->handleAction(renderer); bots[i]->handleMove(); bots[i]->handleState(renderer); bots[i]->render(renderer); bots[i]->handleSkill();
		}
	}

	if (boss->getIsAppear()) {
		boss->handleAction(renderer); boss->handleMove(); boss->handleState(renderer); boss->render(renderer); boss->handleSkill();
		boss->renderText(renderer, font);
	}

	if(!boss->getIsAppear() && (SDL_GetTicks64() - mBossTime > 10000)) {
		boss->setIsAppear(true);
	}

	for (int i = 0; i < int(items.size()); i++) {
		items[i]->handleMove(); items[i]->render(renderer);
		if (items[i]->getRect().x <= 0) {
			delete items[i];
			items.erase(items.begin() + i);
		}
	}
	this->handleCollision(renderer);
}

void Game::handleCollision(SDL_Renderer* renderer) {
	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {
			handleCollide(hero, bots[j], hero->getMaxHp()/2, bots[j]->getMaxHp());

			if (bots[j]->checkIsDestroyed() && bots[j]->getIsAppear()) {
				hero->setScore(hero->getScore() + 2);
				Mix_PlayChannel(-1, mBonkMusic, 0);

				Item* newItem = new Item();
				newItem->loadImage(renderer, static_cast<ItemType>(rand() % int(ITEM_PATHS.size())));
				newItem->setRect(bots[j]->getRect().x + 10, bots[j]->getRect().y + bots[j]->getRect().h / 2);
				items.push_back(newItem);
				
				int temp = 1 + rand()%3;
				for(int i = 0; i < temp; i++) {
					newItem = new Item();
					newItem->loadImage(renderer, ADD_COIN);
					newItem->setRect(bots[j]->getRect().x + 10, bots[j]->getRect().y + bots[j]->getRect().h / 2);
					items.push_back(newItem);
				}
			}
		}
	}

	if (boss->getIsAppear()) {
		handleCollide(hero, boss, hero->getMaxHp(), 0);
		if (boss->checkIsDestroyed()) {
			hero->setScore(hero->getScore() + 10);
			hero->setScore(hero->getCoin() + 5);
		}
	}

	for (int i = 0; i < int(items.size()); i++) {
		if(items[i]->getRect().x < 0) {
			if(items[i] != nullptr) {
				delete items[i];
				items.erase(items.begin() + i);
			}
		}
		else if (hero->getHp() > 0 && checkConllision(hero, items[i])) {
			Mix_PlayChannel(-1, mItemMusic, 0);
			switch (items[i]->getItemType()) {
			case BUFF_HP:
				hero->setHp(hero->getHp() + 10);
				break;

			case ADD_BULLET:
				if (hero->getMaxBullet() < 5) {
					hero->setMaxBullet(hero->getMaxBullet() + 1);
				}
				break;

			case ADD_BLUE_BALL:
			case ADD_GREEN_BALL:
			case ADD_RED_BALL:
				if (int(hero->getCurrentBullet()) == int(items[i]->getItemType())) {
					hero->setMaxBullet(hero->getMaxBullet() + 1);
					if (hero->getMaxBullet() >= 5) {
						hero->setMaxBullet(5);
					}
				}
				else {
					hero->setCurrentBullet(static_cast<BulletType>(items[i]->getItemType()));
					hero->setMaxBullet(1);
				}
				break;

			case ADD_COIN:
				hero->setCoin(hero->getCoin() + 1);				
				break;
			
			case ADD_MAGNET:
				hero->useEffect(MAGNET_EFFECT);
				break;
			
			case ADD_SPEED:
				hero->useEffect(SPEED_UP_EFFECT);
				break;
			}

			if (items[i] != nullptr) {
				delete items[i];
				items.erase(items.begin() + i);
			}
		}
	}
}

void Game::handleEffect() {
	if(hero->mEffectList[0]->mCurrentTime != 0) {
		for(auto it : items) {
			if(it->getItemType() == ADD_COIN) {
				int x1 = hero->getRect().x + hero->getRect().w/2, y1 = hero->getRect().y + hero->getRect().h/2;
				int x2 = it->getRect().x - x1, y2 = it->getRect().y - y1;
				if(std::abs(x2) > std::abs(y2)) {
					it->mXVal = (x2 < 0) ? 3 : -3;
					it->mYVal = y2 * it->mXVal / x2;
				}
				else {
					it->mYVal = (y2 < 0) ? 3 : -3;
					it->mXVal = x2 * it->mYVal / y2;
				}
			}
		}
	}
}

void Game::restart(SDL_Renderer* renderer) {
	setRect(0, 0);
	hero->restart(renderer);
	for (int j = 0; j < int(bots.size()); j++) {
		bots[j]->restart(renderer);
	}
	boss->restart(renderer);

	while (!items.empty()) {
		if (items[items.size() - 1] != nullptr) {
			items[items.size() - 1]->free();
			delete items[items.size() - 1];
			items.pop_back();
		}
	}
}

void Game::setUpLevel(SDL_Renderer* renderer, int level) {
	mState = static_cast<GameState> (int(LEVEL1) + rand()%5);
	mLevelText->loadText(renderer, font, "LEVEL " + std::to_string(mLevel));
	if(level <= 3) {
		for(int i = 0; i < int(bots.size()); i++) {
			bots[i]->setIsAppear((i < 2) ? true : false);
		}
	}
	else if(level <= 9) {
		for(int i = 0; i < int(bots.size()); i++) {
			bots[i]->setIsAppear((i < level) ? true : false);
		}
	}
	mBossTime = SDL_GetTicks64();
	this->restart(renderer);
}
