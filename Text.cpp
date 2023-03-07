#include "Text.h"

Text::Text() {

}

Text::~Text() {

}

void Text::loadText(SDL_Renderer* renderer, std::string content) {
	free();
	TTF_Font *gFont = TTF_OpenFont("font_folder/font1.ttf", 24);
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "pppppppp", gTextColor);



	if (textSurface == nullptr) {
		std::cout << "TextureSurface nullptr and " << TTF_GetError() << "\n";
	}

	mRect.w = textSurface->w;
	mRect.h = textSurface->h;

	mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	TTF_CloseFont(gFont);
	SDL_FreeSurface(textSurface);
}