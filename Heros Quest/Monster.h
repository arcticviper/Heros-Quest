#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
//Monster Template, inherits Character

class Monster : public Character {
public:
	Monster(); // default constructor
	//~Monster(); // default destructor
	Monster(std::string name, int health, int attack, int defence, int prizeMoney); // manual constructor, no special attack
	Monster(std::string name, int health, int attack, int defence, int specialAttack, int prizeMoney); // manual constructor, including special attack
	int specialAttack(); //special attack replaces attack as 1-6+attack+special
	int getPrizeMoney(); //gets how much money they get.
	void addStats();

protected:
	int intPrizeMoney;
	int intSpecialAttack;


private:


};

#endif // !PLAYER_H
