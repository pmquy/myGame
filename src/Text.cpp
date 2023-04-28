#include "Text.h"

Text::Text() {

}

Text::~Text() {

}

void Text::loadText(SDL_Renderer* renderer,TTF_Font* font, std::string content, SDL_Color color) {
	free();
	if(content == "") {
		content = "???";
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, content.c_str(), color);
	mRect.w = textSurface->w;
	mRect.h = textSurface->h;
	mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}

