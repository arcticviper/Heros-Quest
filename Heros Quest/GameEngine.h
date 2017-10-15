#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Combat.h"


class GameEngine
{
public:
	GameEngine(); //initialise
	// ~GameEngine();
	void PlayGame(); //Play game
	void Basic(); //Basic Mode, 1pv1m standard drop rates
	void Easy(); //Easy mode, 4pv1m increased drop rates
	void Normal(); //Normal mode, 4pv4m standard drop rates
	void Hard(); //Hard mode, 1pv4m lowered drop rates
	std::vector<Item*> FillLoot(); //Fill loot vector with items
	Item GetLoot(); //Fill loot vector with items
	Player allocateSkills(Player tempPlayer);

private:
	std::vector<Player*> Players;
	std::vector<Monster*> Monsters;
	std::vector<Item*> Loot;
};

#endif // !
