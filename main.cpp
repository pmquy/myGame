#include "Background.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"
#include "Boss.h"

bool isQuit = false;
Background background;
Character hero;
Bot bot1;
Bot bot2;
Boss boss;
std::pair<int, int> gMouse;
BKG gState = BKG::START;


void loadResource() {
	std::vector<std::string> listName;

	listName = { "Image_Folder/Background/Lose2.png", "Image_Folder/Background/Level_1.jpg", "Image_Folder/dead.png", "Image_Folder/shop.png"};
	background.loadImage(gRenderer, listName);
	background.setRect(0, 0, 1200, 600);

	listName = { "Image_Folder/Airplane/Fighter/Idle.png", "Image_Folder/Airplane/Fighter/Destroyed.png", "Image_Folder/Airplane/Fighter/Attack_1.png" };
	hero.loadImage(gRenderer, listName);
	hero.setRect(0, 200);
	hero.setAttack(20);
	
	listName = { "Image_Folder/Airplane/Bomber/Idle.png", "Image_Folder/Airplane/Bomber/Destroyed.png", "Image_Folder/Airplane/Bomber/Attack_1.png" };
	bot1.loadImage(gRenderer, listName);
	bot1.setRect(SCREEN_WIDTH, 100);
	bot1.setAttack(1);

	listName = { "Image_Folder/Airplane/Bomber/Idle.png", "Image_Folder/Airplane/Bomber/Destroyed.png", "Image_Folder/Airplane/Bomber/Attack_1.png" };
	bot2.loadImage(gRenderer, listName);
	bot2.setRect(SCREEN_WIDTH, 300);
	bot2.setAttack(1);

	listName = { "Image_Folder/Airplane/Corvette/Idle.png", "Image_Folder/Airplane/Corvette/Destroyed.png", "Image_Folder/Airplane/Corvette/Attack_1.png" };
	boss.loadImage(gRenderer, listName);
	boss.setAttack(5);
	boss.setHeart(100);
}


void handleColision() {

	for (int i = 0; i < int(hero.getBulletList().size()); i++) {
		if (checkConllision(bot1, *hero.getBulletList()[i])) {
			bot1.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
		}

		if (checkConllision(bot2, *hero.getBulletList()[i])) {
			bot2.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
		}
		
		if (checkConllision(boss, *hero.getBulletList()[i])) {
			boss.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
		}
	}
	for (int i = 0; i < int(bot1.getBulletList().size()); i++) {
		if (checkConllision(hero, *bot1.getBulletList()[i])) {
			hero.getDamage(bot1.getAttack());
			bot1.getBulletList()[i]->setIsMove(false);
		}
	}
	for (int i = 0; i < int(bot2.getBulletList().size()); i++) {
		if (checkConllision(hero, *bot2.getBulletList()[i])) {
			hero.getDamage(bot2.getAttack());
			bot2.getBulletList()[i]->setIsMove(false);
		}
	}
	for (int i = 0; i < int(boss.getBulletList().size()); i++) {
		if (checkConllision(hero, *boss.getBulletList()[i])) {
			hero.getDamage(boss.getAttack());
			boss.getBulletList()[i]->setIsMove(false);
		}
	}
}

void Init() {
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
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
}


int main(int argc, char* argv[]) {
	Init();
	loadResource();
	
	while (!isQuit) {

		background.handleState(gState, gRenderer, gMouse);
		background.render(gRenderer);
		

		switch (gState) {
		case START:
			background.render(gRenderer);
			while (SDL_PollEvent(&gEvent)) {
				SDL_GetMouseState(&gMouse.first, &gMouse.second);
				if (gEvent.type == SDL_MOUSEBUTTONDOWN && gMouse.first >= 560 && gMouse.first <= 620 && gMouse.second >= 220 && gMouse.second <= 260) {
					gState = LEVEL_1;
				}
				if (gEvent.type == SDL_MOUSEBUTTONDOWN && gMouse.first >= 560 && gMouse.first <= 620 && gMouse.second >= 280 && gMouse.second <= 320) {
					gState = SHOP;
				}
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
			}
			break;

		case LEVEL_1:
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
		
			hero.handleState();
			bot1.handleState();
			bot2.handleState();
			boss.handleState();
		
			handleColision();
		
			hero.render(gRenderer, 1);
			bot1.render(gRenderer, -1);
			bot2.render(gRenderer, -1);
			boss.render(gRenderer, -1);
				
			if (hero.checkIsDestroyed()) {
				gState = DEAD;
			}
			break;

		case DEAD:
			while (SDL_PollEvent(&gEvent)) {
				SDL_GetMouseState(&gMouse.first, &gMouse.second);
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
				else if (gState == DEAD && gEvent.type == SDL_MOUSEBUTTONDOWN && gMouse.first >= 560 && gMouse.first <= 620 && gMouse.second >= 220 && gMouse.second <= 260) {
					gState = LEVEL_1;
				}
				else if (gEvent.type == SDL_MOUSEBUTTONDOWN && gMouse.first >= 560 && gMouse.first <= 620 && gMouse.second >= 280 && gMouse.second <= 320) {
					gState = START;
				}
			}
			break;

		case SHOP:
			while (SDL_PollEvent(&gEvent)) {
				if (gEvent.type == SDL_QUIT) {
					isQuit = true;
				}
			}
			break;
		}

		SDL_RenderPresent(gRenderer);
	}

	Close();
	return 0;
}
