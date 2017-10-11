#include "Character.h"
#include <iostream>
#include <time.h>
using namespace std;

Character::Character()
{
	intHealth = 0;
	strName = "Undefined";
	intAttack = 0;
	intDefence = 0;
}

Character::Character(std::string name, int health, int attack, int defence)
{
	intHealth = health;
	strName = name;
	intAttack = attack;
	intDefence = defence;
}

int Character::characterAttack(int intMin, int intMax)
{
	int damage = 0;
	damage = rand() % intMax + intMin;
	damage = damage + intAttack;
	return damage;
}

int Character::characterAttack()
{
	return characterAttack(1, 6);
}

int Character::characterDefend(int intMin, int intMax)
{
	int defence = 0;
	defence = rand() % intMax + intMin;
	defence = defence + intDefence;
	return defence;
}

int Character::characterDefend()
{
	return characterDefend(1, 6);
}



void Character::takeDamage(int damage) {
	int intDefence = characterDefend();
	if (damage > intDefence) {
		damage = damage - intDefence;
		cout << "You have hit for " << damage << " damage." << endl;
		intHealth = intHealth - damage;
		if (intHealth < 0) {
			intHealth = 0;
		}
	}
	else {
		cout << "You missed!" << endl;
	}
}

void Character::resetSpecial() {
	boolUsedSpecialAttack = false;
}


//int main() {
//	srand(time(NULL));
//	Character test("testname", 10, 10, 10);
//	cout << test.characterAttack() << endl;
//	cout << test.characterDefend() << endl;
//
//
//
//	system("pause");
//	return 0;
//}