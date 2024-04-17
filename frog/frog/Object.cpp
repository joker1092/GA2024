#include "WinApp.h"
#include "object.h"


void Object::InitObject(float x, float y, float width, float height, float speed, HBITMAP pBitmap)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speed = speed;
	this->pBitmap = pBitmap;
}


void Object::SetPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Object::Move(float x, float y)
{
	this->x += x;
	this->y += y;
}
