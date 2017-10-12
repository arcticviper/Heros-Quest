#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item {
public:
	Item(); // default constructor
	Item(std::string itemName, int HPEffect, int ATKEffect, int DEFEffect, int SPATKEffect); //constructor that takes full input
	std::string getName() { return itemName; }; //returns name of item
	std::string getDetails(); //gets all details of item that aren't 0
private:
	std::string itemName; //obvious
	int HPChange; // how this items changes HP
	int ATKChange; // how this items changes ATK
	int DEFChange; // how this items changes DEF
	int SPATKChange; // how this items changes SPATK

};


#endif // !ITEM_H
