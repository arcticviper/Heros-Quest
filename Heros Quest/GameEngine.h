#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Combat.h"


class GameEngine
{
public:
	GameEngine(); //initialise
	// ~GameEngine();
	void PlayGame(); //Play game
	void Basic(); //Basic Mode, 1v1 standard drop rates
	void Easy(); //Easy mode, 4v1 increased drop rates
	void Normal(); //Normal mode, 4v4 standard drop rates
	void Hard(); //Hard mode, 1v4 lowered drop rates
	std::vector<Item*> FillLoot(); //Fill loot vector with items
	Item GetLoot(); //Fill loot vector with items

private:
	std::vector<Player*> Players;
	std::vector<Monster*> Monsters;
	std::vector<Item*> Loot;
};

#endif // !
