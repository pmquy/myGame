#include "Background.h"
#include "Character.h"
#include "Bot.h"
#include "Text.h"

bool isQuit = false;

void Init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	gWindow = SDL_CreateWindow("minhquy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
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
	hero.loadImage(gRenderer, "image_folder/hero.png");
	hero.setRect(0, 200);

	Bot bot1;
	bot1.loadImage(gRenderer, "image_folder/plane.png");
	bot1.setRect(200, 200);


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
		hero.handleBulletMove();
		hero.render(gRenderer);
	


		bot1.handleMove();
		bot1.render(gRenderer);

		for (int i = 0; i < int(hero.getBulletList().size()); i++) {
			if (checkConllision(bot1, *hero.getBulletList()[i])) {
				bot1.getDamage(hero.getAttack());
				hero.getBulletList()[i]->setIsMove(false);
			}
		}
		
		SDL_RenderPresent(gRenderer);
	}


	Close();
	return 0;
}