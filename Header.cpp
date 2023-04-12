#include"Header.h"

Game1::Game1() {
	mRect.x = mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = SCREEN_HEIGHT;
	mXVal = -1; mYVal = 0;
	mState = oldState = START;
}

void Game1::handleMove() {
	if (mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY && checkToMove(20)) {
		BaseClass::handleMove();
		if (mRect.x <= -1200) mRect.x = 0;
	}
}

void Game1::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	mTexture = mTextures[int(mState)];
	if (mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY) {
		BaseClass::render(renderer);
		mRect.x += 1200;
		BaseClass::render(renderer);
		mRect.x -= 1200;
	}
	else {
		BaseClass::render(renderer);
	}
}

void Game1::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	SDL_Texture* loadedTexture;
	for (std::string s : listName) {
		loadedTexture = loadTexture(renderer, s);
		mTextures.push_back(loadedTexture);
	}
}

void Game1::handleState(SDL_Renderer* renderer, std::pair<int, int> mouse, SDL_Event event) {

	if (!(mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY)) {
		setRect(0, 0);
	}

	switch (mState) {

	case START:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 140 && mouse.second <= 190) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mState = LEVEL_1;
				hero->reborn();
			}
			SDL_Rect rect = { 550, 140, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = SHOP;
			SDL_Rect rect = { 550, 220, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = UPGRADE;
			SDL_Rect rect = { 500, 300, 200, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case LEVEL_1:
	case LEVEL_2:
	case LEVEL_3:
	case LEVEL_4:
	case LEVEL_5:
		break;
	case DEAD:
		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mState = oldState;
			}

			SDL_Rect rect = { 490, 220, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mState = START;
				for (int i = 0; i < int(bots.size()); i++) {
					if (i < 2) {
						bots[i]->setIsAppear(true);
					}
					else {
						bots[i]->setIsAppear(false);
					}
				}
			}

			SDL_Rect rect = { 550, 300, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case SHOP:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10) {
					hero->setCoin(hero->getCoin() - 10);
					hero->loadImage(renderer, HERO3_PATHS);
				}
			}
			SDL_Rect rect = { 550, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 230 && mouse.first <= 330 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10) {
					hero->setCoin(hero->getCoin() - 10);
					hero->loadImage(renderer, HERO1_PATHS);
				}
			}
			SDL_Rect rect = { 230, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 860 && mouse.first <= 960 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10) {
					hero->setCoin(hero->getCoin() - 10);
					hero->loadImage(renderer, HERO2_PATHS);
				}
			}
			SDL_Rect rect = { 860, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 380 && mouse.second <= 430) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;

			SDL_Rect rect = { 550, 380, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;

	case VICTORY:
		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 140 && mouse.second <= 190) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (oldState == LEVEL_1) {
					mState = LEVEL_2;
					bots[2]->setIsAppear(true);
				}
				else if (oldState == LEVEL_2) {
					mState = LEVEL_3;
					bots[2]->setIsAppear(true);
				}
				else if (oldState == LEVEL_3) {
					mState = LEVEL_4;
					bots[3]->setIsAppear(true);
				}
				else if (oldState == LEVEL_4) {
					mState = LEVEL_5;
					bots[4]->setIsAppear(true);
				}
				else if (oldState == LEVEL_5) {
					mState = LEVEL_5;
					bots[5]->setIsAppear(true);
				}
			}

			SDL_Rect rect = { 490, 140, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}

		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (oldState == LEVEL_1) {
					mState = LEVEL_1;
				}
				else if (oldState == LEVEL_2) {
					mState = LEVEL_2;
				}
				else if (oldState == LEVEL_3) {
					mState = LEVEL_3;
				}
				else if (oldState == LEVEL_4) {
					mState = LEVEL_4;
				}
				else if (oldState == LEVEL_5) {
					mState = LEVEL_5;
				}
			}

			SDL_Rect rect = { 490, 220, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;

			for (int i = 0; i < int(bots.size()); i++) {
				if (i < 2) {
					bots[i]->setIsAppear(true);
				}
				else {
					bots[i]->setIsAppear(false);
				}
			}
			SDL_Rect rect = { 550, 300, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case UPGRADE:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 380 && mouse.second <= 430) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;
			SDL_Rect rect = { 550, 380, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 130 && mouse.second <= 180) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10 && hero->getMaxHeart() < 110) {
					hero->setCoin(hero->getCoin() - 10);
					hero->setMaxHeart(hero->getMaxHeart() + 10);
				}
			}
			SDL_Rect rect = { 1030, 130, 60, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 210 && mouse.second <= 260) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10 && hero->getAmor() < 6) {
					hero->setCoin(hero->getCoin() - 10);
					hero->setAmor(hero->getAmor() + 1);
				}
			}
			SDL_Rect rect = { 1030, 210, 60, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 290 && mouse.second <= 340) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10 && hero->getAttack() < 35) {
					hero->setCoin(hero->getCoin() - 10);
					hero->setAttack(hero->getAttack() + 5);
				}
			}
			SDL_Rect rect = { 1030, 290, 60, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}

		SDL_Rect rectBg = { 320, 140, 600, 10 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_Rect rect = { 320, 140, (hero->getMaxHeart() - 50) / 10 * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 230, (hero->getAmor() - 0) * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 320, (hero->getAttack() - 5) / 5 * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);

		break;
	}
}


