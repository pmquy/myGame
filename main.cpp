#include "Background.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"

bool isQuit = false;
std::pair<int, int> gMouse;
BackgroundType gState = BackgroundType::START;
int score = 0;
Background background;
Character hero;
Bot bot1;
Bot bot2;
Bot bot3;
Text gScore;
Text gCoin;



void loadResource() {
	background.loadImage(gRenderer, BACKGROUND_PATHS);
	
	hero.loadImage(gRenderer, HERO_PATHS1);
	
	bot1.loadImage(gRenderer, BOT1_PATHS);
	bot1.setShipType(ShipType::SHIP1);

	bot2.loadImage(gRenderer, BOT2_PATHS);
	bot2.setShipType(ShipType::SHIP1);

	bot3.loadImage(gRenderer, BOT3_PATHS);
	bot3.setAttack(5);
	bot3.setShipType(ShipType::SHIP2);
	
	gScore.setRect(0, 0);
	gCoin.setRect(0, 50);

	collisionMusic = Mix_LoadWAV("Music_Folder/music1.wav");
	backgroundMusic = Mix_LoadWAV("Music_Folder/music2.wav");
	
}



void handleColision() {
	for (int i = 0; i < int(hero.getBulletList().size()); i++) {
		if (checkConllision(bot1, *hero.getBulletList()[i])) {
			bot1.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
		}
		if (checkConllision(bot2, *hero.getBulletList()[i])) {
			bot2.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
		}
		if (checkConllision(bot3, *hero.getBulletList()[i])) {
			bot3.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
		}
	}
	for (int i = 0; i < int(bot1.getBulletList().size()); i++) {
		if (checkConllision(hero, *bot1.getBulletList()[i])) {
			hero.getDamage(bot1.getAttack());
			bot1.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
		}
	}
	for (int i = 0; i < int(bot2.getBulletList().size()); i++) {
		if (checkConllision(hero, *bot2.getBulletList()[i])) {
			hero.getDamage(bot2.getAttack());
			bot2.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
		}
	}
	for (int i = 0; i < int(bot3.getBulletList().size()); i++) {
		if (checkConllision(hero, *bot3.getBulletList()[i])) {
			hero.getDamage(bot3.getAttack());
			bot3.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
		}
	}
	if (checkConllision(hero, bot1) && bot1.getHeart() != 0) {
		hero.getDamage(10);
		bot1.getDamage(1000);
	}
	if (checkConllision(hero, bot2) && bot2.getHeart() != 0) {
		hero.getDamage(10);
		bot2.getDamage(1000);
	}
	if (checkConllision(hero, bot3) && bot3.getHeart() != 0) {
		hero.getDamage(10);
		bot3.getDamage(1000);
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
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
}


int main(int argc, char* argv[]) {
	Init();
	loadResource();

	while (!isQuit) {
		//Mix_PlayChannel(-1, backgroundMusic, 0);
		background.render(gRenderer);
		background.handleState(gState, gRenderer, gMouse, gEvent, &hero);
		
		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
			background.handleState(gState, gRenderer, gMouse, gEvent, &hero);
			SDL_GetMouseState(&gMouse.first, &gMouse.second);
			if (gState == LEVEL_1 || gState == LEVEL_2) {
				hero.handleAction(gEvent, gRenderer);
			}
		}

		switch (gState) {
		
		case UPGRADE:
		case SHOP:
			gCoin.loadNumber(gRenderer, hero.getCoin(), "Coin");
			gCoin.render(gRenderer);
			break;
		case START:
		case DEAD:
		case VICTORY:
			break;
		case LEVEL_1:
		case LEVEL_2:
			while (SDL_PollEvent(&gEvent)) {
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
			}
			gScore.loadNumber(gRenderer, score, "Score");
			gScore.render(gRenderer);

			gCoin.loadNumber(gRenderer, hero.getCoin(), "Coin");
			gCoin.render(gRenderer);

			handleColision();

			background.handleMove(); hero.handleMove(); bot1.handleMove(); bot2.handleMove(); bot3.handleMove();
		
			bot1.handleAction(gRenderer); bot2.handleAction(gRenderer); bot3.handleAction(gRenderer);
			
			hero.handleState(gRenderer); bot1.handleState(gRenderer); bot2.handleState(gRenderer); bot3.handleState(gRenderer);
		
			hero.render(gRenderer, 1); bot1.render(gRenderer, -1); bot2.render(gRenderer, -1); bot3.render(gRenderer, -1);
				
			if (hero.checkIsDestroyed()) {
				bot1.reborn(); bot2.reborn(); hero.reborn(); bot3.reborn(); hero.reborn();
				gState = DEAD;
			}
			if (bot1.checkIsDestroyed()) {
				score++;
				hero.setCoin(hero.getCoin() + 1);
			}
			if (bot2.checkIsDestroyed()) {
				score++;
				hero.setCoin(hero.getCoin() + 1);
			}
			if (bot3.checkIsDestroyed()) {
				score+=2;
				hero.setCoin(hero.getCoin() + 2);
			}
			if (score >= 4) {
				gState = VICTORY;
				score = 0;
				bot1.reborn(); bot2.reborn(); hero.reborn(); bot3.reborn();
			}
			break;
		}
		SDL_RenderPresent(gRenderer);
	}
	Close();
	return 0;
}

