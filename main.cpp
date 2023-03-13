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

void loadResource() {
	
	std::vector<std::string> listName;

	listName = { "Image_Folder/background/Level_1.jpg", "Image_Folder/background/Lose2.png"};
	background.loadImage(gRenderer, listName);
	background.setRect(0, 0, 1200, 600);

	listName = { "Image_Folder/Airplane/Fighter/Idle.png", "Image_Folder/Airplane/Fighter/Destroyed.png", "Image_Folder/Airplane/Fighter/Attack_1.png" };
	hero.loadImage(gRenderer, listName);
	hero.setRect(0, 200);
	hero.setAttack(20);
	
	listName = { "Image_Folder/Airplane/Bomber/Idle.png", "Image_Folder/Airplane/Bomber/Destroyed.png", "Image_Folder/Airplane/Bomber/Attack_1.png" };
	bot1.loadImage(gRenderer, listName);
	bot1.setRect(SCREEN_WIDTH, 100);
	bot1.setAttack(5);

	listName = { "Image_Folder/Airplane/Bomber/Idle.png", "Image_Folder/Airplane/Bomber/Destroyed.png", "Image_Folder/Airplane/Bomber/Attack_1.png" };
	bot2.loadImage(gRenderer, listName);
	bot2.setRect(SCREEN_WIDTH, 300);
	bot2.setAttack(5);

	listName = { "Image_Folder/Airplane/Corvette/Idle.png", "Image_Folder/Airplane/Corvette/Destroyed.png", "Image_Folder/Airplane/Corvette/Attack_1.png" };
	boss.loadImage(gRenderer, listName);
	boss.setAttack(5);
}


void handleColision() {

	for (int i = 0; i < int(hero.getBulletList().size()); i++) {
		if (checkConllision(bot1, *hero.getBulletList()[i])) {
			bot1.getDamage(hero.getAttack());
			hero.getBulletList()[i]->setIsMove(false);
		}
	}

	for (int i = 0; i < int(hero.getBulletList().size()); i++) {
		if (checkConllision(bot2, *hero.getBulletList()[i])) {
			bot2.getDamage(hero.getAttack());
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
}

void Init() {
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
	srand(time(0));
	Init();
	loadResource();

	while (!isQuit) {

		background.handleMove();
		background.handleState(hero.checkIsDestroyed());
		background.render(gRenderer);


		while (SDL_PollEvent(&gEvent)) {

			SDL_GetMouseState(&gMouse.first, &gMouse.second);

			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
			else if (gEvent.type == SDL_MOUSEBUTTONDOWN && hero.checkIsDestroyed() && gMouse.first >= 560 && gMouse.first <= 630 && gMouse.second >= 230 && gMouse.second <= 260) {
				hero.reborn();
			}
			hero.handleAction(gEvent, gRenderer);
		}

		if (!hero.checkIsDestroyed()) {

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
			
		}
	
		
		SDL_RenderPresent(gRenderer);
	}

	Close();
	return 0;
}