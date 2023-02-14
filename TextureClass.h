#ifndef TEXTURECLASS_H_
#define TEXTURECLASS_H_

#include "Common.h"


class TextureClass {
public:
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	TextureClass();
	~TextureClass();
	void loadFromFile(SDL_Renderer* renderer,std::string fileName);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);
private:
	int mWidth;
	int mHeight;
	SDL_Texture* mTexture;
};


#endif 

