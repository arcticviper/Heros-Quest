#include "Character.h"
#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;

Character::Character()
{
	intHealth = new int(0);
	strName = new string("Undefined");
	intAttack = new int(0);
	intDefence = new int(0);
	intSpecialAttack = new int(0);
	boolUsedSpecialAttack = new bool(false);
}

Character::Character(std::string name, int health, int attack, int defence)
{
	intHealth = new int(health);
	strName = new string(name);
	intAttack = new int(attack);
	intDefence = new int(defence);
	intSpecialAttack = new int(0);
	boolUsedSpecialAttack = new bool(false);
}

Character::~Character()
{
	delete intHealth;
	delete strName;
	delete intAttack;
	delete intDefence;
	delete intSpecialAttack;
	delete boolUsedSpecialAttack;

}

int Character::characterAttack(int intMin, int intMax)
{
	int damage = 0;
	damage = rand() % intMax + intMin;
	damage = damage + *intAttack;
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
	defence = defence + *intDefence;
	return defence;
}

int Character::characterDefend()
{
	return characterDefend(1, 6);
}

string Character::displayStats() {
	stringstream sstream;
	sstream << "Name: " << getName();
	sstream << "\t" << "HP: " << getHealth();
	sstream << "\t" << "ATK: " << getAttack();
	sstream << "\t" << "DEF: " << getDefence();
	sstream << "\t" << "SPATK: " << getSpecialAttack();
	sstream << endl;
	return sstream.str();
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
	*boolUsedSpecialAttack = false;
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