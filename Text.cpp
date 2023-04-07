#include "Text.h"

Text::Text() {

}

Text::~Text() {
	BaseClass::free();
}


void Text::loadText(SDL_Renderer* renderer,TTF_Font* font, std::string content) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, content.c_str(), gTextColor);
	mRect.w = textSurface->w;
	mRect.h = textSurface->h;

	mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

