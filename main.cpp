#include "Game.h"

Game game;
GameType oldState;

void loadResource() {
	game.loadImage(gRenderer, GAME_PATHS);
	hero.loadImage(gRenderer, HERO1_PATHS);

	for (int i = 0; i < int(bots.size()); i++) {
		Bot* newBot = new Bot();
		newBot->loadImage(gRenderer, BOTS_PATHS[rand()%3]);
		newBot->setBotType(static_cast<BotType>(rand() % 2));

		if (i <= 1) {
			newBot->setIsAppear(true);
		}
		else {
			newBot->setIsAppear(false);
		}
		bots[i] = newBot;
	}
}


void Init() {
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	gWindow = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	gFont = TTF_OpenFont("Font_Folder/font2.ttf", 30);
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
	
	game.playMusic();
	
	while (true) {

		game.render(gRenderer);
		game.renderText(gRenderer, gFont);
		game.handleState(gRenderer, gMouse, gEvent, &hero, oldState, bots);

		while (SDL_PollEvent(&gEvent)) {
			if (gEvent.type == SDL_QUIT) {
				return;
			}
			SDL_GetMouseState(&gMouse.first, &gMouse.second);
			game.handleState(gRenderer, gMouse, gEvent, &hero, oldState, bots);

			if (game.getState() != START && game.getState() != SHOP && game.getState() != DEAD && game.getState() != UPGRADE && game.getState() != VICTORY) {
				hero.handleAction(gEvent, gRenderer);
			}
		}

		switch (game.getState()) {
		
		case UPGRADE:
		case SHOP:
		case START:
		case DEAD:
		case VICTORY:
			break;
		case LEVEL_1:
		case LEVEL_2:
		case LEVEL_3:
		case LEVEL_4:
		case LEVEL_5:

			game.handleMove(); 
			oldState = game.getState();
			game.handleLogic(gRenderer, &hero, bots);
			
			hero.handleMove(); hero.handleState(gRenderer); hero.handleSkill(); hero.renderText(gRenderer, gFont); hero.render(gRenderer, 1);
			for (int i = 0; i < int(bots.size()); i++) {
				if (bots[i]->getIsAppear()) {
					bots[i]->handleAction(gRenderer); bots[i]->handleMove(); bots[i]->handleState(gRenderer); bots[i]->render(gRenderer, -1);
				}
			}
			break;
		}
		SDL_RenderPresent(gRenderer);
	}
}

int main(int argc, char* argv[]) {
	Init();
	loadResource();
	gameLoop();
	Close();
	return 0;
}

