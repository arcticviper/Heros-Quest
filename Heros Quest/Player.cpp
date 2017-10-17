#include "Player.h"
#include <iostream>
using namespace std;

Player::Player () : Character(){
	intPrizeMoney = new int(0);
	intSpecialAttack = new int(0);
	boolUsedSpecialAttack = new bool(false);
	boolUsedDodge = new bool(false);
}

<<<<<<< HEAD
Player::Player(string name, int health, int attack, int defence, int specialAttack) : Character(name, health, attack, defence){
	intPrizeMoney = 0;
	intSpecialAttack = specialAttack;
	boolUsedSpecialAttack = false;
}

int Player::specialAttack(){
	boolUsedSpecialAttack = true;
	return (Player::characterAttack() + intSpecialAttack);
=======
Player::Player(std::string name, int health, int attack, int defence, int specialAttack) : Character(name, health, attack, defence){
	intPrizeMoney = new int(0);
	intSpecialAttack = new int (specialAttack);
	boolUsedSpecialAttack = new bool (false);
	boolUsedDodge = new bool(false);
}

int Player::specialAttack(){
	*boolUsedSpecialAttack = true;
	return (Player::characterAttack() + *intSpecialAttack);
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd
}

void Player::addStats(int health, int attack, int defence, int specialAttack){
	// define variables to cap max stats
	int intHealthCap;
	int intAttackCap;
	int intDefenceCap;
	int intSpecialAttackCap;
	//calculates the changes can caps them if above a certain value.
<<<<<<< HEAD
	intHealthCap = intHealth + health;
	if (intHealthCap > 50) {
		intHealthCap = 50;
	}
	intAttackCap = intAttack + attack;
	if (intAttackCap > 10) {
		intAttackCap = 10;
	}
	intDefenceCap = intDefence + defence;
	if (intDefenceCap > 10) {
		intDefenceCap = 10;
	}
	intSpecialAttackCap = intSpecialAttack + specialAttack;
=======
	intHealthCap = *intHealth + health;
	if (intHealthCap > 50) {
		intHealthCap = 50;
	}
	intAttackCap = *intAttack + attack;
	if (intAttackCap > 10) {
		intAttackCap = 10;
	}
	intDefenceCap = *intDefence + defence;
	if (intDefenceCap > 10) {
		intDefenceCap = 10;
	}
	intSpecialAttackCap = *intSpecialAttack + specialAttack;
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd
	if (intSpecialAttackCap > 10) {
		intSpecialAttackCap = 10;
	}
	replaceStats(intHealthCap, intAttackCap, intDefenceCap, intSpecialAttackCap);
}

void Player::buffStats(int health, int attack, int defence, int specialAttack,bool isTemp){
	//if not perm, store stats in buff vector before changing
	if (isTemp == true) {
		stats = { intHealth ,intAttack ,intDefence ,intSpecialAttack };
	}
	//sets changes
	intHealth = intHealth + health;
	intAttack = intAttack + attack;
	intDefence = intDefence + defence;
	intSpecialAttack = intSpecialAttack + specialAttack;
}

//replaces player stats with new ones, restricting it to limits in the guideline
void Player::replaceStats(int health, int attack, int defence, int specialAttack){
	//caps max health at 50
	if (health > 50) {
		health = 50;
	}
	//caps max attack at 10
	if (attack > 10) {
		attack = 10;
	}
	//caps max defence at 10
	if (defence > 10) {
		defence = 10;
	}
	//caps max special Attack at 10
	if (specialAttack > 10) {
		specialAttack = 10;
	}
	//runs replace stats command
	replaceStatsNoCap(health, attack, defence, specialAttack);
}

void Player::replaceStatsNoCap(int health, int attack, int defence, int specialAttack){
	delete intHealth;
	delete intAttack;
	delete intDefence;
	delete intSpecialAttack;
	intHealth = new int (health);
	intAttack = new int (attack);
	intDefence = new int (defence);
	intSpecialAttack = new int (specialAttack);
}

//buffs defence by 1-6 by adding it onto of stats
int Player::playerDodge(){
	int dodgeBuff;
	dodgeBuff = rand() % 6 + 1;
<<<<<<< HEAD
	boolUsedDodge = true;
	addBuffs(0, 0, dodgeBuff, 0);
	return Player::intDefence + dodgeBuff;
=======
	*boolUsedDodge = true;
	addBuffs(0, 0, dodgeBuff, 0);
	return *intDefence + dodgeBuff;
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd
}

void Player::addBuffs(int intHPBuff, int intATKBuff, int intDEFBuff, int intSPATKBuff){
	//stores buffs in buff vector
	buffStats(intHPBuff, intATKBuff, intDEFBuff, intSPATKBuff,true);
	//adds stats to no
}

void Player::resetBuffs(){
	// calls stats stored in saved stats if there are any saved for the player
	if (stats.size() != 0) {
<<<<<<< HEAD
		replaceStats(stats[0], stats[1], stats[2], stats[3]);
=======
		replaceStats(*stats[0], *stats[1], *stats[2], *stats[3]);
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd
	}
	//resets temporary stored stats vector to nothing
	stats.clear();
}

void Player::useItem(int elementNumber){
	//prints out itemname
	cout << "You have chosen " << bag[elementNumber]->getDetails() << endl;
	//stores stats in element
	vector<int> tempStats;
	tempStats = bag[elementNumber]->getStats();
	//if the item is temporary then buff temporarily
	if (bag[elementNumber]->getTemp() == true) {
		addBuffs(tempStats[0], tempStats[1], tempStats[2], tempStats[3]);
	}
	//else add stats
	else {
		addStats(tempStats[0], tempStats[1], tempStats[2], tempStats[3]);
	}
	//delete's item from bag
	bag.erase(bag.begin() + elementNumber);
	
}

void Player::displayItem(){
	cout << "Displaying items: " << endl;
	for (int i = 0; i < bag.size(); i++) {
		cout << i+1 << ". " <<  bag[i]->getDetails();
	}
	cout << endl;
}

void Player::addItem(Item* newItem){
	bag.push_back(newItem);
<<<<<<< HEAD
	cout << "The new item: " << newItem.getName() << " has been added to your inventory." << endl;
=======
<<<<<<< HEAD
	cout << "The new item: " << newItem->getName() << " has been added to your inventory." << endl;
=======
	cout << "The new item: " << newItem.getName() << "has been added to your inventory." << endl;
>>>>>>> parent of 23824e3... 15/10 - Completed easy
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd
}

void Player::addMoney(int money){
	intPrizeMoney = intPrizeMoney + money;
}
<<<<<<< HEAD

void Player::takeDamage(int damage)
{
	int intDefence = characterDefend();
	if (damage > intDefence) {
		damage = damage - intDefence;
		cout << getName() << " has been hit for " << damage << " damage." << endl;
		intHealth = intHealth - damage;
		if (intHealth < 0) {
			intHealth = 0;
		}
	}
	else {
		cout << "You missed!" << endl;
	}
}
=======
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd

