#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "Participant.h"

class Player;

/**
 * @brief The class that represents the child of the parent class Participant - Enemy
 */
class Enemy : public Participant
{
public:
	/**
	 * @brief Standard constructor initializing new Enemy
	 *
	 * @param[in] teams team					team of Object
	 * list <shared_ptr<Anthill>>* anthills_			list container that keep all anthills
	 */
	Enemy(teams team, list <shared_ptr<Anthill>>* anthills);
	/**
	 * @brief Method that sets enemies of player
	 * @param[in] shared_ptr<Player> enemy1		enemy1
	 * @param[in] shared_ptr<Enemy> enemy2		enemy2
	 */
	void set_enemies(shared_ptr<Player> enemy1, shared_ptr<Enemy> enemy2);
	/**
	 * @brief Method that imits intelligence
	 */
	void ai();
	
	shared_ptr<Player> enemy1;
	shared_ptr<Enemy> enemy2;
private:
	unsigned int lastAction = 0;
	int ants_to_send = 0;
};

#endif // !ENEMY_H
