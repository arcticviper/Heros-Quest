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
	void addStats(int health, int attack, int defence, int specialAttack); // adds stats on top of existing, for leveling
	void buffStats(int health, int attack, int defence, int specialAttack,bool isPerm); // adds stats on top of existing without cap, for buffs/items
	void replaceStats(int health, int attack, int defence, int specialAttack); // replaces existing stats with cap
	void replaceStatsNoCap(int health, int attack, int defence, int specialAttack); // replaces existing stats without cap
	int playerDodge(); // rolls 1-6 on top of defence
	void resetBuffs(); // resets all the buffs implemented
	void useItem(); // 


protected:
	void addBuffs(int intHPBuff, int intATKBuff, int intDEFBuff, int intSPATKBuff);
	int intPrizeMoney; //prize money recieved
	int intSpecialAttack; //special attack stat
	bool boolUsedDodge; //used special attack
	// std::vector<Item> bag; // bag for items
	std::vector<int> stats ; // buffs that are utilised for a single turn

private:


};

#endif // !PLAYER_H
