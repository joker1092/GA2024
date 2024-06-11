#include <iostream>
using namespace std;

typedef unsigned char BYTE;

static class Color
{
public:
	static int RGB(BYTE r, BYTE g, BYTE b) { return r << 16 | g << 8 | b; }
	static BYTE RED(int color) { return (BYTE)((color) >> 16); }
	static BYTE GREEN(int color) { return (BYTE)((color) >> 8); }
	static BYTE BLUE(int color) { return (BYTE)((color)); }
};




int main()
{
	int color = Color::RGB(0xFF, 0xEE, 0xAA);

	printf("red : %x ,green : %x ,blue : %x", Color::RED(color), Color::GREEN(color), Color::BLUE(color));

	return 0;
}