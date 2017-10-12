#include "Combat.h"
#include <time.h>
using namespace std;

Combat::Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter) {
	playerParty = PlayableCharacter;
	monsterParty = NonPlayableCharacter;
}

void Combat::execute_Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter){
	//set special attacks to false for combat
	for (int i = 0; i < playerParty.size(); i++) {
		playerParty[i].resetSpecial();
	}
	//loops through mobs
	for (int i = 0; i < monsterParty.size(); i++) {
		monsterParty[i].resetSpecial();
	}
	while (playerParty.size() > 0 || monsterParty.size() > 0) {
		//checks life of party

		//if party is dead
		if (playerParty.size() == 0) {
			cout << "Your party is dead." << endl;
			break;
		}
		//if monsters are dead
		else if (monsterParty.size() == 0) {
			cout << endl << "The enemies are dead." << endl;
			break;
		}
		else {

			//loops through playable character
			for (int i = 0; i < playerParty.size(); i++) {
				//cout << playerParty[i].getHealth() <<endl;
				cout << i + 1 << ". HP: " << playerParty[i].getHealth() << "\t" << "Name: " << playerParty[i].getName() << endl; //displays as: 1. HP: 99	Name: Mobname
				playerCombat(playerParty[i],i); //runs combat options
			}
			//loops through mobs
			for (int i = 0; i < monsterParty.size(); i++) {
				//cout << monsterParty[i].getHealth() << endl;
				//monsterCombat();
			}
		}
	}
}

void Combat::playerCombat(Player thePlayer, int intPlayer){
	Monster mobParty; //used for selecting monster
	int intMonsterChoice = 0; // int version of monster choice
	int intPlayerOption = 0;
	int intAttackChoice = 0;
	bool boolValidChoice = false; //ensuring choice is valid
	//selecting monster
	if (monsterParty.size() == 1) {
		cout << "There is only one monster left." << endl;
	}
	else {
		cout << "Which monster do you want to attack?" << endl;
	}
	for (int i = 0; i < monsterParty.size(); i++) {
		cout << i + 1 << ". HP: "<< monsterParty[i].getHealth() << "\t" << "Name: " << monsterParty[i].getName() << endl; //displays as: 1. HP: 99	Name: Mobname
	}
	//while monsterchoice is greater than 0 and less than or equal to party size, ask for input
	//if party size is 1, default to remaining monster
	if (monsterParty.size() == 1){
		intMonsterChoice = 1;
	}
	else {
		//else pick a monster
		intMonsterChoice = makeIntChoice("What monster would you like to select?", 1, monsterParty.size());
	}
	boolValidChoice = false;
	//sets it to array readable values
	intMonsterChoice = intMonsterChoice - 1;

	cout << "You have selected: " << monsterParty[intMonsterChoice].getName() << endl << endl;

	//display menu
	cout << "1. Light Attack (2-4 + Attack)" << endl; //modified attack for players for lower risk, lower damage
	cout << "2. Heavy Attack (1-6 + Attack)" << endl; //standard attack for players
	cout << "3. Special attack (Heavy Attack + Sp.Attack)" << endl; //special attack, can only be used once per combat
	cout << "4. Dodge (Buff Defence by 1-6, 0 dmg)" << endl; //buffs defence by 1-6 points for single round but deals no damage
	cout << "5. Item" << endl; //Opens item inventory, if item is used, sacrifice turn
	cout << "6. Save (saves current level+stats)" << endl; //Saves current game, not current state

	//resets if spatk or dodge has been used or cancels item use
	while (boolValidChoice == false) {
		intPlayerOption = makeIntChoice("What would you like to select?", 1, 6);
		switch (intPlayerOption) {
		case 1:
			monsterParty[intMonsterChoice].takeDamage(thePlayer.characterAttack(2, 4));
			boolValidChoice = true;
			break;
		case 2:
			monsterParty[intMonsterChoice].takeDamage(thePlayer.characterAttack());
			boolValidChoice = true;
			break;
		case 3:
			if (thePlayer.getSpecial() == true) {
				cout << "You have used your special attack already" << endl;
				break;
			}
			else {
				monsterParty[intMonsterChoice].takeDamage(thePlayer.specialAttack());
				//save special attack state
				playerParty[intPlayer] = thePlayer;
				break;
			}
		case 4:
			cout << "Your defence is now: " << thePlayer.playerDodge() << "." << endl;
			playerParty[intPlayer] = thePlayer;
			break;
		case 5:
			thePlayer.displayItem();
			itemMenu(thePlayer, intPlayer);
			break;
		case 6:
			break;
		}
	}
	
	if (monsterParty[intMonsterChoice].getHealth() <= 0) {
		cout << "The monster: "<< monsterParty[intMonsterChoice].getName() << " is dead" << endl;
		monsterParty.erase(monsterParty.begin() + intMonsterChoice);
	}

}
void Combat::monsterCombat(Monster theMonster, int intMonster){
	// Randomly generates the player that will be attacking
	int intPlayerChoice;
	intPlayerChoice = rand() % playerParty.size();
	//roll 25% chance at doing a special attack
	int intSpecialRoll;
	intSpecialRoll = rand() % 101; // 0-100
	// if roll is at 75 or higher, do special attack
	if (intSpecialRoll > 75) {
		// Deals special attack and saves the special attack state
		playerParty[intPlayerChoice].takeDamage(theMonster.specialAttack());
		monsterParty[intPlayerChoice] = theMonster;
	}
	else {
		// Attacks the player
		playerParty[intPlayerChoice].takeDamage(theMonster.characterAttack());
	}
	
	if (playerParty[intPlayerChoice].getHealth() <= 0) {
		cout << "The player: " << playerParty[intPlayerChoice].getName() << " is dead" << endl;
		playerParty.erase(playerParty.begin() + intPlayerChoice);
	}
}

