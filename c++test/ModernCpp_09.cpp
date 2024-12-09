// Players 를 
// 이름 순으로 정렬하여 출력하고,
// 레벨 순으로 정렬하여 출력하세요.
// 
// sort 알고리즘과 람다를 활용하여 해결하세요.

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class Player {
public:
	int level = 0;
	string name = "";
	Player(string name, int level) : name(name), level(level) {}
};

int main()
{
	vector<Player> players; 
	players.push_back(Player("player1", 4));
	players.push_back(Player("player4", 1));
	players.push_back(Player("player2", 2));
	players.push_back(Player("player3", 3));
	
	//이름 순으로 정렬하여 출력하기
	sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
		return a.name < b.name;
	});
	for (auto& p :players)
	{
		cout << p.name << " "<< p.level <<endl;
	}

	//레벨 순으로 정렬하여 출력하기
	sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
		return a.level < b.level;
		});
	for (auto& p : players)
	{
		cout << p.name << " " << p.level << endl;
	}


	return 0;
}
