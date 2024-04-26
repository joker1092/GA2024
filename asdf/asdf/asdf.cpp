#include <iostream>
using namespace std;

class Charter {
private:
	char name[8];
	int hp;
	int ap;
public:
	Charter(const char* _name ,int _hp, int _ap) {
		strcpy_s(name,_name);
		hp = _hp;
		ap = _ap;
	}
	void setHp(int _hp) { hp = _hp; };
	int getHp() { return hp; };
	void setAp(int _ap) { ap = _ap; };
	int getAp() { return ap; };
	void setName(const char* _name) { strcpy_s(name, _name); };
	char* getName() { return name; };

	void Attack(Charter& p) {
		p.hp -= ap;
	}
};



int main(void)
{	
	Charter player{ "player",100,10 };
	Charter monster{ "monster",60,7 };

	std::string winner = "";

	while (true) {
		player.Attack(monster);
		if (monster.getHp() < 0) { winner = player.getName(); break; };
		
		monster.Attack(player);
		if (player.getHp() < 0)		{ winner = monster.getName(); break; }
	}

	cout << "winner : " << winner << endl;

	return 0;
}
