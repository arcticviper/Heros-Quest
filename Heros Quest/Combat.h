#ifndef COMBAT_H
#define COMBAT_H
#include <vector>
#include <iostream>
#include <string>
#include "Player.h"
#include "Monster.h"

class Combat{
public:
	Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter); // initiates combat sequence
	//~Combat(); // returns state to original
	//void combatSequence(Player playerAttacker, Monster mobDefender);
<<<<<<< HEAD
	void execute_Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter); // runs combat
	std::vector<Player> getPlayerResult() { return playerParty; }; //returns playerparty
	std::vector<Monster> getMonsterResult() { return monsterParty; }; //returns monsterparty
=======
	void execute_Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter);
	std::vector<Player> getPlayerResult() { return playerParty; };
	std::vector<Monster> getMonsterResult() { return monsterParty; };
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd

protected:

private:
	void playerCombat(Player thePlayer,int intPlayer); //displays combat options
	void monsterCombat(Monster theMonster,int intMonster); //displays combat options
	//void monsterCombat(); //Manages AI combat
	std::vector<Player> playerParty; //for holding players to easier manage players
	std::vector<Monster> monsterParty; //for holding monsters to easier manage monsters
	bool itemMenu(Player thePlayer, int intPlayer);
<<<<<<< HEAD
	
=======
>>>>>>> 8747f571685280f2a5599efe7e3336b41edd54bd
};

#endif