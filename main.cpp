#include "background.h"

bool isQuit = false;

void Init() {
	SDL_Init(SDL_INIT_EVERYTHING);
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
}


int main(int argc, char* argv[]) {

	Init();

	Background background;
	background.loadImage(gRenderer, "bg.jpg");
	background.setRect(0, 0, 1200, 600);

	BaseClass character;
	character.loadImage(gRenderer, "character.png");
	character.setRect(100, 250, 1200/8, 573/3);

	SDL_Rect clips[8];
	for (int i = 0; i < 8; i++) {
		clips[i].x = i * 1200 / 8;
		clips[i].y = 0;
		clips[i].w = 1200 / 8;
		clips[i].h = 573 / 3;
	}
	int j = 0;

	UINT32 startTime = 0;
	int ii = 0;

	while (!isQuit) {
		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
		}
		
		background.handleMove();
		background.render(gRenderer);

		character.setRect(ii, 250);
		character.render(gRenderer, &clips[j]);
		UINT32 time = SDL_GetTicks() - startTime;
		if (time >= 200) {
			j++;
			if (j == 8) j = 0;
			startTime = SDL_GetTicks();
			ii += 20;
			if (ii >= 1000) ii = 0;
		}
		SDL_Delay(20);
		SDL_RenderPresent(gRenderer);
	}


	Close();
	return 0;
}