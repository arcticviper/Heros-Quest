#include "GameEngine.h"
#include "InputFunctions.h"
#include <iostream>
#include <time.h>
using namespace std;

GameEngine::GameEngine(){
	//initalise empty vectors for storing players/monsters
	Players = {};
	Monsters = {};
	//Loot = {};
	//populate items, may change in future
	vector<Item*> tempLoot = FillLoot();
	Loot.insert(Loot.begin(), tempLoot.begin(), tempLoot.end());
	srand(time(NULL)); //initialises random items

}

void GameEngine::PlayGame(){
	int modes;
	cout << "Welcome to Hero's Quest!" << endl;
	cout << "There are 4 Different modes:" << endl;
	//display menu
	cout << endl;
	cout << "1. Basic Mode - 1 on 1 combat with standard drop rates." << endl; // 50% item loot
	cout << "2. Easy Mode - 4 on 1 combat with increased drop rates." << endl; // 75% item loot
	cout << "3. Normal Mode - 4 on 4 combat with standard drop rates." << endl; // 50% item loot
	cout << "4. Hard Mode - 1 on 4 combat with lowered drop rates." << endl; // 25% item loot
	//cout << "5. Custom Modes - Unique Challenges" << endl; //1 defence challenge, ect
	modes = makeIntChoice("Which mode would you like to select?", 1, 4);
	switch (modes)
	{
	case 1:
		Basic();
	case 2:
		//Easy();
	case 3:
		//Normal();
	case 4:
		//Hard();
	default:
		break;
	}
}

void GameEngine::Basic(){
	
	//populate enemies
	Monsters.push_back(new Monster("Monster 1", 10, 1, 1, 0));
	Monsters.push_back(new Monster("Monster 2", 20, 3, 2, 0));
	Monsters.push_back(new Monster("Monster 3", 30, 5, 4, 0));
	Monsters.push_back(new Monster("Monster 4", 40, 6, 7, 0));
	Monsters.push_back(new Monster("Monster 5", 50, 8, 8, 5));
	//get player name
	string PlayerName = makeStringChoice("What is your name?");
	//Add player
	Players.push_back(new Player(PlayerName, 20, 3, 3, 2));
	//Give a random item to start with
<<<<<<< HEAD
	Players[0]->addItem(new Item (GetLoot()));
=======
	Players[0]->addItem(GetLoot());
	//while both vectors are not empty
>>>>>>> parent of 23824e3... 15/10 - Completed easy
	vector<Player> SinglePlayer;
	vector<Monster> SingleMonster;
	while (Monsters.size() > 0 && Players.size() > 0){
		//store players/monsters in temp vector
		SinglePlayer.push_back(*Players[0]);
		SingleMonster.push_back(*Monsters[0]);
		//initialise combat
		cout << SinglePlayer[0].getHealth();
		Combat SingleFight(SinglePlayer, SingleMonster);
		cout << SinglePlayer[0].getHealth();
		//instance combat
		SingleFight.execute_Combat(SinglePlayer, SingleMonster);
		//return the current state of player
		SinglePlayer = SingleFight.getPlayerResult();
		SingleMonster = SingleFight.getMonsterResult();
		//check if player has won
		if (SingleMonster.size() == 0) {
			cout << "You won the battle!" << endl;
			//get prize money
			SinglePlayer[0].addMoney(SinglePlayer[0].getHealth());
			//add 20 health
			SinglePlayer[0].addStats(20, 0, 0, 0);
			//removes monster
			Monsters.erase(Monsters.begin());
		}
<<<<<<< HEAD
		//give player skills to add
		SinglePlayer[0] = allocateSkills(SinglePlayer[0]);
		//give 50% chance of loot by rolling intLoopChance
		int intLootChance;
		intLootChance = rand() % + 101;
		if (intLootChance > 50) {
			SinglePlayer[0].addItem(new Item(GetLoot()));
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
	Monsters.push_back(new Monster("Monster 1", 10, 1, 1, 0));
	Monsters.push_back(new Monster("Monster 2", 20, 3, 2, 0));
	Monsters.push_back(new Monster("Monster 3", 30, 5, 4, 0));
	Monsters.push_back(new Monster("Monster 4", 40, 6, 7, 0));
	Monsters.push_back(new Monster("Monster 5", 50, 8, 8, 5));
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
		Players[0]->addItem(new Item(GetLoot()));
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
=======

		else if (SinglePlayer.size() == 0) {
>>>>>>> parent of 23824e3... 15/10 - Completed easy
			cout << "You lose!" << endl;
			cout << "Game over!" << endl;
			break;
		}
		//give player skills to add

		//give 50% chance of loot
		int intLootChance;
<<<<<<< HEAD
		for (int i = 0; i < PlayerTeam.size(); i++) {
			intLootChance = rand() % +101;
			if (intLootChance > 75) {
				PlayerTeam[0].addItem(new Item(GetLoot()));
			}
		}
		//save the players state;
		for (int i = 0; i < PlayerTeam.size(); i++) {
			*Players[i] = PlayerTeam[i];
		}
		//clear vectors
		PlayerTeam.erase(PlayerTeam.begin());
		//SingleMonster.erase(SingleMonster.begin());
	}
	if (Players.size() > 0) {
		cout << "Congratulations!" << endl;
		cout << "You win!" << endl;
		int totalScore = 0;
		for (int i = 0; i < Players.size(); i++) {
			totalScore = totalScore + Players[i]->getMoney();
=======
		intLootChance = rand() % 0 + 101;
		if (intLootChance > 50); {
			Players[0]->addItem(GetLoot());
>>>>>>> parent of 23824e3... 15/10 - Completed easy
		}
	}
	


}

vector<Item*> GameEngine::FillLoot(){
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

	Items.insert(Items.end(), Potions.begin(), Potions.end());
	Items.insert(Items.end(), Armour.begin(), Armour.end());
	Items.insert(Items.end(), Weapons.begin(), Weapons.end());
	return Items;
}

Item GameEngine::GetLoot()
{
	int intLoot;
	intLoot = rand() % Loot.size();
	Item tempItem = *Loot[intLoot];
	return tempItem;
}

int main() {
	GameEngine newGame;
	newGame.PlayGame();

	system("pause");
	return 0;
}