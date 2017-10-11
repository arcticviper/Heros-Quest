#include "Player.h"

Player::Player () : Character(){
	intPrizeMoney = 0;
	intSpecialAttack = 0;
	boolUsedSpecialAttack = false;
}

Player::Player(std::string name, int health, int attack, int defence, int specialAttack) : Character(name, health, attack, defence){
	intPrizeMoney = 0;
	intSpecialAttack = specialAttack;
	boolUsedSpecialAttack = false;
}

int Player::specialAttack()
{
	boolUsedSpecialAttack = true;
	return (Player::characterAttack() + intSpecialAttack);
}

void Player::addStats(int health, int attack, int defence, int specialAttack){
	intHealth = intHealth + health;
	if (intHealth > 50) {
		intHealth = 50;
	}
	intAttack = intAttack + attack;
	if (intAttack > 10) {
		intAttack = 10;
	}
	intDefence = intDefence + defence;
	if (intDefence > 10) {
		intDefence = 10;
	}
	intSpecialAttack = intSpecialAttack + specialAttack;
	if (intSpecialAttack > 10) {
		intSpecialAttack = 10;
	}
}

void Player::replaceStats(int health, int attack, int defence, int specialAttack){
	intHealth = health;
	if (intHealth > 50) {
		intHealth = 50;
	}
	intAttack = attack;
	if (intAttack > 10) {
		intAttack = 10;
	}
	intDefence = defence;
	if (intDefence > 10) {
		intDefence = 10;
	}
	intSpecialAttack = specialAttack;
	if (intSpecialAttack > 10) {
		intSpecialAttack = 10;
	}
}

int Player::playerDodge()
{
	boolUsedDodge = true;
	return Player::characterDefend() + rand() % 6 + 1;
}