#include "CommonFunction.h"

SDL_Texture* loadTexture(SDL_Renderer *renderer, std::string path) {
	SDL_Texture* loadedTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		std::cout << "loaded surface failed";
	}
	else {
		loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (loadedTexture == nullptr) {
			std::cout << "loaded texture failed";
		}
	}
	return loadedTexture;
}