#include "GameEngine.h"
#include "InputFunctions.h"
#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;

GameEngine::GameEngine(){
	//initalise empty vectors for storing players/monsters
	Players = {};
	Monsters = {};
	//populate items, may change in future
	Loot = {};
	FillLoot();
	//vector<Item*> tempLoot = FillLoot();
	//populate monster names
	FillNames();
	srand(time(NULL)); //initialises random items

}

GameEngine::~GameEngine()
{
	for (int i = 0; i < Players.size(); i++) {
		delete Players[i];
	}
	for (int i = 0; i < Monsters.size(); i++) {
		delete Monsters[i];
	}
	for (int i = 0; i < Loot.size(); i++) {
		delete Loot[i];
	}

}

void GameEngine::PlayGame(){
	int modes;
	cout << "Welcome to Hero's Quest!" << endl;
	cout << "There are 4 Different modes:" << endl;
	//display menu
	cout << endl;
	cout << "1. Basic Mode - 1 on 1 combat with standard drop rates. Fixed monster stats" << endl; // 50% item loot
	cout << "2. Easy Mode - 4 on 1 combat with increased drop rates. Fixed monster stats" << endl; // 75% item loot
	cout << "3. Normal Mode - 4 on 4 combat with standard drop rates. Random monster stats" << endl; // 50% item loot
	cout << "4. Hard Mode - 1 on 4 combat with lowered drop rates. Random monster stats" << endl; // 25% item loot
	//cout << "5. Custom Modes - Unique Challenges" << endl; //1 defence challenge, ect
	modes = makeIntChoice("Which mode would you like to select?", 1, 4);
	switch (modes)
	{
	case 1:
		Basic();
		break;
	case 2:
		Easy();
		break;
	case 3:
		Normal();
		break;
	case 4:
		Hard();
		break;
	default:
		break;
	}
}

void GameEngine::Basic(){
	//populate enemies
	Monsters.push_back(new Monster(getMonsterName(0), 10, 1, 1, 0));
	Monsters.push_back(new Monster(getMonsterName(1), 20, 3, 2, 0));
	Monsters.push_back(new Monster(getMonsterName(2), 30, 5, 4, 0));
	Monsters.push_back(new Monster(getMonsterName(3), 40, 6, 7, 0));
	Monsters.push_back(new Monster(getMonsterName(4), 50, 8, 8, 5));
	//get player name
	string PlayerName = makeStringChoice("What is your name?");
	//Add player
	Players.push_back(new Player(PlayerName, 20, 3, 3, 2));

	//Give a random item to start with
	Players[0]->addItem(GetLoot());
	vector<Player> SinglePlayer;
	vector<Monster> SingleMonster;
	while (Monsters.size() > 0 && Players.size() > 0){
		//store instance players/monsters in temp vector
		SinglePlayer.push_back(*Players[0]);
		SingleMonster.push_back(*Monsters[0]);
		//initialise combat
		Combat SingleFight(SinglePlayer, SingleMonster);
		//instance combat
		SingleFight.execute_Combat(SinglePlayer, SingleMonster);
		//checks if player has lost
		if (SingleFight.getPlayerResult().size() == 0) {
			cout << "You lose!" << endl;
			cout << "Game over!" << endl;
			cout << "Your final score was: " << SinglePlayer[0].getMoney() << endl;
			Players.clear();
			break;
		}
		//return/overwrites the current state of player
		SinglePlayer = SingleFight.getPlayerResult();
		SingleMonster = SingleFight.getMonsterResult();
		//check if player has won
		if (SingleFight.getMonsterResult().size() == 0) {
			cout << "You won the battle!" << endl;
			//get prize money
			SinglePlayer[0].addMoney(SinglePlayer[0].getHealth());
			//add 20 health
			SinglePlayer[0].addStats(20, 0, 0, 0);
			//delete pointer location
			delete Monsters[0];
			//removes monster from monsters vector
			Monsters.clear();
		}
		//give player skills to add
		SinglePlayer[0] = allocateSkills(SinglePlayer[0]);
		//give 50% chance of loot by rolling intLoopChance
		int intLootChance;
		intLootChance = getRandom(0, 100);
		if (intLootChance > 50) {
			SinglePlayer[0].addItem(GetLoot());
		}
		//save the players state;
		*Players[0] = SinglePlayer[0];
		//clear vectors
		SinglePlayer.erase(SinglePlayer.begin());
		//SingleMonster.erase(SingleMonster.begin());
	}
	if (Players.size() > 0) {
		cout << "Congratulations!" << endl;
		cout << "You win!" << endl;
		int totalScore = 0;
		for (int i = 0; i < Players.size(); i++) {
			totalScore = totalScore + Players[i]->getMoney();
		}
		//add 50 points for winning
		totalScore = totalScore + 50;
		cout << "Your final score was: " << totalScore << endl;
	}
	


}

