#include "Background.h"
#include "Character.h"



Background::Background() {
	startTime = 0;
	mRect.x = mRect.y = mRect.w = mRect.h = 0;
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
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 220 && mouse.second <= 270) {
			if(event.type == SDL_MOUSEBUTTONDOWN)
				mState = LEVEL_1;
			SDL_Rect rect = { 550, 220, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = SHOP;
			SDL_Rect rect = { 550, 300, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case LEVEL_1:
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
	case SHOP:
		
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				hero->loadImage(renderer, HERO_PATHS3);
			}
				
			
			SDL_Rect rect = { 550, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		else if (mouse.first >= 230 && mouse.first <= 330 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				hero->loadImage(renderer, HERO_PATHS1);
			}
				
			SDL_Rect rect = { 230, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		else if (mouse.first >= 860 && mouse.first <= 960 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				hero->loadImage(renderer, HERO_PATHS2);
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
	}

	s = mState;
}