void Game1::handleLogic(SDL_Renderer* renderer) {
	if (hero->checkIsDestroyed()) {
		mState = DEAD;
		hero->reborn();
		for (int j = 0; j < int(bots.size()); j++) {
			bots[j]->reborn(renderer);
		}
	}

	if (hero->getScore() >= 10) {
		mState = VICTORY;
		hero->reborn();
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->reborn(renderer);
		}
	}

	this->handleCollision(renderer);
}

void Game1::handleCollision(SDL_Renderer* renderer) {
	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {

			for (int i = 0; i < int(hero->getBulletList().size()); i++) {
				if (checkConllision(bots[j], hero->getBulletList()[i])) {
					bots[j]->getDamage(hero->getAttack());
					hero->getBulletList()[i]->setIsAppear(false);
				}
			}

			for (int i = 0; i < int(bots[j]->getBulletList().size()); i++) {
				if (bots[j]->getHeart() != 0 && checkConllision(hero, bots[j]->getBulletList()[i])) {
					hero->getDamage(bots[j]->getAttack());
					bots[j]->getBulletList()[i]->setIsAppear(false);
				}
			}

			if (checkConllision(hero, bots[j]) && bots[j]->getHeart() != 0) {
				bots[j]->getDamage(1000);
				hero->getDamage(30);
			}
		}
		if (bots[j]->checkIsDestroyed()) {
			Mix_PlayChannel(-1, mBonkMusic, 0);
			hero->setScore(hero->getScore() + 2);
			hero->setCoin(hero->getCoin() + 3);
			
			Item* newItem = new Item();
			newItem->loadImage(renderer, ItemType::BUFF_HP);
			newItem->setRect(bots[j]->getRect().x, bots[j]->getRect().y, 50, 50);
			items.push_back(newItem);
		}
	}

	for (int i = 0; i < int(items.size()); i++) {
		if (checkConllision(hero, items[i])) {
			if (items[i]->getItemType() == ItemType::BUFF_HP) {
				hero->setHeart(hero->getHeart() + 10);
			}
			delete items[i];
			items.erase(items.begin() + i);
		}
	}
}


void Game1::renderText(SDL_Renderer* renderer) {
	if (mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY) {
		texts[0]->loadText(renderer, font, "Score : " + std::to_string(hero->getScore())) ; texts[0]->render(renderer);
		texts[1]->loadText(renderer, font, "Coin : " + std::to_string(hero->getCoin())); texts[1]->render(renderer);
	}
	else if (mState == SHOP || mState == UPGRADE) {
		texts[1]->loadText(renderer, font, "Coin : " + std::to_string(hero->getCoin())); texts[1]->render(renderer);
	}
}

void Game1::loadResource(SDL_Renderer* renderer) {
	hero = new Character();
	this->loadImage(renderer, GAME_PATHS);
	hero->loadImage(renderer, HERO1_PATHS);

	mGameMusic = Mix_LoadMUS("Music_Folder/music.mp3");
	mBonkMusic = Mix_LoadWAV("Music_Folder/bonk.wav");

	for (int i = 0; i < 10; i++) {
		Bot* newBot = new Bot();
		newBot->loadImage(renderer, BOTS_PATHS[rand() % 3]);
		newBot->setBotType(static_cast<BotType>(rand() % 2));

		if (i <= 1) {
			newBot->setIsAppear(true);
		}
		else {
			newBot->setIsAppear(false);
		}
		bots.push_back(newBot);
	}

	for (int i = 0; i < 2; i++) {
		Text* newText = new Text();
		newText->setRect(0, i * 30);
		texts.push_back(newText);
	}
	mState = oldState = Game1Type::START;
	font = TTF_OpenFont("Font_Folder/font2.ttf", 30);
}


void Game1::handleObject(SDL_Renderer* renderer) {

	hero->handleMove(); hero->handleState(renderer); hero->handleSkill(); hero->renderText(renderer, font); hero->render(renderer, 1);

	for (int i = 0; i < int(bots.size()); i++) {
		if (bots[i]->getIsAppear()) {
			bots[i]->handleAction(renderer); bots[i]->handleMove(); bots[i]->handleState(renderer); bots[i]->render(renderer, -1);
		}
	}
	for (int i = 0; i < int(items.size()); i++) {
		items[i]->handleMove(); items[i]->render(renderer);
		if (items[i]->getRect().x <= 0) {
			delete items[i];
			items.erase(items.begin() + i);
		}
	}
}