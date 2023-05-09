#include "Game.h"
#include <time.h>

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Event gEvent;
Game game;

void Init() {
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	gWindow = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void gameLoop() {
	while (true) {
		game.handleState(gRenderer, gEvent);
		game.render(gRenderer);
		game.handleMove();

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				return;
			}
			game.handleState(gRenderer, gEvent);
		}

		if ((game.getState() == LEVEL)) {
			game.updateObject(gRenderer);
		}

		SDL_RenderPresent(gRenderer);
	}
}

int main(int argc, char* argv[]) {
	Init();
	game.loadResource(gRenderer);
	gameLoop();
	Close();
	return 0;
}

