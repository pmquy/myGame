#include "Text.h"

Text::Text() {

}

Text::~Text() {
	BaseClass::free();
}

void Text::loadText(SDL_Renderer* renderer, std::string content) {

	TTF_Font *font = TTF_OpenFont("Font_folder/Font2.ttf", 24);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, content.c_str(), gTextColor);
	mRect.w = textSurface->w;
	mRect.h = textSurface->h;

	mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	TTF_CloseFont(font);
	SDL_FreeSurface(textSurface);
}

void Text::loadNumber(SDL_Renderer* renderer, int number) {
	if (number == 0) {
		loadText(renderer, "Score: 0");
		return;
	}
	std::string s = "";
	while (number != 0) {
		s = std::string(1, number % 10 + '0') + s;
		number /= 10;
	}
	loadText(renderer, "Score: " + s);
}