#ifndef TEXT_H
#define TEXT_H
#include "BaseClass.h"


class Text : public BaseClass {
	public:
		Text();
		~Text();
		void loadText(SDL_Renderer *renderer, TTF_Font*, std::string content, SDL_Color = { 255, 255, 255 });
	private:
};

#endif