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
	void execute_Combat(std::vector<Player> PlayableCharacter, std::vector<Monster> NonPlayableCharacter);
	std::vector<Player> getPlayerResult() { return playerParty; };
	std::vector<Monster> getMonsterResult() { return monsterParty; };

protected:

private:
	void playerCombat(Player thePlayer,int intPlayer); //displays combat options
	void monsterCombat(Monster theMonster,int intMonster); //displays combat options
	//void monsterCombat(); //Manages AI combat
	std::vector<Player> playerParty; //for holding players to easier manage players
	std::vector<Monster> monsterParty; //for holding monsters to easier manage monsters
	bool itemMenu(Player thePlayer, int intPlayer);
};

#endif