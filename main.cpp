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
Bot boss;
Text gScore;
Text gCoin;



void loadResource() {


	background.loadImage(gRenderer, BACKGROUND_PATHS);
	background.setRect(0, 0, 1200, 600);

	hero.loadImage(gRenderer, HERO_PATHS1);
	hero.setRect(0, 200);
	hero.setAttack(20);
	
	bot1.loadImage(gRenderer, BOT1_PATHS);
	bot1.setRect(SCREEN_WIDTH, 100);
	bot1.setAttack(1);
	bot1.setShipType(ShipType::SHIP1);

	bot2.loadImage(gRenderer, BOT2_PATHS);
	bot2.setRect(SCREEN_WIDTH, 300);
	bot2.setAttack(1);
	bot2.setShipType(ShipType::SHIP1);

	boss.loadImage(gRenderer, BOT3_PATHS);
	boss.setAttack(5);
	boss.setHeart(100);
	boss.setShipType(ShipType::SHIP2);
	
	gScore.setRect(0, 0);
	gCoin.setRect(0, 100);

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
		
		if (checkConllision(boss, *hero.getBulletList()[i])) {
			boss.getDamage(hero.getAttack());
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
	for (int i = 0; i < int(boss.getBulletList().size()); i++) {
		if (checkConllision(hero, *boss.getBulletList()[i])) {
			hero.getDamage(boss.getAttack());
			boss.getBulletList()[i]->setIsMove(false);
			//Mix_PlayChannel(-1, collisionMusic, 0);
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
		
		Mix_PlayChannel(-1, backgroundMusic, 0);
		background.render(gRenderer);

		switch (gState) {

		case START:
			background.render(gRenderer);
			while (SDL_PollEvent(&gEvent)) {

				SDL_GetMouseState(&gMouse.first, &gMouse.second);
				background.handleState(gState, gRenderer, gMouse, gEvent);

				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
			}
			background.handleState(gState, gRenderer, gMouse, gEvent);
			break;

		case LEVEL_1:
		case LEVEL_2:
			
			gScore.loadNumber(gRenderer, score, "Score");
			gScore.setRect(0, 0);
			gScore.render(gRenderer);
			
			gCoin.loadNumber(gRenderer, hero.getCoin(), "Coin");
			gCoin.setRect(0, 100);
			gCoin.render(gRenderer);


			while (SDL_PollEvent(&gEvent)) {
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
				hero.handleAction(gEvent, gRenderer);
			}

			background.handleMove();
			hero.handleMove();
			bot1.handleMove();
			bot2.handleMove();
			boss.handleMove();
		
			bot1.handleAction(gRenderer);
			bot2.handleAction(gRenderer);
			boss.handleAction(gRenderer);
			
			hero.handleState(gRenderer);
			bot1.handleState(gRenderer);
			bot2.handleState(gRenderer);
			boss.handleState(gRenderer);
		
			handleColision();
		
			hero.render(gRenderer, 1);
			bot1.render(gRenderer, -1);
			bot2.render(gRenderer, -1);
			boss.render(gRenderer, -1);
				
			if (hero.checkIsDestroyed()) {
				bot1.reborn();
				bot2.reborn();
				hero.reborn();
				boss.reborn();
				hero.reborn();
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
			if (boss.checkIsDestroyed()) {
				score+=2;
				hero.setCoin(hero.getCoin() + 2);
			}

			if (score >= 4) {
				gState = VICTORY;
				score = 0;
				bot1.reborn();
				bot2.reborn();
				hero.reborn();
				boss.reborn();
			}

			background.handleState(gState, gRenderer, gMouse, gEvent);
			break;

		case DEAD:
			while (SDL_PollEvent(&gEvent)) {
				SDL_GetMouseState(&gMouse.first, &gMouse.second);
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
				background.handleState(gState, gRenderer, gMouse, gEvent);
			}
			background.handleState(gState, gRenderer, gMouse, gEvent);
			break;

		case SHOP:
			while (SDL_PollEvent(&gEvent)) {
				SDL_GetMouseState(&gMouse.first, &gMouse.second);
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
				background.handleState(gState, gRenderer, gMouse, gEvent, &hero);
			}
			background.handleState(gState, gRenderer, gMouse, gEvent, &hero);
			break;

		case VICTORY:
			while (SDL_PollEvent(&gEvent)) {
				SDL_GetMouseState(&gMouse.first, &gMouse.second);
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
				background.handleState(gState, gRenderer, gMouse, gEvent);
			}
			background.handleState(gState, gRenderer, gMouse, gEvent);
			break;
		}
		
		SDL_RenderPresent(gRenderer);
	}

	Close();
	return 0;
}
