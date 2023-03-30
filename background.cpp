#include "Background.h"
#include "Character.h"



Background::Background() {
	startTime = 0;
	mRect.x = mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = SCREEN_HEIGHT;
	mState = START;
}

Background::~Background() {
	free();
}

void Background::handleMove() {
	int duration = SDL_GetTicks() - startTime;
	if (duration >= 20 && (mState == LEVEL_1 || mState == LEVEL_2)) {
		mRect.x--;
		if (mRect.x <= -1200) mRect.x = 0;
		startTime = SDL_GetTicks();
	}
}

void Background::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	mTexture = mTextures[int(mState)];
	if (mState == LEVEL_1 || mState == LEVEL_2) {
		BaseClass::render(renderer);
		mRect.x += 1200;
		BaseClass::render(renderer);
		mRect.x -= 1200;
	}
	else {
		BaseClass::render(renderer);
	}
}

void Background::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	SDL_Texture* loadedTexture = nullptr;
	for (std::string s : listName) {
		loadedTexture = loadTexture(renderer, s);
		mTextures.push_back(loadedTexture);
	}
}

void Background::handleState(BackgroundType &s, SDL_Renderer* renderer, std::pair<int, int>& mouse, SDL_Event &event, Character* hero) {
	mState = s;

	if (mState != LEVEL_1 && mState != LEVEL_2) {
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
			if(event.type == SDL_MOUSEBUTTONDOWN)
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
		break;
	case DEAD:
		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = LEVEL_1;
			SDL_Rect rect = { 490, 220, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		else if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;
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
					hero->loadImage(renderer, HERO_PATHS3);
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
					hero->loadImage(renderer, HERO_PATHS1);
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
					hero->loadImage(renderer, HERO_PATHS2);
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
				mState = LEVEL_2;
				std::cout << mState;
			}
				
			SDL_Rect rect = { 490, 140, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}

		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = LEVEL_1;
			SDL_Rect rect = { 490, 220, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;
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
				
		SDL_Rect rectBg = {320, 140, 600, 10};
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
	s = mState;
}

