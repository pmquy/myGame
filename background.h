#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "BaseClass.h"

enum BKG {
	LEVEL_1,
	LOSE
};

class Background : public BaseClass {
public:

	Background();
	~Background();
	void handleMove();
	void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
	void handleState(bool);
	void loadImage(SDL_Renderer* renderer, std::string s1, std::string s2);
	BKG mState;
private:
	UINT32 startTime;
	std::vector<SDL_Texture*> mTextures;
};


#endif