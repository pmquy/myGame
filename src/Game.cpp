#include"Game.h"

Game::Game() {
	mRect.x = mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = SCREEN_HEIGHT;
	mXVal = -1; mYVal = 0;
	mState = oldState = HOME;
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
	for (auto it : texts) {
		if (it != nullptr) {
			delete it;
			it = nullptr;
		}
	}
	texts = {};
}

void Game::handleMove() {
	if ((mState == LEVEL1 || mState == LEVEL2 || mState == LEVEL3 || mState == LEVEL4 || mState == LEVEL5) && checkToMove(20)) {
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
		rect = { 320, 320, (hero->getMaxAtk() - 5) * 100 / 2, 10 };
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
	std::pair<int, int> mouse;
	SDL_GetMouseState(&mouse.first, &mouse.second);

	switch (mState) {

	case LEVEL1:
	case LEVEL2:
	case LEVEL3:
	case LEVEL4:
	case LEVEL5:
		oldState = mState;
		if (hero->checkIsDestroyed()) {
			mState = LOSE;
			setRect(0, 0);
			Mix_PlayMusic(mHomeMusic, -1);
		}
		if (boss->getIsAppear() && boss->checkIsDestroyed()) {
			mState = WIN;
			setRect(0, 0);
			Mix_PlayMusic(mHomeMusic, -1);
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
				mState = LEVEL1;
				setUpLevel(renderer, LEVEL1);
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
				mState = oldState;
				Mix_PlayMusic(mGameMusic, -1);
				setUpLevel(renderer, mState);
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
				if (oldState < LEVEL5) {
					mState = static_cast<GameState>(int(oldState + 1));
				}
				else {
					mState = LEVEL5;
				}
				setUpLevel(renderer, mState);
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
				mState = oldState;
				setUpLevel(renderer, mState);
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
				if (hero->getCoin() >= 20 && hero->getAtk() < 17) {
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

	mGameMusic = Mix_LoadMUS("Music_Folder/music.mp3");
	mHomeMusic = Mix_LoadMUS("Music_Folder/home.mp3");
	mIntroMusic = Mix_LoadMUS("Music_Folder/intro.mp3");
	mBonkMusic = Mix_LoadWAV("Music_Folder/bonk.wav");
	mItemMusic = Mix_LoadWAV("Music_Folder/item.wav");
	mWinMusic = Mix_LoadWAV("Music_Folder/win.wav");
	mGameOverMusic = Mix_LoadWAV("Music_Folder/game_over.wav");;

	for (int i = 0; i < 10; i++) {
		Bot* newBot = new Bot();
		newBot->loadImage(renderer, BOTS_PATHS[rand() % 3]);

		if (i <= 1) {
			newBot->setIsAppear(true);
		}
		else {
			newBot->setIsAppear(false);
		}
		bots.push_back(newBot);
	}

	font = TTF_OpenFont("Font_Folder/font2.ttf", 30);
	
	Text* newText = new Text();
	newText->loadText(renderer, font, "BOSS");
	texts.push_back(newText);

	mState = oldState = GameState::HOME;
}


void Game::updateObject(SDL_Renderer* renderer) {

	hero->handleMove(); hero->handleState(renderer); hero->handleSkill(); hero->render(renderer, 1);
	hero->renderCoin(renderer, font); hero->renderScore(renderer, font); hero->renderSkill(renderer, font);

	for (int i = 0; i < int(bots.size()); i++) {
		if (bots[i]->getIsAppear()) {
			bots[i]->handleAction(renderer); bots[i]->handleMove(); bots[i]->handleState(renderer); bots[i]->render(renderer, -1); bots[i]->handleSkill();
		}
	}

	for (int i = 0; i < int(items.size()); i++) {
		items[i]->handleMove(); items[i]->render(renderer);
		if (items[i]->getRect().x <= 0) {
			delete items[i];
			items.erase(items.begin() + i);
		}
	}

	if (boss->getIsAppear()) {
		boss->handleAction(renderer); boss->handleMove(); boss->handleState(renderer); boss->render(renderer, -1); boss->handleSkill();
		boss->renderText(renderer, font);
	}

	if(boss->getHp() != 0)
		this->handleCollision(renderer);

	if (hero->getScore() >= 2 * int(mState)) {
		boss->setIsAppear(true);
	}
	
}


void Game::handleCollision(SDL_Renderer* renderer) {
	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {
			check(hero, bots[j]);
		}
		if (bots[j]->checkIsDestroyed() && bots[j]->getIsAppear()) {
			hero->setScore(hero->getScore() + 2);
			hero->setCoin(hero->getCoin() + 3);
			Mix_PlayChannel(-1, mBonkMusic, 0);

			Item* newItem = new Item();
			newItem->loadImage(renderer, static_cast<ItemType>(rand() % 5));
			newItem->setRect(bots[j]->getRect().x + 10, bots[j]->getRect().y + bots[j]->getRect().h / 2);
			items.push_back(newItem);
		}
	}

	if (boss->getIsAppear()) {
		check(boss, hero);
	}

	if (boss->getIsAppear() && boss->checkIsDestroyed()) {
		Mix_PlayChannel(-1, mWinMusic, 0);
		hero->setScore(hero->getScore() + 10);
		hero->setCoin(hero->getCoin() + 10);
	}


	if (hero->checkIsDestroyed()) {
		Mix_PlayChannel(-1, mGameOverMusic, 0);
	}

	for (int i = 0; i < int(items.size()); i++) {

		if (hero->getHp() > 0 && checkConllision(hero, items[i])) {
			Mix_PlayChannel(-1, mItemMusic, 0);
			switch (items[i]->getItemType()) {
			case BUFF_HP:
				hero->setHp(hero->getHp() + 10);
				break;

			case ADD_BULLET:
				hero->setMaxBullet(hero->getMaxBullet() + 1);
				if (hero->getMaxBullet() >= 5) {
					hero->setMaxBullet(5);
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
			}
			if (items[i] != nullptr) {
				delete items[i];
				items.erase(items.begin() + i);
			}
		}
	}
}

void Game::restart(SDL_Renderer* renderer) {
	hero->restart();
	for (int j = 0; j < int(bots.size()); j++) {
		bots[j]->restart(renderer);
	}

	while (!items.empty()) {
		if (items[items.size() - 1] != nullptr) {
			items[items.size() - 1]->free();
			delete items[items.size() - 1];
			items.pop_back();
		}
	}
	setRect(0, 0);
	boss->setIsAppear(false);
	boss->restart(renderer);
}

void Game::setUpLevel(SDL_Renderer* renderer, GameState state) {
	switch (state) {
	case LEVEL1:
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->setMaxAtk(2);
			bots[i]->setMaxHp(50);
			bots[i]->setMaxDef(0);
			bots[i]->setMaxBullet(2);
			if (i < 2) {
				bots[i]->setIsAppear(true);
			}
			else {
				bots[i]->setIsAppear(false);
			}
		}
		boss->setMaxAtk(5);
		boss->setMaxHp(100);
		boss->setMaxDef(0);
		boss->setMaxBullet(4);
		break;

	case LEVEL2:
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->setMaxAtk(3);
			bots[i]->setMaxHp(60);
			bots[i]->setMaxDef(0);
			bots[i]->setMaxBullet(3);
			if (i < 3) {
				bots[i]->setIsAppear(true);
			}
			else {
				bots[i]->setIsAppear(false);
			}
		}
		boss->setMaxAtk(5);
		boss->setMaxHp(100);
		boss->setMaxDef(1);
		boss->setMaxBullet(4);
		break;
	case LEVEL3:
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->setMaxAtk(3);
			bots[i]->setMaxHp(70);
			bots[i]->setMaxDef(1);
			bots[i]->setMaxBullet(3);
			if (i < 4) {
				bots[i]->setIsAppear(true);
			}
			else {
				bots[i]->setIsAppear(false);
			}
		}
		boss->setMaxAtk(8);
		boss->setMaxHp(150);
		boss->setMaxDef(1);
		boss->setMaxBullet(5);
		break;
	case LEVEL4:
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->setMaxAtk(4);
			bots[i]->setMaxHp(80);
			bots[i]->setMaxDef(1);
			bots[i]->setMaxBullet(3);
			if (i < 5) {
				bots[i]->setIsAppear(true);
			}
			else {
				bots[i]->setIsAppear(false);
			}
		}
		boss->setMaxAtk(10);
		boss->setMaxHp(200);
		boss->setMaxDef(2);
		boss->setMaxBullet(6);
		break;
	case LEVEL5:
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->setMaxAtk(5);
			bots[i]->setMaxHp(100);
			bots[i]->setMaxDef(1);
			bots[i]->setMaxBullet(3);
			if (i < 7) {
				bots[i]->setIsAppear(true);
			}
			else {
				bots[i]->setIsAppear(false);
			}
		}
		boss->setMaxAtk(20);
		boss->setMaxHp(250);
		boss->setMaxDef(4);
		boss->setMaxBullet(6);
		break;
	}
	this->restart(renderer);

}