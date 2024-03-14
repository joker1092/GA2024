#include "Fraemwork.h"
#include "Charecter.h"

Charecter::Charecter() {
	init();
}

void Charecter::init() {
	str = 10;
	dex = 10;
	itl = 10;
	chr = 10;
	aff = 10;
}

void Charecter::addStr(int a) {
	str = +a;
}
void Charecter::addDex(int a) {
	dex = +a;
}
void Charecter::addItl(int a) {
	itl = +a;
}
void Charecter::addChr(int a) {
	chr = +a;
}
void Charecter::addAff(int a) {
	aff = +a;
}

int Charecter::getStr() {
	return str;
}
int Charecter::getDex() {
	return dex;
}
int Charecter::getItl() {
	return itl;
}
int Charecter::getChr() {
	return chr;
}
int Charecter::getAff() {
	return aff;
}

void Charecter::statusView(int state) {
	if (state != 99) {
		cout << "Èû : " << str << "¹ÎÃ¸ÇÕ : " << dex << "Áö½Ä : " << itl << endl;
		cout << "¸Å·Â : " << chr << "¿µÇâ·Â : " << aff << endl;
	}
}

Charecter::~Charecter() {

}