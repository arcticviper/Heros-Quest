#include "Combat.h"
#include <time.h>
using namespace std;

Combat::Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter){
	playerParty = PlayableCharacter;
	monsterParty = NonPlayableCharacter;
	//checks life of party
	while (playerParty.size() > 0 || monsterParty.size() > 0) {
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
				playerCombat(playerParty[i]); //runs combat options
			}
			//loops through mobs
			for (int i = 0; i < monsterParty.size(); i++) {
				//cout << monsterParty[i].getHealth() << endl;
				//monsterCombat();
			}
		}
	}
}

void Combat::playerCombat(Player thePlayer){
	Monster mobParty; //used for selecting monster
	int intMonsterChoice = 0; // int version of monster choice
	int intPlayerOption = 0;
	int intAttackChoice = 0;
	bool boolValidChoice = false; //ensuring choice is valid
	//selecting monster
	cout << "Which monster do you want to attack?" << endl;
	for (int i = 0; i < monsterParty.size(); i++) {
		cout << i + 1 << ". HP: "<< monsterParty[i].getHealth() << "\t" << "Name: " << monsterParty[i].getName() << endl; //displays as: 1. HP: 99	Name: Mobname
	}
	//while monsterchoice is greater than 0 and less than or equal to party size, ask for input
	while (boolValidChoice == false) {
		intMonsterChoice = int(makeCharChoice("What monster would you like to select?") - '0');
		if ((intMonsterChoice > 0) && (intMonsterChoice <= monsterParty.size())) {
			boolValidChoice = true;
		}
	}
	boolValidChoice = false;
	intMonsterChoice = intMonsterChoice - 1;

	cout << "You have selected: " << monsterParty[intMonsterChoice].getName() << endl << endl;

	//display menu
	cout << "1. Light Attack (2-4 + Attack)" << endl; //modified attack for players for lower risk, lower damage
	cout << "2. Heavy Attack (1-6 + Attack)" << endl; //standard attack for players
	cout << "3. Special attack (Heavy Attack + Sp.Attack)" << endl; //special attack, can only be used once per combat
	cout << "4. Dodge (Buff Defence by 1-6, 0 dmg)" << endl; //buffs defence by 1-6 points for single round but deals no damage
	cout << "5. Item" << endl; //Opens item inventory, if item is used, sacrifice turn
	cout << "6. Save (saves current level+stats)" << endl; //Saves current game, not current state

	//asks for input
	
	while (boolValidChoice == false) {
		intPlayerOption = int(makeCharChoice("What would you like to select?") - '0');
		if ((intPlayerOption > 0) && (intPlayerOption <= 6)) {
			boolValidChoice = true;
		}
	}
	switch (intPlayerOption) {
	case 1: monsterParty[intMonsterChoice].takeDamage(thePlayer.characterAttack(2,4));
		break;
	case 2: monsterParty[intMonsterChoice].takeDamage(thePlayer.characterAttack());
		break;
	case 3: monsterParty[intMonsterChoice].takeDamage(thePlayer.specialAttack());
		break;
	case 4: thePlayer.playerDodge();
		break;
	case 5: itemMenu(thePlayer);
		break;
	case 6:
		break;
	}
	if (monsterParty[intMonsterChoice].getHealth() <= 0) {
		cout << "The monster is dead";
		monsterParty.erase(monsterParty.begin() + intMonsterChoice);
	}

}
void Combat::monsterCombat(Monster theMonster){
	// Randomly generates the player that will be attacking
	int intPlayerChoice;
	intPlayerChoice = rand() % playerParty.size();
	// Attacks the player
	playerParty[intPlayerChoice].takeDamage(theMonster.characterAttack());
}
void Combat::itemMenu(Player thePlayer){
	thePlayer;
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
	//cout << test.characterAttack() << endl;
	//cout << test.characterDefend() << endl;
	Monster mob1("Testmob", 10, 10, 10, 100);
	//cout << mob1.characterAttack() << endl;
	//cout << mob1.characterDefend() << endl;
	vector<Player> plParty = { test };
	vector<Monster> mbParty = { mob1 };
	Combat fight1(plParty, mbParty);


	system("pause");
	return 0;
}