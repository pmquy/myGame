#include "Background.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"

bool isQuit = false;
std::pair<int, int> gMouse;
int score = 0;
Background game;
Character hero;
std::vector<Bot*> bots(6, nullptr);
Text gScore;
Text gCoin;
BackgroundType oldState = START;


void loadResource() {
	game.loadImage(gRenderer, GAME_PATHS);
	hero.loadImage(gRenderer, HERO_PATHS1);


	for (int i = 0; i < int(bots.size()); i++) {
		Bot* newBot = new Bot();
		int t = rand() % 2;
		if (t == 0) {
			newBot->loadImage(gRenderer, BOT1_PATHS);
			newBot->setShipType(ShipType::SHIP1);
		}
		else if (t == 1) {
			newBot->loadImage(gRenderer, BOT2_PATHS);
			newBot->setShipType(ShipType::SHIP2);
		}
		if (i <= 1) {
			newBot->setIsAppear(true);
		}
		else {
			newBot->setIsAppear(false);
		}
		bots[i] = newBot;
	}
	
	gScore.setRect(0, 0);
	gCoin.setRect(0, 50);
	gFont = TTF_OpenFont("Font_Folder/font2.ttf", 30);
	gameMusic = Mix_LoadMUS("Music_Folder/music.mp3");
	bonk = Mix_LoadWAV("Music_Folder/bonk.wav");
	Mix_VolumeMusic(128);
}

void handleColision() {

	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {

			for (int i = 0; i < int(hero.getBulletList().size()); i++) {
				if (checkConllision(bots[j], hero.getBulletList()[i])) {
					bots[j]->getDamage(hero.getAttack());
					hero.getBulletList()[i]->setIsAppear(false);	
				}
			}

			for (int i = 0; i < int(bots[j]->getBulletList().size()); i++) {
				if (bots[j]->getHeart() != 0 && checkConllision(&hero, bots[j]->getBulletList()[i])) {
					hero.getDamage(bots[j]->getAttack());
					bots[j]->getBulletList()[i]->setIsAppear(false);
				}
			}

			if (checkConllision(&hero, bots[j]) && bots[j]->getHeart() != 0) {
				bots[j]->getDamage(1000);
				hero.getDamage(30);
			}
		}
	}

}

void Init() {
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	gWindow = SDL_CreateWindow("minhquy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void Close() {
	Mix_FreeMusic(gameMusic);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
}

void gameLoop() {
	
	Mix_PlayMusic(gameMusic, -1);

	
	while (!isQuit) {

		game.render(gRenderer);
		game.handleState(gRenderer, gMouse, gEvent, &hero, oldState, bots);

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
			SDL_GetMouseState(&gMouse.first, &gMouse.second);
			game.handleState(gRenderer, gMouse, gEvent, &hero, oldState, bots);
			if (game.getState() != START && game.getState() != SHOP && game.getState() != DEAD && game.getState() != UPGRADE && game.getState() != VICTORY) {
				hero.handleAction(gEvent, gRenderer);
			}
		}	

		switch (game.getState()) {
		
		case UPGRADE:
		case SHOP:
			gCoin.loadText(gRenderer, gFont, "Coin : " + std::to_string(hero.getCoin()));
			gCoin.render(gRenderer);
			break;
		case START:
		case DEAD:
		case VICTORY:
			break;
		case LEVEL_1:
		case LEVEL_2:
		case LEVEL_3:
		case LEVEL_4:
		case LEVEL_5:
			game.handleMove(); 
			oldState = game.getState();
			game.handleLogic(gRenderer, &hero, bots);

			gScore.loadText(gRenderer, gFont, "Score : " + std::to_string(hero.getScore())); gScore.render(gRenderer);
			gCoin.loadText(gRenderer, gFont, "Coin : " + std::to_string(hero.getCoin())); gCoin.render(gRenderer);
			hero.handleMove(); 
			hero.handleState(gRenderer);
			hero.handleSkill();
			hero.renderText(gRenderer, gFont); 
			hero.render(gRenderer, 1);
			
			
			for (int i = 0; i < int(bots.size()); i++) {
				if (bots[i]->getIsAppear()) {
					bots[i]->handleAction(gRenderer); bots[i]->handleMove(); bots[i]->handleState(gRenderer); bots[i]->render(gRenderer, -1);
				}
				if (bots[i]->checkIsDestroyed()) {
					Mix_PlayChannel(-1, bonk, 0);
					hero.setScore(hero.getScore() + 2);
					hero.setCoin(hero.getCoin() + 3);
				}
			}

			handleColision();
			break;
		}

		SDL_RenderPresent(gRenderer);
		
		if (isQuit) {
			return;
		}
	}
}


int main(int argc, char* argv[]) {
	Init();
	loadResource();
	gameLoop();
	Close();
	return 0;
}

