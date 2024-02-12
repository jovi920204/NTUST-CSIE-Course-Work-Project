#include <iostream>
#include <vector>
#include "Entity.h"
using namespace std;
int main() {
	vector<Monster> monsterList;
	int hp, attack, defence;
	cin >> hp >> attack >> defence;
	Hero hero(hp, attack, defence);

	while (cin >> hp >> attack >> defence) {
		Monster monster(hp, attack, defence);
		monsterList.push_back(monster);
	}
	while (monsterList.size() && hero.getHp() > 0) {
		if (hero.getHp() <= 0)
			break;
		monsterList.front().attacking(hero, monsterList.front());
		cout << "Player:" << hero.getHp() << " Enemy:" << monsterList.front().getHp() << "\n";
		if (monsterList.front().getHp() <= 0) {
			monsterList.erase(monsterList.begin());
			cout << "Player Win\n";
			continue;
		}
		if (monsterList.size()) {
			monsterList.front().attacking(monsterList.front(), hero);
			cout << "Player:" << hero.getHp() << " Enemy:" << monsterList.front().getHp() << "\n";
		}
	}
	if (hero.getHp() <= 0)
		cout << "Player Dead\n";
	return 0;
}