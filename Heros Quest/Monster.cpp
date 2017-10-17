#include "Monster.h"
#include <sstream>
using namespace std;

Monster::Monster() : Character(){
	//intPrizeMoney = 0;
	intSpecialAttack = 0;
}

Monster::Monster(string name, int health, int attack, int defence) : Character(name,health,attack,defence)
{
	//intPrizeMoney = prizeMoney;
	intSpecialAttack = 0;
}

Monster::Monster(string name, int health, int attack, int defence, int specialAttack) : Character(name, health, attack, defence)
{
	//intPrizeMoney = prizeMoney;
	intSpecialAttack = specialAttack;
}

int Monster::specialAttack()
{
	return (Monster::characterAttack() + intSpecialAttack);
}

//int Monster::getPrizeMoney()
//{
//	return intPrizeMoney;
//}

string Monster::displayStats() {
	stringstream sstream;
	sstream << "Name: " << Monster::getName();
	sstream << "\t" << "HP: " << Monster::getHealth();
	sstream << "\t" << "ATK: " << Monster::getAttack();
	sstream << "\t" << "DEF: " << Monster::getDefence();
	if (Monster::getSpecialAttack() != 0) {
		sstream << "\t" << "SPATK: " << Monster::getSpecialAttack();
	}
	sstream << endl;
	return sstream.str();
}