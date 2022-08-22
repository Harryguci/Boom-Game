#include "Object_Common.h"

Object::Object()
{
	_Img = NULL;
	_rect.x = _rect.y = 0;
}

Object::~Object()
{
	;
}

bool Object::SetImage(const std::string& file_name)
{
	if (_Img != NULL)
		_Img = NULL;
	_Img = CommonFunction::LoadImage(file_name);
	return (_Img == NULL ? false : true);
}

void Object::Display(SDL_Surface* _Img, SDL_Surface* g_bk)
{
	if (_Img != NULL && g_background != NULL)
		CommonFunction::ApplySurface(_Img, g_bk, _rect.x, _rect.y);
}