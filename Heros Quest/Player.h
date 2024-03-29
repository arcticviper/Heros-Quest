#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "Item.h"
#include <vector>
//Player Template, inherits Character

class Player : public Character{
public:
	Player(); // default constructor
	Player(std::string name, int health, int attack, int defence, int specialAttack); // manual constructor
	int specialAttack(); //special attack replaces attack as 1-6+attack+special
	void addStats(int health, int attack, int defence, int specialAttack); // adds stats on top of existing, for leveling
	void replaceStats(int health, int attack, int defence, int specialAttack); // replaces existing stats with cap
	int playerDodge(); // rolls 1-6 on top of defence
	void resetBuffs(); // resets all the buffs implemented
	void useItem(int elementNumber); // use item by picking element number
	void displayItem(); // displays items in bag
	void addItem(Item newItem); // adds new item
	int getBagsize() { return bag.size(); } //returns bag size
	void addMoney(int money); //adds money into intPrizemoney
	int getMoney() { return intPrizeMoney; }; //returns total value of money
	void takeDamage(int damage); //custom takedamage output


protected:
	void replaceStatsNoCap(int health, int attack, int defence, int specialAttack); // replaces existing stats without cap
	void addBuffs(int intHPBuff, int intATKBuff, int intDEFBuff, int intSPATKBuff);
	void buffStats(int health, int attack, int defence, int specialAttack, bool isPerm); // adds stats on top of existing without cap, for buffs/items
	int intPrizeMoney; //prize money recieved
	bool boolUsedDodge; //used dodge
	std::vector<Item> bag; // bag for items
	std::vector<int> stats ; // buffs that are utilised for a single turn

private:


};

#endif // !PLAYER_H
