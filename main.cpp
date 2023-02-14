#include "TextureClass.h"
bool isQuit = false;

void Init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("minhquy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_JPG);
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

	TextureClass background;
	background.loadFromFile(gRenderer, "bg.jpg");
	background.setHeight(SCREEN_HEIGHT);
	background.setWidth(SCREEN_WIDTH);
	int i = 0;

	while (!isQuit) {
		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				isQuit = true;
			}
		}
		SDL_Rect vip = { 0, 0, 1200, 600 };
		background.render(gRenderer, i, 0);
		background.render(gRenderer, i + 1200, 0);
		i--;
		if (i == -1200) i = 0;



		
		SDL_RenderPresent(gRenderer);
		SDL_Delay(10);
	}


	Close();
	return 0;
}