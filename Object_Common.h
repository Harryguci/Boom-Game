#ifndef  H_OBJECT_COMMON_
#define H_OBJECT_COMMON_
#include "CommonFunction.h"

class Object
{
public :
	Object();
	~Object();
	SDL_Rect _rect;
	SDL_Surface* _Img;
	bool SetImage(const std::string& file_name);
	void Display(SDL_Surface* _Img,SDL_Surface* g_bk);
};

#endif // ! H_OBJECT_COMMON
