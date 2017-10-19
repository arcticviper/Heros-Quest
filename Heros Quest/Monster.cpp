#include "Monster.h"
#include <sstream>
using namespace std;

// default monnster constructor
Monster::Monster() : Character(){
	//intPrizeMoney = 0;
	intSpecialAttack = 0;
}
// monster constructor that takes name, health, attack and defence.
Monster::Monster(string name, int health, int attack, int defence) : Character(name,health,attack,defence)
{
	//intPrizeMoney = prizeMoney;
	intSpecialAttack = 0;
}
// monster constructor that allows for special attack
Monster::Monster(string name, int health, int attack, int defence, int specialAttack) : Character(name, health, attack, defence)
{
	//intPrizeMoney = prizeMoney;
	intSpecialAttack = specialAttack;
}
// executes special attack
int Monster::specialAttack()
{
	return (Monster::characterAttack() + intSpecialAttack);
}

//int Monster::getPrizeMoney()
//{
//	return intPrizeMoney;
//}
//displays monsters stats and displays special attack if any
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