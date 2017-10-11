#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include <vector>
//Player Template, inherits Character

class Player : public Character{
public:
	Player(); // default constructor
	Player(std::string name, int health, int attack, int defence, int specialAttack); // manual constructor
	int specialAttack(); //special attack replaces attack as 1-6+attack+special
	void addStats(int health, int attack, int defence, int specialAttack); // adds stats on top of existing, for leveling?
	void replaceStats(int health, int attack, int defence, int specialAttack); // replaces existing stats,for items?
	int playerDodge(); // rolls 1-6 on top of defence


protected:
	int intPrizeMoney; //prize money recieved
	int intSpecialAttack; //special attack stat
	bool boolUsedSpecialAttack; //used special attack
	bool boolUsedDodge; //used special attack
	// std::vector<Item> bag; // bag for items
	// std::vector<Buffs> buffs // buffs

private:


};

#endif // !PLAYER_H
