#include "Background.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"

bool isQuit = false;
Background background;
Character hero;
Bot bot1;
Bot bot2;


void loadResource() {

	background.loadImage(gRenderer, "Image_Folder/background/Level_1.jpg", "Image_Folder/background/Lose.png");
	background.setRect(0, 0, 1200, 600);

	hero.loadImage(gRenderer, "Image_Folder/Airplane/Fighter/Idle.png", "Image_Folder/Airplane/Fighter/Destroyed.png", "Image_Folder/Airplane/Fighter/Attack_1.png");
	hero.setRect(0, 200);
	hero.setAttack(20);

	bot1.loadImage(gRenderer, "Image_Folder/Airplane/Corvette/Idle.png", "Image_Folder/Airplane/Corvette/Destroyed.png", "Image_Folder/Airplane/Corvette/Attack_1.png");
	bot1.setRect(SCREEN_WIDTH, 100);
	bot1.setAttack(5);


	bot2.loadImage(gRenderer, "Image_Folder/Airplane/Corvette/Idle.png", "Image_Folder/Airplane/Corvette/Destroyed.png", "Image_Folder/Airplane/Corvette/Attack_1.png");
	bot2.setRect(SCREEN_WIDTH, 300);
	bot2.setAttack(5);

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
	Init();
	loadResource();

	while (!isQuit) {

		background.handleMove();
		background.handleState(hero.checkIsDestroyed());
		background.render(gRenderer);

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
			else if (gEvent.type == SDL_MOUSEBUTTONDOWN && hero.checkIsDestroyed()) {
				hero.reborn();
			}
			hero.handleAction(gEvent, gRenderer);
		}

		if (!hero.checkIsDestroyed()) {

			hero.handleMove();
			bot1.handleMove();
			bot2.handleMove();

			bot1.handleAction(gRenderer);
			bot2.handleAction(gRenderer);

			hero.handleState();
			bot1.handleState();
			bot2.handleState();

			handleColision();

			hero.render(gRenderer, 1);
			bot1.render(gRenderer, -1);
			bot2.render(gRenderer, -1);
		}
	
		
		SDL_RenderPresent(gRenderer);
	}

	Close();
	return 0;
}