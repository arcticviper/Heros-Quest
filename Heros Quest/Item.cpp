#include "Item.h"
#include <sstream>
using namespace std;

Item::Item(){
	//sets name to undefined and all other values to 0
	itemName = "Undefined";
	HPChange = 0;
	ATKChange = 0;
	DEFChange = 0;
	SPATKChange = 0;
}

Item::Item(std::string newItemName, int HPEffect, int ATKEffect, int DEFEffect, int SPATKEffect, bool TEMPEffect){
	itemName = newItemName;
	HPChange = HPEffect;
	ATKChange = ATKEffect;
	DEFChange = DEFEffect;
	SPATKChange = SPATKEffect;
	boolTemporary = TEMPEffect;
}

std::string Item::getDetails()
{
	stringstream sstream;
	sstream << "Name: " << itemName;
	//if HP change is not 0, display HP stat
	if (HPChange != 0) {
		sstream << "\t" << "HP: " << HPChange;
	}
	if (ATKChange != 0) {
		sstream << "\t" << "ATK: " << ATKChange;
	}
	if (DEFChange != 0) {
		sstream << "\t" << "DEF: " << DEFChange;
	}
	if (SPATKChange != 0) {
		sstream << "\t" << "SPATK: " << SPATKChange;
	}
	sstream << endl;
	return sstream.str();
}

std::string Item::getDetailsShort()
{
	stringstream sstream;
	//if HP change is not 0, display HP stat
	if (HPChange != 0) {
		sstream << "\t" << "HP: " << HPChange;
	}
	if (ATKChange != 0) {
		sstream << "\t" << "ATK: " << ATKChange;
	}
	if (DEFChange != 0) {
		sstream << "\t" << "DEF: " << DEFChange;
	}
	if (SPATKChange != 0) {
		sstream << "\t" << "SPATK: " << SPATKChange;
	}
	sstream << endl;
	return sstream.str();
}

std::vector<int> Item::getStats(){
	vector<int> itemStats = { HPChange , ATKChange , DEFChange, SPATKChange };
	return itemStats;
}
