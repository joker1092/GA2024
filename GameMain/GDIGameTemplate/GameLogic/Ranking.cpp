#include "Ranking.h"

Renking::Renking() {
    filename = "rankings.txt";
    loadRankings();
    sortRank();
    rankToStr();
}

bool Renking::comparePlayer(const Player& p1, const Player& p2)
{
	return p1.score > p2.score;
}

void Renking::saveRankings()
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const Player& player : players) {
        file << player.name << " " << player.score << std::endl;
    }

    file.close();
}

void Renking::loadRankings()
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading.\n";
        return;
    }

    std::string name;
    int score;

    while (file >> name >> score) {
        players.push_back(Player(name, score));
    }

    file.close();
}

void Renking::sortRank()
{
    std::sort(players.begin(), players.end(), comparePlayer);
}

void Renking::rankToStr()
{
    str_rank = "";
    int rank = 1;
    
    for (const Player& player : players) {
        str_rank += rank + ". " + player.name + " - " + std::to_string(player.score) + "\n";
        rank++;
    }
}

Renking::~Renking() {
    
}