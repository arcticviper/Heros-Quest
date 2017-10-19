#include "Character.h"
#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;

//default player constructor
Character::Character()
{
	intHealth = 0;
	strName = "Undefined";
	intAttack = 0;
	intDefence = 0;
	intSpecialAttack = 0;
	boolUsedSpecialAttack = false;
}
//player constructor that takes health, attack and defence as input
Character::Character(string name, int health, int attack, int defence)
{
	intHealth = health;
	strName = name;
	intAttack = attack;
	intDefence = defence;
	intSpecialAttack = 0;
	boolUsedSpecialAttack = false;
}
//runs attack allowing for minimum and plus values
int Character::characterAttack(int intMin, int intMax)
{
	int damage = 0;
	damage = rand() % intMax + intMin;
	damage = damage + intAttack;
	return damage;
}
//default attack from spec
int Character::characterAttack()
{
	return characterAttack(1, 6);
}
//runs the defecne allowing for minimum and plus values
int Character::characterDefend(int intMin, int intMax)
{
	int defence = 0;
	defence = rand() % intMax + intMin;
	defence = defence + intDefence;
	return defence;
}
//default defence from spec
int Character::characterDefend()
{
	return characterDefend(1, 6);
}
//displays the chatacters stats
string Character::displayStats() {
	stringstream sstream;
	sstream << "Name: " << Character::getName();
	sstream << "\t" << "HP: " << Character::getHealth();
	sstream << "\t" << "ATK: " << Character::getAttack();
	sstream << "\t" << "DEF: " << Character::getDefence();
	sstream << "\t" << "SPATK: " << Character::getSpecialAttack();
	sstream << endl;
	return sstream.str();
}

//takes damage if the damage is higher than the characters defence
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
//resets the special attack
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