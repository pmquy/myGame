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
	if (mState == HOME2 && checkToMove(5)) {
		BaseClass::handleMove();
	}
}

void Game::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	if (mState != HOME2) {
		mTexture = mTextures[int(mState)];
		if (mState == LEVEL1 || mState == LEVEL2 || mState == LEVEL3 || mState == LEVEL4 || mState == LEVEL5) {
			BaseClass::render(renderer);
			mRect.x += SCREEN_WIDTH;
			BaseClass::render(renderer);
			mRect.x -= SCREEN_WIDTH;
		}
		else {
			BaseClass::render(renderer);
		}
	}
	else {
		SDL_Rect oldRect = mRect;
		mTexture = mTextures[int(START)];
		setRect(0, 0);
		BaseClass::render(renderer);
		setRect(oldRect.x, oldRect.y);
		mTexture = mTextures[int(HOME)];
		BaseClass::render(renderer);
	}

	if (mState == UPGRADE || mState == UPGRADE2 || mState == UPGRADE1 || mState == UPGRADE3 || mState == UPGRADE4) {
		SDL_Rect rectBg = { 320, 140, 600, 10 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_Rect rect = { 320, 140, (hero->getMaxHp() - 50) / 10 * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 230, (hero->getDef() - 0) * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 320, (hero->getAtk() - 5) / 5 * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
	}

	if (mState == LEVEL1 || mState == LEVEL2 || mState == LEVEL3 || mState == LEVEL4 || mState == LEVEL5) {
		texts[0]->loadText(renderer, font, "Score : " + std::to_string(hero->getScore()), color); texts[0]->render(renderer);
		texts[1]->loadText(renderer, font, "Coin : " + std::to_string(hero->getCoin()), color); texts[1]->render(renderer);
	}
	if (mState == UPGRADE || mState == UPGRADE2 || mState == UPGRADE1 || mState == UPGRADE3 || mState == UPGRADE4 ||
		mState == SHOP || mState == SHOP1 || mState == SHOP2 || mState == SHOP3 || mState == SHOP4) {
		texts[1]->loadText(renderer, font, "Coin : " + std::to_string(hero->getCoin()), color); texts[1]->render(renderer);
	}
	if (boss->getIsAppear()) {
		texts[2]->setRect(boss->getRect().x + 80, boss->getRect().y); texts[2]->render(renderer);
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
		if (hero->checkIsDestroyed()) {
			mState = LOSE;
			this->restart(renderer);
		}
		if (boss->getIsAppear() && boss->checkIsDestroyed()) {
			mState = WIN;
			this->restart(renderer);
		}
		break;
	case HOME:
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 252 && mouse.second <= 327) {
			mState = HOME1;
		}
		break;

	case HOME1:
		if (!(mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 252 && mouse.second <= 327)) {
			mState = HOME;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mState = HOME2;
			mYVal = -1; mXVal = 0;
		}
		break;

	case HOME2:
		if (event.type == SDL_MOUSEBUTTONDOWN || mRect.y <= -SCREEN_HEIGHT) {
			setRect(0, 0);
			mState = START;
			mXVal = -1; mYVal = 0;
		}
		break;

	case START1:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mState = LEVEL1;
			hero->restart();
		}
		if (!(mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 152 && mouse.second <= 227)) {
			mState = START;
		}
		break;

	case START2:
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mState = SHOP;

		if (!(mouse.first >= 540 && mouse.first <= 660 && mouse.second >= 252 && mouse.second <= 327)) {
			mState = START;
		}
		break;

	case START3:
		if (!(mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 363 && mouse.second <= 438)) {
			mState = START;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mState = UPGRADE;
		break;

	case START:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 152 && mouse.second <= 227) {
			mState = START1;
		}
		if (mouse.first >= 540 && mouse.first <= 660 && mouse.second >= 252 && mouse.second <= 327) {
			mState = START2;
		}
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 363 && mouse.second <= 438) {
			mState = START3;
		}
		break;
	
	case LOSE1:
		if (!(mouse.first >= 520 && mouse.first <= 680 && mouse.second >= 252 && mouse.second <= 327)) {
			mState = LOSE;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mState = oldState;
		break;

	case LOSE2:
		if (!(mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427)) {
			mState = LOSE;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (int i = 0; i < int(bots.size()); i++) {
				if (i < 2) {
					bots[i]->setIsAppear(true);
				}
				else {
					bots[i]->setIsAppear(false);
				}
			}
			mState = START;
		}
		break;

	case LOSE:
		if (mouse.first >= 520 && mouse.first <= 680 && mouse.second >= 252 && mouse.second <= 327) {
			mState = LOSE1;
		}
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427) {
			mState = LOSE2;
		}
		break;
	
	case SHOP1:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (hero->getCoin() >= 50) {
				hero->setCoin(hero->getCoin() - 50);
				hero->loadImage(renderer, HERO1_PATHS);
			}
		}
		if (!(mouse.first >= 230 && mouse.first <= 330 && mouse.second >= 216 && mouse.second <= 291)) {
			mState = SHOP;
		}
		break;

	case SHOP2:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (hero->getCoin() >= 50) {
				hero->setCoin(hero->getCoin() - 50);
				hero->loadImage(renderer, HERO3_PATHS);
			}
		}
		if (!(mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 216 && mouse.second <= 291)) {
			mState = SHOP;
		}
		break;
	case SHOP3:
		if (!(mouse.first >= 860 && mouse.first <= 960 && mouse.second >= 216 && mouse.second <= 291)) {
			mState = SHOP;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (hero->getCoin() >= 50) {
				hero->setCoin(hero->getCoin() - 50);
				hero->loadImage(renderer, HERO2_PATHS);
			}
		}
		break;
	case SHOP4:
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mState = START;
		if (!(mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427)) {
			mState = SHOP;
		}
		break;

	case SHOP:
		if (mouse.first >= 230 && mouse.first <= 330 && mouse.second >= 216 && mouse.second <= 291) {
			mState = SHOP1;
		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 216  && mouse.second <= 291) {
			mState = SHOP2;
		}
		if (mouse.first >= 860 && mouse.first <= 960 && mouse.second >= 216 && mouse.second <= 291) {
			mState = SHOP3;
		}
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427) {
			mState = SHOP4;
		}
		break;

	case WIN1:
		if (!(mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 152 && mouse.second <= 227)) {
			mState = WIN;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (oldState == LEVEL1) {
				mState = LEVEL2;
				bots[2]->setIsAppear(true);
			}
			else if (oldState == LEVEL2) {
				mState = LEVEL3;
				bots[2]->setIsAppear(true);
			}
			else if (oldState == LEVEL3) {
				mState = LEVEL4;
				bots[3]->setIsAppear(true);
			}
			else if (oldState == LEVEL4) {
				mState = LEVEL5;
				bots[4]->setIsAppear(true);
			}
			else if (oldState == LEVEL5) {
				mState = LEVEL5;
				bots[5]->setIsAppear(true);
			}
		}
		break;
	case WIN2:
		if (!(mouse.first >= 540 && mouse.first <= 660 && mouse.second >= 252 && mouse.second <= 327)) {
			mState = WIN;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (oldState == LEVEL1) {
				mState = LEVEL1;
			}
			else if (oldState == LEVEL2) {
				mState = LEVEL2;
			}
			else if (oldState == LEVEL3) {
				mState = LEVEL3;
			}
			else if (oldState == LEVEL4) {
				mState = LEVEL4;
			}
			else if (oldState == LEVEL5) {
				mState = LEVEL5;
			}
		}
		break;
	case WIN3:
		if (!(mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427)) {
			mState = WIN;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (int i = 0; i < int(bots.size()); i++) {
				if (i < 2) {
					bots[i]->setIsAppear(true);
				}
				else {
					bots[i]->setIsAppear(false);
				}
			}
			mState = START;
		}
		break;

	case WIN:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 152 && mouse.second <= 227) {
			mState = WIN1;
		}

		if (mouse.first >= 540 && mouse.first <= 660 && mouse.second >= 252 && mouse.second <= 327) {
			mState = WIN2;
		}

		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427) {
			mState = WIN3;
		}
		break;
	case UPGRADE1:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (hero->getCoin() >= 20 && hero->getMaxHp() < 110) {
				hero->setCoin(hero->getCoin() - 20);
				hero->setMaxHp(hero->getMaxHp() + 20);
			}
		}
		if (!(mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 119 && mouse.second <= 180)) {
			mState = UPGRADE;
		}
		break;

	case UPGRADE2:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (hero->getCoin() >= 20 && hero->getDef() < 6) {
				hero->setCoin(hero->getCoin() - 20);
				hero->setDef(hero->getDef() + 1);
			}
		}
		if (!(mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 204 && mouse.second <= 265)) {
			mState = UPGRADE;
		}
		break;

	case UPGRADE3:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (hero->getCoin() >= 20 && hero->getAtk() < 35) {
				hero->setCoin(hero->getCoin() - 20);
				hero->setAtk(hero->getAtk() + 5);
			}
		}
		if (!(mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 291 && mouse.second <= 352)) {
			mState = UPGRADE;
		}
		break;

	case UPGRADE4:
		if (!(mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427)) {
			mState = UPGRADE;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mState = START;
		}
		break;

	case UPGRADE:
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 352 && mouse.second <= 427) {
			mState = UPGRADE4;
		}
		if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 119 && mouse.second <= 180) {
			
			mState = UPGRADE1;
		}
		if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 204 && mouse.second <= 265) {

			mState = UPGRADE2;
		}
		if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 291 && mouse.second <= 352) {
			
			mState = UPGRADE3;
		}
		break;
	}
}

