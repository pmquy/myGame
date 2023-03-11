#include "Background.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"

bool isQuit = false;

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

	Background background;
	background.loadImage(gRenderer, "image_folder/bg.jpg");
	background.setRect(0, 0, 1200, 600);

	Character hero;
	hero.loadImage(gRenderer, "image_folder/airplane/Fighter/Idle.png", "image_folder/airplane/Fighter/Destroyed.png", "image_folder/airplane/Fighter/Attack_1.png");
	hero.setRect(0, 200);
	hero.setAttack(20);

	Bot bot1;
	bot1.loadImage(gRenderer, "image_folder/airplane/Corvette/Idle.png", "image_folder/airplane/Corvette/Destroyed.png", "image_folder/airplane/Corvette/Attack_1.png");
	bot1.setRect(SCREEN_WIDTH, 100);
	bot1.getBulletList()[0]->loadImage(gRenderer, "image_folder/airplane/Corvette/Charge_1.png");
	bot1.getBulletList()[0]->setIsMove(true);


	Bot bot2;
	bot2.loadImage(gRenderer, "image_folder/airplane/Corvette/Idle.png", "image_folder/airplane/Corvette/Destroyed.png", "image_folder/airplane/Corvette/Attack_1.png");
	bot2.setRect(SCREEN_WIDTH, 300);
	bot2.getBulletList()[0]->loadImage(gRenderer, "image_folder/airplane/Corvette/Charge_1.png");
	bot2.getBulletList()[0]->setIsMove(true);

	while (!isQuit) {

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
			hero.handleAction(gEvent, gRenderer);
		}

		background.handleMove();
		background.render(gRenderer);

		hero.handleMove();
		hero.render(gRenderer);	

		bot1.handleMove();
		bot1.handleState();
		bot1.render(gRenderer);

		bot2.handleMove();
		bot2.handleState();
		bot2.render(gRenderer);


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

		SDL_RenderPresent(gRenderer);
	}

	Close();
	return 0;
}