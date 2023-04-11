#ifndef TEXT_
#define TEXT_
#include "BaseClass.h"

static SDL_Color gTextColor = { 255, 100, 100 };
static TTF_Font* gFont = nullptr;


class Text : public BaseClass {
	public:
		Text();
		~Text();
		void loadText(SDL_Renderer *renderer, TTF_Font*, std::string content);
	private:
		
};

#endif