void Game::restart(SDL_Renderer* renderer) {
	hero->restart();
	
	for (int j = 0; j < int(bots.size()); j++) {
		bots[j]->restart(renderer);
	}

	while(!items.empty()) {
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


void Game::handleCollision(SDL_Renderer* renderer) {
	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {
			check(hero, bots[j]);
		}
		if (bots[j]->checkIsDestroyed()) {
			Mix_PlayChannel(-1, mBonkMusic, 0);
			hero->setScore(hero->getScore() + 2);
			hero->setCoin(hero->getCoin() + 3);
			
			Item* newItem = new Item();
			newItem->loadImage(renderer, static_cast<ItemType>(rand() % 4));
			newItem->setRect(bots[j]->getRect().x + 10, bots[j]->getRect().y + bots[j]->getRect().h / 2);
			items.push_back(newItem);
		}
	}

	if (boss->getIsAppear()) {
		check(boss, hero);
	}

	if (boss->checkIsDestroyed()) {
		Mix_PlayChannel(-1, mBonkMusic, 0);
		hero->setScore(hero->getScore() + 50);
		hero->setCoin(hero->getCoin() + 50);
	}

	if (hero->checkIsDestroyed()) {
		Mix_PlayChannel(-1, mBonkMusic, 0);
	}

	for (int i = 0; i < int(items.size()); i++) {
		if (hero->getHp() > 0 && checkConllision(hero, items[i])) {

			switch (items[i]->getItemType()) {
			case BUFF_HP:
				hero->setHp(hero->getHp() + 10);
				break;
			case ADD_BLUE_BALL:
				if (hero->getCurrentBullet() == BLUE_BALL) {
					hero->mMaxBullet += 1;
					if (hero->mMaxBullet >= 5) {
						hero->mMaxBullet = 5;
					}
				}
				else {
					hero->setCurrentBullet(BLUE_BALL);
					hero->mMaxBullet = 1;
				}
				break;
			case ADD_GREEN_BALL:
				if (hero->getCurrentBullet() == GREEN_BALL) {
					hero->mMaxBullet += 1;
					if (hero->mMaxBullet >= 5) {
						hero->mMaxBullet = 5;
					}
				}
				else {
					hero->setCurrentBullet(GREEN_BALL);
					hero->mMaxBullet = 1;
				}
				break;
			case ADD_RED_BALL:
				if (hero->getCurrentBullet() == RED_BALL) {
					hero->mMaxBullet += 1;
					if (hero->mMaxBullet >= 5) {
						hero->mMaxBullet = 5;
					}
				}
				else {
					hero->setCurrentBullet(RED_BALL);
					hero->mMaxBullet = 1;
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


void Game::loadResource(SDL_Renderer* renderer) {
	
	this->loadImage(renderer, GAME_PATHS);

	hero = new Character(); hero->loadImage(renderer, HERO1_PATHS);

	boss = new Boss(); boss->loadImage(renderer, BOTS_PATHS[rand() % 3]);

	mGameMusic = Mix_LoadMUS("Music_Folder/music.mp3");
	mBonkMusic = Mix_LoadWAV("Music_Folder/bonk.wav");

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

	for (int i = 0; i < 3; i++) {
		Text* newText = new Text();
		if (i == 2) {
			newText->loadText(renderer, font, "BOSS");
		}
		newText->setRect(0, i * 30);
		texts.push_back(newText);
	}
	mState = oldState = GameType::HOME;
}


void Game::handleObject(SDL_Renderer* renderer) {

	hero->handleMove(); hero->handleState(renderer); hero->handleSkill(); hero->renderText(renderer, font); hero->render(renderer, 1);

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
	}

	if (hero->getScore() >= 4) {
		boss->setIsAppear(true);
	}

	this->handleCollision(renderer);
}