void GameEngine::Easy(){
	//populate enemies
	Monsters.push_back(new Monster(getMonsterName(0), 10, 1, 1, 0));
	Monsters.push_back(new Monster(getMonsterName(1), 20, 3, 2, 0));
	Monsters.push_back(new Monster(getMonsterName(2), 30, 5, 4, 0));
	Monsters.push_back(new Monster(getMonsterName(3), 40, 6, 7, 0));
	Monsters.push_back(new Monster(getMonsterName(4), 50, 8, 8, 5));
	//get player name/add 4 players
	stringstream sstream;
	for (int i = 0; i < 4; i++) {
		sstream << "What is your name Player " << i + 1 << " ?";
		string PlayerName = makeStringChoice(sstream.str());
		Players.push_back(new Player(PlayerName, 20, 3, 3, 2));
		sstream.str("");
	}
	

	//Give a random item to start with
	for (int i = 0; i < Players.size(); i++) {
		Players[i]->addItem(GetLoot());
	}
	vector<Player> PlayerTeam;
	vector<Monster> SingleMonster;
	while (Monsters.size() > 0 && Players.size() > 0) {
		//store instance players/monsters in temp vector
		for (int i = 0; i < Players.size(); i++) {
			PlayerTeam.push_back(*Players[i]);
		}
		SingleMonster.push_back(*Monsters[0]);
		//initialise combat
		Combat SingleFight(PlayerTeam, SingleMonster);
		//instance combat
		SingleFight.execute_Combat(PlayerTeam, SingleMonster);
		//checks if player has lost
		if (SingleFight.getPlayerResult().size() == 0) {
			cout << "You lose!" << endl;
			cout << "Game over!" << endl;
			int totalScore = 0;
			for (int i = 0; i < PlayerTeam.size(); i++) {
				totalScore = totalScore + PlayerTeam[i].getMoney();
			}
			cout << "Your final score was: " << totalScore << endl;
			//removes players
			Players.clear();
			break;
		}
		//return/overwrites the current state of player
		PlayerTeam = SingleFight.getPlayerResult();
		SingleMonster = SingleFight.getMonsterResult();
		//check if player has won
		if (SingleFight.getMonsterResult().size() == 0) {
			cout << "You won the battle!" << endl;
			//get prize money for all players
			for (int i = 0; i < PlayerTeam.size(); i++) {
				PlayerTeam[i].addMoney(PlayerTeam[i].getHealth());
			}
			//add 20 health
			for (int i = 0; i < PlayerTeam.size(); i++) {
				PlayerTeam[0].addStats(20, 0, 0, 0);
			}
			//delete pointer location
			delete Monsters[0];
			//removes monster from monsters vector
			Monsters.erase(Monsters.begin());
		}
		//give player skills to add
		for (int i = 0; i < PlayerTeam.size(); i++) {
			PlayerTeam[i] = allocateSkills(PlayerTeam[i]);
		}
		//give 75% chance of loot by rolling intLoopChance
		int intLootChance;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			intLootChance = getRandom(0, 100);
			if (intLootChance > 25) {
				PlayerTeam[0].addItem(GetLoot());
			}
		}
		//save the players state;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			*Players[i] = PlayerTeam[i];
		}
		//clear vectors
		PlayerTeam.clear();
		//SingleMonster.erase(SingleMonster.begin());
	}
	if (Players.size() > 0) {
		cout << "Congratulations!" << endl;
		cout << "You win!" << endl;
		int totalScore = 0;
		for (int i = 0; i < Players.size(); i++) {
			totalScore = totalScore + Players[i]->getMoney();
		}
		//add 50 points for winning
		totalScore = totalScore + 50;
		cout << "Your final score was: " << totalScore << endl;
	}



}

