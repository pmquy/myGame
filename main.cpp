#include "Header.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Event gEvent;
std::pair<int, int> gMouse(0, 0);

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
	
	Mix_PlayMusic(game.mGameMusic, -1);
	
	while (true) {

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				return;
			}
			SDL_GetMouseState(&gMouse.first, &gMouse.second);
			game.handleState(gRenderer, gMouse, gEvent);

			if (game.mState == LEVEL1 || game.mState == LEVEL2 || game.mState == LEVEL3 || game.mState == LEVEL4 || game.mState == LEVEL5) {
				game.hero->handleAction(gEvent, gRenderer);
			}
		}

		game.render(gRenderer);
		game.renderText(gRenderer);
		game.handleState(gRenderer, gMouse, gEvent);

		if (game.mState == LEVEL1 || game.mState == LEVEL2 || game.mState == LEVEL3 || game.mState == LEVEL4 || game.mState == LEVEL5) {
			game.oldState = game.getState();
			game.handleMove();
			game.handleLogic(gRenderer);
			game.handleObject(gRenderer);
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

