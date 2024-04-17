#pragma once
class Object
{
public:
	void InitObject(float x, float y, float width, float height, float speed, HBITMAP pBitmap);

	void SetPos(float x, float y);

	void Move(float x, float y);

	float x;
	float y;
	float width;
	float height;
	float speed;

	HBITMAP pBitmap;
};

