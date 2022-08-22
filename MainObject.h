#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include "CommonFunction.h"
using namespace CommonFunction;
enum Body
{
	UP1 = 0, UP2, UP3, UP4, l1, l2, l3, l4, R1, R2, R3, R4, D1, D2, D3, D4
};

class MainObject
{
public :
	MainObject();
	~MainObject();
	void SetUp()
	{
		this._img[0] =	LoadImage()
	}

private:
	SDL_Surface* _img[16];
	SDL_Rect _rect;
	
};

#endif // !MAINOBJECT_H
