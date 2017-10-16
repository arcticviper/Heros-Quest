#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>

class Item {
public:
	Item(); // default constructor
	Item(std::string itemName, int HPEffect, int ATKEffect, int DEFEffect, int SPATKEffect, bool TEMPEffect); //constructor that takes full input
	//~Item(); // default destructor
	std::string getName() { return itemName; } //returns name of item
	std::string getDetails(); //gets all details of item that aren't 0
	std::string getDetailsShort(); //gets all details of item that aren't 0 ignoring name
	std::vector<int> getStats(); //returns effects as stat ints
	bool getTemp() { return boolTemporary; } //gets item permanent values
	Item getItem(); //randomly generates items
private:
	std::string itemName; //obvious
	int HPChange; // how this items changes HP
	int ATKChange; // how this items changes ATK
	int DEFChange; // how this items changes DEF
	int SPATKChange; // how this items changes SPATK
	bool boolTemporary; // is the item temporary or permanent

};


#endif // !ITEM_H
