#pragma once
#include "../stdafx.h"

class Renking
{
	struct Player {
		std::string name;
		int score;

		Player(const std::string& n,int s):name(n), score(s){}
	};
public:
	std::vector<Player> players;
	std::string filename;

	std::string str_rank;

	Renking();
	~Renking();
	bool comparePlayer(const Player& p1, const Player& p2);
	void saveRankings();
	void loadRankings();
	void sortRank();
	void rankToStr();
};

