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
	hero.setRect(0, 200, 64, 91);

	Bot bot1;
	bot1.loadImage(gRenderer, "image_folder/threat.png");

	Text fps;
	fps.loadText(gRenderer, "vipfjdkfj");
	fps.setRect(0, 0);
	

	while (!isQuit) {

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
			hero.handleAction(gEvent);
		}

		background.handleMove();
		background.render(gRenderer);

		SDL_Rect temp = { 0,0,300, 100 };



		hero.handleMove();
		hero.render(gRenderer);


		bot1.handleMove();
		bot1.render(gRenderer);

		fps.render(gRenderer);
		
		
		SDL_RenderPresent(gRenderer);

	}


	Close();
	return 0;
}