#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "BaseClass.h"

class Background : public BaseClass {
public:

	Background();
	~Background();
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
private:
	UINT32 startTime;
};


#endif