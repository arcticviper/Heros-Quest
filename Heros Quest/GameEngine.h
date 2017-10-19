#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Combat.h"


class GameEngine
{
public:
	GameEngine(); //initialise
	~GameEngine();
	void PlayGame(); //Play game
	void Basic(); //Basic Mode, 1pv1m standard drop rates
	void Easy(); //Easy mode, 4pv1m increased drop rates
	void Normal(); //Normal mode, 4pv4m standard drop rates
	void Hard(); //Hard mode, 1pv4m lowered drop rates
	void FillLoot(); //Fill loot vector with items
	std::string getMonsterName(int mobLevel); //gets a random monster name depending on the level of the monster
	Item GetLoot(); //gets a single item from the loot vector
	Player allocateSkills(Player tempPlayer); //used for skill allocation for the player

private:
	void FillNames();
	std::vector<Player*> Players;
	std::vector<Monster*> Monsters;
	std::vector<Item*> Loot;
	std::vector<std::vector<std::string>> Name;
	int getRandom(int min, int max);
};

#endif // !
