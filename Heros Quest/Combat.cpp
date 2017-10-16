#include "Combat.h"
#include <time.h>
#include "InputFunctions.h"
using namespace std;

Combat::Combat(vector<Player> PlayableCharacter, vector<Monster> NonPlayableCharacter) {
	cout << "Combat constructor " << PlayableCharacter[0].getHealth() << endl;
	for (int i = 0; i < PlayableCharacter.size(); i++) {
		playerParty.push_back(PlayableCharacter[i]);
	}
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
		cout << "It's now the players turn." << endl;
		for (int i = 0; i < playerParty.size(); i++) {
			//break out of for loop if monsters are dead
			if (monsterParty.size() == 0) {
				cout << endl << "The enemies are dead." << endl;
				break;
			}
			else {
				//cout << playerParty[i].getHealth() <<endl;
				cout << i + 1 << ". " << playerParty[i].displayStats() << endl; //displays as: 1. Name: PlayerName HP:123 ATK:123 DEF:123 SPATK:123
				playerCombat(playerParty[i], i); //runs combat options
			}
			
		}
		//break out of while loop if monsters are dead
		if (monsterParty.size() == 0) {
			break;
		}
		//loops through mobs
		cout << "It's now the monsters turn." << endl;
		for (int i = 0; i < monsterParty.size(); i++) {
			//break out of for loop if players are dead
			if (playerParty.size() == 0) {
				cout << "Your party is dead." << endl;
				break;
			}
			else {
				//cout << monsterParty[i].getHealth() << endl;
				cout << i + 1 << ". " << monsterParty[i].displayStats();
				monsterCombat(monsterParty[i], i);
			}
		}
		//break out of while loop if players are dead
		if (playerParty.size() == 0) {
			break;
		}
		cout << endl;
	}
}

void Combat::playerCombat(Player thePlayer, int intPlayer){
	//resets defence buff
	thePlayer.resetBuffs();
	//checks item buff
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

	cout << "You have selected: " << monsterParty[intMonsterChoice].getName() << endl ;

	//resets if spatk or dodge has been used or cancels item use
	while (boolValidChoice == false) {
		//display menu
		cout << endl;
		cout << "1. Light Attack (2-4 + Attack)" << endl; //modified attack for players for lower risk, lower damage
		cout << "2. Heavy Attack (1-6 + Attack)" << endl; //standard attack for players
		cout << "3. Special attack (Heavy Attack + Sp.Attack)" << endl; //special attack, can only be used once per combat
		cout << "4. Dodge (Buff Defence by 1-6, 0 dmg)" << endl; //buffs defence by 1-6 points for single round but deals no damage
		cout << "5. Item" << endl; //Opens item inventory, if item is used, sacrifice turn
		cout << "6. Save (saves current level+stats)" << endl; //Saves current game, not current state
		//option for input
		intPlayerOption = makeIntChoice("What would you like to select?", 1, 6);
		cout << endl;
		switch (intPlayerOption) {
		case 1: // light attack
			monsterParty[intMonsterChoice].takeDamage(thePlayer.characterAttack(2, 4));
			boolValidChoice = true;
			break;
		case 2: // heavy attack
			monsterParty[intMonsterChoice].takeDamage(thePlayer.characterAttack());
			boolValidChoice = true;
			break;
		case 3: // special attack
			// if used, print out text and return to input
			if (thePlayer.getSpecialUsed() == true) {
				cout << "You have used your special attack already" << endl;
				break;
			}
			//else run special attack
			else {
				monsterParty[intMonsterChoice].takeDamage(thePlayer.specialAttack());
				//save special attack state
				boolValidChoice = true;
				break;
			}
		case 4: // dodge for one turn
			cout << "Your defence is now: " << thePlayer.playerDodge() << "." << endl;
			
			boolValidChoice = true;
			break;
		case 5: // use item
			thePlayer.displayItem();
			cout << "0. Cancel" << endl;
			if (itemMenu(thePlayer, intPlayer) == false) {
				break;
			}
			else {
				//requires an earlier save of the instance's current state to display item stats
				 thePlayer = playerParty[intPlayer];
				cout << "Your current stats are:" << thePlayer.displayStats();
				break;
			}
		case 6:
			//save
			break;
		}
	}
	//saves the instance's current state
	playerParty[intPlayer] = thePlayer;
	if (monsterParty[intMonsterChoice].getHealth() <= 0) {
		cout << "The monster: "<< monsterParty[intMonsterChoice].getName() << " is dead" << endl << endl;
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
	if (intSpecialRoll > 75 && theMonster.getSpecialUsed() == false) {
		// Deals special attack and saves the special attack state
		cout << theMonster.getName() << " used a special attack." << endl;
		playerParty[intPlayerChoice].takeDamage(theMonster.specialAttack());
		monsterParty[intMonster] = theMonster;
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

bool Combat::itemMenu(Player thePlayer, int intPlayer){
	int itemChoice;
	itemChoice = makeIntChoice("Which item would you like to use?", 0, thePlayer.getBagsize());
	if (itemChoice == 0) {
		return false;
	}
	itemChoice = itemChoice - 1;
	// uses item
	thePlayer.useItem(itemChoice);
	//save player instance to global vector
	playerParty[intPlayer] = thePlayer;
	return true;
}

//int main() {
//	srand(time(NULL));
//	Player test("testname", 10, 10, 10,5);
//	Item testItem1("Fidget Spinner", 100, 50, 50, 50, true); //one time use item
//	Item testItem2("Health Potion", 100, 0, 0, 0, false); //permanent use item
//	test.addItem(testItem1);
//	test.addItem(testItem2);
//	//cout << test.characterAttack() << endl;
//	//cout << test.characterDefend() << endl;
//	Monster mob1("Testmob", 10, 10, 10);
//	Monster mob2("Testmob2", 100, 5, 5);
//	Monster mob3("Testmob3", 100, 5, 5, 3 );
//	//cout << mob1.characterAttack() << endl;
//	//cout << mob1.characterDefend() << endl;
//	vector<Player> plParty = { test };
//	vector<Monster> mbParty = { mob1,mob2 , mob3 };
//	Combat fight1(plParty, mbParty);
//	fight1.execute_Combat(plParty, mbParty);
//
//
//	system("pause");
//	return 0;
//}