void Combat::itemMenu(Player thePlayer, int intPlayer){
	int itemChoice;
	itemChoice = makeIntChoice("Which item would you like to use?", 1, thePlayer.getBagsize());
	itemChoice = itemChoice - 1;
	// uses item
	thePlayer.useItem(itemChoice);
	//save player
	playerParty[intPlayer] = thePlayer;
}

//limit input to string
string Combat::makeStringChoice(string strQuestion) {
	string choice = "";
	cout << strQuestion << endl;
	getline(cin, choice);
	while (choice.length() == 0) {
		cout << "Did you enter anything? (String input please)" << endl;
		getline(cin, choice);
	}
	return choice;
}

int Combat::makeIntChoice(std::string strQuestion, int lowerLimit, int upperLimit){
	int intPlayerOption;
	int boolValidChoice = false;
	while (boolValidChoice == false) {
		intPlayerOption = stoi(makeStringChoice(strQuestion));
		if ((intPlayerOption >= lowerLimit) && (intPlayerOption <= upperLimit)) {
			boolValidChoice = true;
		}
	}
	return intPlayerOption;
}

//limit input to char
char Combat::makeCharChoice(string strQuestion) {
	string choiceReturn;
	char charChoice;
	choiceReturn = makeStringChoice(strQuestion);

	while (choiceReturn.length() != 1) {
		choiceReturn = makeStringChoice(strQuestion);
		if (choiceReturn.length() == 0) {
			cout << "Did you enter anything? (Character input please)" << endl;
		}
		else if (choiceReturn.length() > 1) {
			cout << "Single Character Please" << endl;
		}

	}
	charChoice = choiceReturn[0];
	return charChoice;
}

int main() {
	srand(time(NULL));
	Player test("testname", 10, 10, 10,5);
	Item testItem("Fidget Spinner", 100, 50, 50, 50, false);
	//test.addItem(testItem);
	//cout << test.characterAttack() << endl;
	//cout << test.characterDefend() << endl;
	Monster mob1("Testmob", 10, 10, 10, 100);
	Monster mob2("Testmob2", 100, 5, 5, 150);
	//cout << mob1.characterAttack() << endl;
	//cout << mob1.characterDefend() << endl;
	vector<Player> plParty = { test };
	vector<Monster> mbParty = { mob1,mob2 };
	Combat fight1(plParty, mbParty);
	fight1.execute_Combat(plParty, mbParty);


	system("pause");
	return 0;
}