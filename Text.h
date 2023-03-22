#ifndef TEXT_
#define TEXT_
#include "BaseClass.h"

class Text : public BaseClass {
	public:
		Text();
		~Text();
		void loadText(SDL_Renderer *renderer, std::string content);
		void loadNumber(SDL_Renderer* renderer, int, std::string);
	private:
		

};

#endif