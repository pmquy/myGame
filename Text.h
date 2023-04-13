#ifndef TEXT_
#define TEXT_
#include "BaseClass.h"


class Text : public BaseClass {
	public:
		Text();
		~Text();
		void loadText(SDL_Renderer *renderer, TTF_Font*, std::string content, SDL_Color = { 102, 255, 102 });
	private:
		
};

#endif