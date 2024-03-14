#pragma once
class Charecter
{
public:
	Charecter();
	~Charecter();
	void addStr(int a);
	void addDex(int a);
	void addItl(int a);
	void addChr(int a);
	void addAff(int a);
	int getStr();
	int getDex();
	int getItl();
	int getChr();
	int getAff();
	void statusView(int state);
private:
	void init();
	int str;
	int dex;
	int itl;
	int chr;
	int aff;
};