void GameEngine::Normal()
{
	//populate enemies
	for (int i = 0; i < 4; i++) {
		//creates monster with atk stats ranging from 1-2,def stats ranging 1-2 and sp atk stats ranging 0-1
		Monsters.push_back(new Monster(getMonsterName(0), 10, getRandom(1, 1), getRandom(1, 1), getRandom(0, 1)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with atk stats ranging from 2-4,def stats ranging 2-4 and sp atk stats ranging 1-2
		Monsters.push_back(new Monster(getMonsterName(1), 20, getRandom(2, 2), getRandom(2, 2), getRandom(1, 1)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with atk stats ranging from 4-5,def stats ranging 4-5 and sp atk stats ranging 1-3
		Monsters.push_back(new Monster(getMonsterName(2), 30, getRandom(4, 1), getRandom(4, 1), getRandom(1, 2)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with hp ranging from 35-45, atk stats ranging from 5-7,def stats ranging 5-7 and sp atk stats ranging 2-3
		Monsters.push_back(new Monster(getMonsterName(3), getRandom(35, 10), getRandom(5, 7), getRandom(5, 7), getRandom(2, 1)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with hp ranging from 45-55, atk stats ranging from 7-9,def stats ranging 7-9 and sp atk stats ranging 3-6
		Monsters.push_back(new Monster(getMonsterName(4), getRandom(45, 10), getRandom(7, 2), getRandom(7, 2), getRandom(3, 3)));
	}
	//get player name/add 4 players
	stringstream sstream;
	for (int i = 0; i < 4; i++) {
		sstream << "What is your name Player " << i + 1 << " ?";
		string PlayerName = makeStringChoice(sstream.str());
		Players.push_back(new Player(PlayerName, 20, 3, 3, 2));
		sstream.str("");
	}


	//Give a random item to start with
	for (int i = 0; i < Players.size(); i++) {
		Players[i]->addItem(GetLoot());
	}
	vector<Player> PlayerTeam;
	vector<Monster> MonsterTeam;
	while (Monsters.size() > 0 && Players.size() > 0) {
		//store instance players/monsters in temp vector
		for (int i = 0; i < Players.size(); i++) {
			PlayerTeam.push_back(*Players[i]);
		}
		for (int i = 0; i < 4; i++) {
			MonsterTeam.push_back(*Monsters[i]);
		}
		//initialise combat
		Combat SingleFight(PlayerTeam, MonsterTeam);
		//instance combat
		SingleFight.execute_Combat(PlayerTeam, MonsterTeam);
		//checks if player has lost
		if (SingleFight.getPlayerResult().size() == 0) {
			cout << "You lose!" << endl;
			cout << "Game over!" << endl;
			int totalScore = 0;
			for (int i = 0; i < PlayerTeam.size(); i++) {
				totalScore = totalScore + PlayerTeam[i].getMoney();
			}
			cout << "Your final score was: " << totalScore << endl;
			Players.clear();
			break;
		}
		//return/overwrites the current state of player
		PlayerTeam = SingleFight.getPlayerResult();
		MonsterTeam = SingleFight.getMonsterResult();
		//check if player has won
		if (SingleFight.getMonsterResult().size() == 0) {
			cout << "You won the battle!" << endl;
			//get prize money for all players
			for (int i = 0; i < PlayerTeam.size(); i++) {
				PlayerTeam[i].addMoney(PlayerTeam[i].getHealth());
			}
			//add 20 health
			for (int i = 0; i < PlayerTeam.size(); i++) {
				PlayerTeam[i].addStats(20, 0, 0, 0);
			}
			//delete pointer location
			for (int i = 0; i < 4; i++) {
				delete Monsters[i];
			}
			//removes 4 monsters from monsters vector
			Monsters.erase(Monsters.begin(), Monsters.begin()+4);
		}
		//give player skills to add
		for (int i = 0; i < PlayerTeam.size(); i++) {
			PlayerTeam[i] = allocateSkills(PlayerTeam[i]);
		}
		//give 50% chance of loot by rolling intLoopChance
		int intLootChance;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			intLootChance = getRandom(0, 100);
			if (intLootChance > 50) {
				PlayerTeam[i].addItem(GetLoot());
			}
		}
		//save the players state;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			*Players[i] = PlayerTeam[i];
		}
		//clear vectors
		PlayerTeam.clear();
	}
	if (Players.size() > 0) {
		cout << "Congratulations!" << endl;
		cout << "You win!" << endl;
		int totalScore = 0;
		for (int i = 0; i < Players.size(); i++) {
			totalScore = totalScore + Players[i]->getMoney();
		}
		//add 70 points for winning
		totalScore = totalScore + 70;
		cout << "Your final score was: " << totalScore << endl;
	}
}

void GameEngine::Hard()
{
	//populate enemies
	for (int i = 0; i < 4; i++) {
		//creates monster with atk stats ranging from 1-2,def stats ranging 1-2 and sp atk stats ranging 0-1
		Monsters.push_back(new Monster(getMonsterName(0), 10, getRandom(1, 1), getRandom(1, 1), getRandom(0, 1)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with atk stats ranging from 2-4,def stats ranging 2-4 and sp atk stats ranging 1-2
		Monsters.push_back(new Monster(getMonsterName(1), 20, getRandom(2, 2), getRandom(2, 2), getRandom(1, 1)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with atk stats ranging from 4-5,def stats ranging 4-5 and sp atk stats ranging 1-3
		Monsters.push_back(new Monster(getMonsterName(2), 30, getRandom(4, 1), getRandom(4, 1), getRandom(1, 2)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with hp ranging from 35-45, atk stats ranging from 5-7,def stats ranging 5-7 and sp atk stats ranging 2-3
		Monsters.push_back(new Monster(getMonsterName(3), getRandom(35, 10), getRandom(5, 7), getRandom(5, 7), getRandom(2, 1)));
	}
	for (int i = 0; i < 4; i++) {
		//creates monster with hp ranging from 45-55, atk stats ranging from 7-9,def stats ranging 7-9 and sp atk stats ranging 3-6
		Monsters.push_back(new Monster(getMonsterName(4), getRandom(45, 10), getRandom(7, 2), getRandom(7, 2), getRandom(3, 3)));
	}
	//get player name/add 1 player
	stringstream sstream;
	for (int i = 0; i < 1; i++) {
		sstream << "What is your name Player " << i + 1 << " ?";
		string PlayerName = makeStringChoice(sstream.str());
		Players.push_back(new Player(PlayerName, 20, 4, 4, 4));
		sstream.str("");
	}


	//Give a random item to start with
	for (int i = 0; i < Players.size(); i++) {
		Players[i]->addItem(GetLoot());
	}
	vector<Player> PlayerTeam;
	vector<Monster> MonsterTeam;
	while (Monsters.size() > 0 && Players.size() > 0) {
		//store instance players/monsters in temp vector
		for (int i = 0; i < Players.size(); i++) {
			PlayerTeam.push_back(*Players[i]);
		}
		for (int i = 0; i < 4; i++) {
			MonsterTeam.push_back(*Monsters[i]);
		}
		//initialise combat
		Combat SingleFight(PlayerTeam, MonsterTeam);
		//instance combat
		SingleFight.execute_Combat(PlayerTeam, MonsterTeam);
		//checks if player has lost
		if (SingleFight.getPlayerResult().size() == 0) {
			cout << "You lose!" << endl;
			cout << "Game over!" << endl;
			int totalScore = 0;
			for (int i = 0; i < PlayerTeam.size(); i++) {
				totalScore = totalScore + PlayerTeam[i].getMoney();
			}
			cout << "Your final score was: " << totalScore << endl;
			Players.clear();
			break;
		}
		//return/overwrites the current state of player
		PlayerTeam = SingleFight.getPlayerResult();
		MonsterTeam = SingleFight.getMonsterResult();
		//check if player has won
		if (SingleFight.getMonsterResult().size() == 0) {
			cout << "You won the battle!" << endl;
			//get prize money for all players
			for (int i = 0; i < PlayerTeam.size(); i++) {
				PlayerTeam[i].addMoney(PlayerTeam[i].getHealth());
			}
			//add 20 health
			for (int i = 0; i < PlayerTeam.size(); i++) {
				PlayerTeam[i].addStats(20, 0, 0, 0);
			}
			//delete pointer location
			for (int i = 0; i < 4; i++) {
				delete Monsters[i];
			}
			//removes 4 monsters from monsters vector
			Monsters.erase(Monsters.begin(), Monsters.begin() + 4);
		}
		//give player skills to add
		for (int i = 0; i < PlayerTeam.size(); i++) {
			PlayerTeam[i] = allocateSkills(PlayerTeam[i]);
		}
		//give 25% chance of loot by rolling intLoopChance
		int intLootChance;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			intLootChance = getRandom(0, 100);
			if (intLootChance > 75) {
				PlayerTeam[0].addItem(GetLoot());
			}
		}
		//save the players state;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			*Players[i] = PlayerTeam[i];
		}
		//clear vectors
		PlayerTeam.clear();
	}
	if (Players.size() > 0) {
		cout << "Congratulations!" << endl;
		cout << "You win!" << endl;
		int totalScore = 0;
		for (int i = 0; i < Players.size(); i++) {
			totalScore = totalScore + Players[i]->getMoney();
		}
		//add 70 points for winning
		totalScore = totalScore + 70;
		cout << "Your final score was: " << totalScore << endl;
	}
}

void GameEngine::FillLoot(){
	vector<Item*> Items; // all Items
	vector<Item*> Potions; // potions
	//health potions
	Potions.push_back(new Item("Red Potion", 5, 0, 0, 0, true));
	Potions.push_back(new Item("Orange Potion", 15, 0, 0, 0, true));
	Potions.push_back(new Item("White Potion", 30, 0, 0, 0, true));
	Potions.push_back(new Item("Cheese Wheel", 50, 0, 0, 0, true));
	//Combat potions
	Potions.push_back(new Item("Attack Potion", 0, 5, 0, 0, true));
	Potions.push_back(new Item("Defence Potion", 0, 0, 5, 0, true));
	Potions.push_back(new Item("Special Attack Potion", 0, 0, 0, 5, true));
	
	vector<Item*> Armour; // armours
	//Armour
	Armour.push_back(new Item("Ring of Dormor", 0, 1, 1, 1, false));
	Armour.push_back(new Item("Helmet of Baraduns", 0, 0, 2, 0, false));
	Armour.push_back(new Item("Breastplate of Argon", 0, 0, 3, 0, false));
	
	vector<Item*> Weapons; // armours
	//Weapons
	Weapons.push_back(new Item("Butterfly Net", 0, 1, 0, 0, false));
	Weapons.push_back(new Item("Staff of Netherwind", 0, 2, 0, 0, false));
	Weapons.push_back(new Item("Bow of Darkwood", 0, 3, 0, 0, false));
	//insert all items into loot
	Items.insert(Items.end(), Potions.begin(), Potions.end());
	Items.insert(Items.end(), Armour.begin(), Armour.end());
	Items.insert(Items.end(), Weapons.begin(), Weapons.end());

	Loot.insert(Loot.end(), Items.begin(), Items.end());
}

void GameEngine::FillNames()
{
	//allow for 5 levels
	Name.resize(5);
	//level 1
	Name[0].push_back("Chicken");
	Name[0].push_back("Rat");
	Name[0].push_back("Cow");
	Name[0].push_back("Giant Spider");
	//level 2
	Name[1].push_back("Minotaur");
	Name[1].push_back("Hill Giant");
	Name[1].push_back("Moss Giant");
	Name[1].push_back("Angry Dwarf");
	//level 3 monsters
	Name[2].push_back("Baby Green Dragon");
	Name[2].push_back("Baby Blue Dragon");
	Name[2].push_back("Baby Red Dragon");
	Name[2].push_back("Baby Black Dragon");
	//level 4 monsters
	Name[3].push_back("Green Dragon");
	Name[3].push_back("Blue Dragon");
	Name[3].push_back("Red Dragon");
	Name[3].push_back("Black Dragon");
	//level 5 monsters
	Name[4].push_back("King Green Dragon");
	Name[4].push_back("King Blue Dragon");
	Name[4].push_back("King Red Dragon");
	Name[4].push_back("King Black Dragon");
}

int GameEngine::getRandom(int min, int minplus)
{
		return rand() % minplus + min;
}

string GameEngine::getMonsterName(int mobLevel)
{
	return Name[mobLevel][rand() % Name[mobLevel].size()];
}

Item GameEngine::GetLoot()
{
	int intLoot;
	intLoot = rand() % Loot.size();
	Item tempItem = *Loot[intLoot];
	return tempItem;
}

Player GameEngine::allocateSkills(Player tempPlayer)
{
	int intSkills;
	int skillChoice;
	//randomise the chance for skills up to 7
	intSkills = rand() % + 7;
	cout << "You have received " << intSkills << " skill points." << endl;
	//if skills received is greater than 0
	while (intSkills > 0)
	{
		cout << "You have: " << intSkills << " points remaining." << endl;
		//display menu
		cout << "1. Attack: \t\t Currently:" << tempPlayer.getAttack() << endl;
		cout << "2. Defence:\t\t Currently:" << tempPlayer.getDefence() << endl;
		cout << "3. SpecialAttack: \t Currently:" << tempPlayer.getSpecialAttack() << endl;
		skillChoice = makeIntChoice("Which skill would you like to allocate your points to? (Max is 10)", 1, 3);
		switch (skillChoice){
		case 1:
			tempPlayer.addStats(0, 1, 0, 0);
			intSkills--;
			break;
		case 2:
			tempPlayer.addStats(0, 0, 1, 0);
			intSkills--;
			break;
		case 3:
			tempPlayer.addStats(0, 0, 0, 1);
			intSkills--;
			break;
		default:
			break;
		}
		//break out of while loop if all stats are maxed
		if (tempPlayer.getAttack() == 10 && tempPlayer.getDefence() == 10 && tempPlayer.getSpecialAttack() == 10)
		{
			break;
		}
	}
	return tempPlayer;
}

int main() {
	GameEngine newGame;
	newGame.PlayGame();

	system("pause");
	return 0;
}