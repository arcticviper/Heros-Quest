#include "Monster.h"

Monster::Monster() : Character(){
	intPrizeMoney = 0;
	intSpecialAttack = 0;
}

Monster::Monster(std::string name, int health, int attack, int defence, int prizeMoney) : Character(name,health,attack,defence)
{
	intPrizeMoney = prizeMoney;
	intSpecialAttack = 0;
}

Monster::Monster(std::string name, int health, int attack, int defence, int specialAttack, int prizeMoney) : Character(name, health, attack, defence)
{
	intPrizeMoney = prizeMoney;
	intSpecialAttack = specialAttack;
}

int Monster::specialAttack()
{
	return (Monster::characterAttack() + intSpecialAttack);
}

int Monster::getPrizeMoney()
{
	return intPrizeMoney;
}

