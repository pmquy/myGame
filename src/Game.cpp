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

	std::ofstream file("highscore.txt");
	for(int i = 0; i < 10; i++) {
		file << mHighScores[i].first << " " << mHighScores[i].second << "\n";
	}
	file.close();

	for(auto &it : mHighScoreTexts) {
		if(it) {
			delete it;
			it = nullptr;
		}
	}
	mHighScoreTexts = {};
}

void Game::handleMove() {
	if (mState == LEVEL && checkToMove(20)) {
		BaseClass::handleMove();
		if (mRect.x <= -mRect.w) mRect.x = 0;
	}
	if (mState == HOME2 && checkToMove(10)) {
		BaseClass::handleMove();
	}
}

void Game::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	if (mState != HOME2) {
		mTexture = mTextures[int(mState)];
	}
	
	if (mState == LEVEL) {
		SDL_Rect oldRect = getRect();
		BaseClass::render(renderer);
		while(mRect.x + mRect.w < SCREEN_WIDTH) {
			mRect.x += mRect.w;
			BaseClass::render(renderer);
		}
		setRect(oldRect.x, oldRect.y);

		//render ra o coin,score
		SDL_SetRenderDrawColor(renderer, 42, 157, 143, 0.5);
		SDL_Rect rect = {0,0, 160,100}; SDL_RenderFillRect(renderer, &rect);
		rect = {0,540, 200,60}; SDL_RenderFillRect(renderer, &rect);

		mLevelText->render(renderer);

		if(!hero->checkIsDestroyed()) {
			hero->render(renderer);hero->renderCoin(renderer, font); hero->renderScore(renderer, font); hero->renderSkill(renderer, font); hero->renderEffect(renderer, font);
			
			if(!boss->checkIsDestroyed()) {
				for (int i = 0; i < int(bots.size()); i++) {
					if (bots[i]->getIsAppear()) {
						bots[i]->render(renderer);
					}
				}
				boss->renderText(renderer, font);boss->render(renderer); 
				for (int i = 0; i < int(items.size()); i++) {
					items[i]->render(renderer);
				}
			}
		}
	}
	else if (mState == HOME2) {
		SDL_Rect oldRect = mRect;
		mTexture = mTextures[START];
		setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		BaseClass::render(renderer);
		setRect(oldRect.x, oldRect.y);
		mTexture = mTextures[HOME];
		BaseClass::render(renderer);
	}
	else {
		setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
		SDL_Rect rect = { 320, 140, (hero->getNormalHp() - 50) * 100 / 10 , 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 230, (hero->getNormalDef() - 0) * 100 / 1, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 320, (hero->getNormalAtk() - 20) * 100 / 2, 10 };
		SDL_RenderFillRect(renderer, &rect);
		hero->renderCoin(renderer, font);
	}
	if (mState >= SHOP && mState <= SHOP9) {
		hero->renderCoin(renderer, font);
	}	
	if(mState >= HIGHSCORE && mState <= HIGHSCORE2) {
		renderHighScore(renderer);
		if(mState == HIGHSCORE) {
			userNameText->render(renderer);
		}
	}
}

void Game::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	for (std::string s : listName) {
		mTextures.push_back(loadTexture(renderer, s));
	}
}

