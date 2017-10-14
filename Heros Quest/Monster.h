#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
//Monster Template, inherits Character

class Monster : public Character {
public:
	Monster(); // default constructor
	//~Monster(); // default destructor
	Monster(std::string name, int health, int attack, int defence); // manual constructor, no special attack
	Monster(std::string name, int health, int attack, int defence, int specialAttack); // manual constructor, including special attack
	int specialAttack(); //special attack replaces attack as 1-6+attack+special
	//int getPrizeMoney(); //gets how much money they get.
	void addStats();
	std::string displayStats();

protected:
	//int intPrizeMoney;
	int intSpecialAttack;


private:


};

#endif // !PLAYER_H
