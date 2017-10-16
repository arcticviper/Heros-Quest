#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
//Universal Player/Monster Template

class Character {
public:
	Character(); //default constructor creates character with empty variables
	Character(std::string name, int health, int attack, int defence); //default constructors that take input
	~Character(); //character deconstructor
	int getDefence() { return *intDefence; } //outputs defence
	int getAttack() { return *intAttack; } //outputs attack
	std::string getName() { return *strName; } //returns name
	int getHealth() { return *intHealth; } //outputs attack
	int getSpecialAttack() { return *intSpecialAttack; } //outputs special attack
	bool getSpecialUsed() { return *boolUsedSpecialAttack; };
	int characterAttack(); // runs the 1-6+skill for attack
	int characterAttack(int intMin,int intMax); // runs attack with adjusted min/max values
	int characterDefend(); // runs the 1-6+skill for defence
	int characterDefend(int intMin, int intMax); // runs defence with adjusted min/max values
	void takeDamage(int intDamage);
	void resetSpecial();
	std::string displayStats();

protected:
	int* intHealth; //health variable
	std::string* strName; //name variable
	int* intAttack; //Attack stats
	int* intDefence; //defence stats
	int* intSpecialAttack; //special attack stat
	bool* boolUsedSpecialAttack; //used special attack
private:
	

};

#endif // !CHARACTER_H