void Game::handleState(SDL_Renderer* renderer, SDL_Event event) {
	switch (mState) {
	case LEVEL:
		// hack
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_END) {
			if(boss->getIsAppear())
				boss->setHp(0);
			else 
				boss->setIsAppear(true);
		}

		if (hero->checkIsDestroyed()) {
			Mix_PlayChannel(-1, mGameOverMusic, 0);
			Mix_PlayMusic(mHomeMusic, -1);

			for(auto &it : mHighScores) {
				if(it.second <= hero->getScore()) {
					mState = HIGHSCORE;
					return;
				}
			}
			mState = HIGHSCORE1;
		}
		else {
			if(boss->checkIsDestroyed() && hero->getRect().x >= SCREEN_WIDTH - hero->getRect().w/2) {
				Mix_PlayMusic(mHomeMusic, -1);
				mState = WIN;
			}
			if(!boss->checkIsDestroyed() && !hero->checkIsDestroyed()) {
				hero->handleAction(event, renderer);
			}
		}
		break;

	case HIGHSCORE:
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
				if(userName.size() < 20) {
					userName.push_back(event.key.keysym.sym - SDLK_a + 'a');
					userNameText->loadText(renderer, font, userName);
				}
			}
			else if(event.key.keysym.sym == SDLK_BACKSPACE) {
				if(userName.size() != 0) {
					userName.pop_back();
					userNameText->loadText(renderer, font, userName);
				}
			}
			if(event.key.keysym.sym == SDLK_RETURN) {
				Mix_PlayChannel(-1, mClickMusic, 1);
				addHighScore(renderer, hero->getScore(), userName);
				userName = "";
				userNameText->loadText(renderer, font, userName);
				mState = HIGHSCORE1;
			}
		}
		break;

	case HIGHSCORE1:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
			case SDLK_UP:
			case SDLK_LEFT:
			case SDLK_RIGHT:
				mState = HIGHSCORE2;
				break;
			}
		}
		break;

	case HIGHSCORE2:
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			Mix_PlayChannel(-1, mClickMusic, 1);
			mState = LOSE;
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
			Mix_PlayChannel(-1, mClickMusic, 1);
			mState = HOME2;
			Mix_PlayMusic(mIntroMusic, -1);
			mYVal = -1; mXVal = 0;
		}
		break;

	case HOME2:
		if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) || mRect.y <= -SCREEN_HEIGHT) {
			Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				mState = LEVEL;
				setUpLevel(renderer, mLevel);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				mState = LEVEL;
				mLevel = 1;
				setUpLevel(renderer, mLevel);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				mState = START;
				mLevel = 1;
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				if (hero->getCoin() >= 20) {
					hero->setCoin(hero->getCoin() - 20);
					hero->addSkill(SUPER_SKILL);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
			case SDLK_UP:
				mState = WIN2;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				Mix_PlayChannel(-1, mClickMusic, 1);
				mState = LEVEL;
				mLevel++;
				setUpLevel(renderer, mLevel);
				break;
			}
		}
		break;

	case WIN2:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
			case SDLK_UP:
				mState = WIN1;
				break;
			case SDLK_LEFT:
			case SDLK_RIGHT:
				break;
			case SDLK_RETURN:
				Mix_PlayChannel(-1, mClickMusic, 1);
				mLevel = 1;
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
				mState = WIN2;
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				if (hero->getCoin() >= 20 && hero->getNormalHp() < 110) {
					hero->setCoin(hero->getCoin() - 20);
					hero->setNormalHp(hero->getNormalHp() + 10);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				if (hero->getCoin() >= 20 && hero->getDef() < 6) {
					hero->setCoin(hero->getCoin() - 20);
					hero->setNormalDef(hero->getNormalDef() + 1);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
				if (hero->getCoin() >= 20 && hero->getNormalAtk() < 20 + 12) {
					hero->setCoin(hero->getCoin() - 20);
					hero->setNormalAtk(hero->getNormalAtk() + 2);
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
				Mix_PlayChannel(-1, mClickMusic, 1);
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
	mClickMusic = Mix_LoadWAV("Music_Folder/click.wav");
	mGameOverMusic = Mix_LoadWAV("Music_Folder/game_over.wav");;

	font = TTF_OpenFont("Font_Folder/font3.ttf", 30);
	userNameText = new Text(); userNameText->setRect(700, 200); userNameText->loadText(renderer, font, userName);
	mLevel = 1;
	mLevelText = new Text(); mLevelText->setRect(500, 0); mLevelText->loadText(renderer, font, "LEVEL : " + std::to_string(mLevel));
	mState = GameState::HOME;

	std::ifstream file("highscore.txt");
	std::string user;
	int score;
	
	for(int i = 0; i < 10; i++) {
		file >> user; file >> score;
		mHighScores.push_back(std::pair<std::string, int> (user, score));
		Text *t = new Text();
		t->setRect(100, i*30 + 100);
		t->loadText(renderer, font, user + " : " + std::to_string(score));
		mHighScoreTexts.push_back(t);	
	}	
	file.close();
}

void Game::updateObject(SDL_Renderer* renderer) {
	if(hero->checkIsDestroyed()) {
		return;
	}
	if(boss->checkIsDestroyed()) {
		hero->mXVal = 5; hero->mYVal = 0; hero->handleMove(); hero->handleState(renderer);	
		if(boss->getIsAppear()) {
			hero->setCoin(hero->getCoin() + 10);
			hero->setScore(hero->getScore() + 10);
			Mix_PlayChannel(-1, mWinMusic, 0);
			boss->setIsAppear(false);
		}
		return;
	}
	handleCollision(renderer);
	hero->handleMove(); hero->handleState(renderer); hero->handleSkill(); hero->handleEffect(); 
	handleEffect();
	for (int i = 0; i < int(bots.size()); i++) {
		if (bots[i]->getIsAppear()) {
			bots[i]->handleAction(renderer); bots[i]->handleMove(); bots[i]->handleState(renderer); bots[i]->handleSkill();
		}
	}
	if (boss->getIsAppear()) {
		boss->handleAction(renderer); boss->handleMove(); boss->handleState(renderer); boss->handleSkill();
	}
	else if(SDL_GetTicks64() - mBossTime > 30000) {
		boss->setIsAppear(true);
	}
	for (int i = 0; i < int(items.size()); i++) {
		items[i]->handleMove(); 
		if (items[i]->getRect().x <= 0) {
			delete items[i];
			items.erase(items.begin() + i);
		}
	}
}

void Game::handleCollision(SDL_Renderer* renderer) {
	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {
			handleCollide(hero, bots[j], hero->getNormalHp()/2, bots[j]->getNormalHp());

			if (bots[j]->checkIsDestroyed()) {
				hero->setScore(hero->getScore() + 2);
				Mix_PlayChannel(-1, mBonkMusic, 0);

				for(int i = 0; i < 3; i++) {
					Item* newItem = new Item();
					newItem->loadImage(renderer, static_cast<ItemType>(rand()%int(ITEM_PATHS.size())));
					newItem->setRect(bots[j]->getRect().x + 10, bots[j]->getRect().y + bots[j]->getRect().h / 2);
					newItem->mXVal = -3; newItem->mYVal = i-1;
					items.push_back(newItem);
				}
			}
		}
	}

	if (boss->getIsAppear()) {
		handleCollide(hero, boss, hero->getNormalHp(), 0);
	}

	for (int i = 0; i < int(items.size()); i++) {
		if(items[i]->getRect().x < 0) {
			if(items[i] != nullptr) {
				delete items[i];
				items.erase(items.begin() + i);
			}
		}
		else if (hero->getHp() > 0 && checkCollision(hero, items[i])) {
			Mix_PlayChannel(-1, mItemMusic, 0);
			switch (items[i]->getItemType()) {
			case HP_ITEM:
				hero->setHp(hero->getHp() + 10);
				break;

			case BULLET_ITEM:
				if (hero->getNormalBullet() < 5) {
					hero->setNormalBullet(hero->getNormalBullet() + 1);
				}
				break;
			case BLUE_BULLET_ITEM:
			case GREEN_BULLET_ITEM:
			case RED_BULLET_ITEM:
				if (int(hero->getCurrentBullet()) == int(items[i]->getItemType())) {
					hero->setNormalBullet(hero->getNormalBullet() + 1);
					if (hero->getNormalBullet() >= 5) {
						hero->setNormalBullet(5);
					}
				}
				else {
					hero->setCurrentBullet(static_cast<BulletType>(items[i]->getItemType()));
					hero->setNormalBullet(1);
				}
				break;
			case COIN_ITEM:
				hero->setCoin(hero->getCoin() + 1);				
				break;			
			case MAGNET_ITEM:
				hero->useEffect(MAGNET_EFFECT, 30);
				break;			
			case SPEED_UP_ITEM:
				hero->useEffect(SPEED_UP_EFFECT, 30);
				break;
			case SPEED_DOWN_ITEM:
				hero->useEffect(SPEED_DOWN_EFFECT, 15);
				break;
			case ARMOR_ITEM:
				hero->useEffect(ARMOR_EFFECT, 15);
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
		for(auto &it : items) {
			if(it->getItemType() == COIN_ITEM) {
				int x1 = hero->getRect().x + hero->getRect().w/2, y1 = hero->getRect().y + hero->getRect().h/2;
				int x2 = it->getRect().x - x1, y2 = it->getRect().y - y1;
				if(std::abs(x2) > std::abs(y2)) {
					it->mXVal = (x2 < 0) ? 5 : -5;
					it->mYVal = y2 * it->mXVal / x2;
				}
				else {
					it->mYVal = (y2 < 0) ? 5 : -5;
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

	for(auto &it : items) {
		delete it;
		it = nullptr;
	}
	items = {};
}

void Game::setUpLevel(SDL_Renderer* renderer, int level) {
	if(level == 1) {
		hero->setScore(0);
		hero->setNormalBullet(1);
		hero->setCurrentBullet(GREEN_BALL);
	}

	// load background level moi 
	if(mTextures[LEVEL]) {
		SDL_DestroyTexture(mTextures[LEVEL]);
	}

	std::string path = "Image_Folder/Background/Level/" + std::to_string(1 + rand()%33) + ".png";
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	mTextures[LEVEL] = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	mRect.w = loadedSurface->w;
	mRect.h = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
	 
	mLevelText->loadText(renderer, font, "LEVEL : " + std::to_string(mLevel));

	if(level <= 3) 
		for(int i = 0; i < int(bots.size()); i++) 
			bots[i]->setIsAppear((i < 2) ? true : false);
	else if(level <= 9) 
		for(int i = 0; i < int(bots.size()); i++)
			bots[i]->setIsAppear((i < level) ? true : false);

	mBossTime = SDL_GetTicks64();
	this->restart(renderer);
	Mix_PlayMusic(mGameMusic, -1);
}

void Game::addHighScore(SDL_Renderer* renderer, int score, std::string user) {
	int i = 0;
	while(i < int(mHighScores.size()) && mHighScores[i].second > score)
		i++;
	for(int j = mHighScores.size() - 1; j > i; j--)
		mHighScores[j] = mHighScores[j-1];
	if(i < int(mHighScores.size()))
		mHighScores[i] = std::pair<std::string, int> (user, score);
	for(int i = 0; i < int(mHighScoreTexts.size()); i++)
		mHighScoreTexts[i]->loadText(renderer, font, mHighScores[i].first + " : " + std::to_string(mHighScores[i].second));
}

void Game::renderHighScore(SDL_Renderer* renderer) {
	for(int i = 0; i < int(mHighScoreTexts.size()); i++)
		mHighScoreTexts[i]->render(renderer);
}