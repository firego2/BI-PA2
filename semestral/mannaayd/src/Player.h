#ifndef PLAYER_H

#define PLAYER_H

#include "Participant.h"
#include "Enemy.h"
class Enemy;

/**
 * @brief The class that represents the child of the parent class Participant - Player
 */
class Player : public Participant
{
public:
	/**
	 * @brief Standard constructor initializing new Player
	 *
	 * @param[in] teams team					team of Object
	 * list <shared_ptr<Anthill>>* anthills_			list container that keep all anthills
	 */
	Player(teams team, list <shared_ptr<Anthill>>* empty_hills);
	/**
	 * @brief Method that checks selected anthill if its blue
	 * @param[in] shared_ptr<Anthill> select	pointer to selected anthill
	 */
	void check_select(shared_ptr<Anthill> select);
	/**
	 * @brief Method that clear selected anthills
	 */
	void clear_select();
	/**
	 * @brief Method that checks selected anthills
	 * @return true or false
	 */
	bool is_selected();
	/**
	 * @brief Method that checks if player wins
	 * @return true or false
	 */
	bool is_win();
	/**
	 * @brief Method that attack from selected anthill to enemy anthill
	 */
	void send_attack();
	/**
	 * @brief Method that sets enemies of player
	 * @param[in] shared_ptr<Enemy> enemy1		enemy1
	 * @param[in] shared_ptr<Enemy> enemy2		enemy2
	 */
	void set_enemies(shared_ptr<Enemy> enemy1, shared_ptr<Enemy> enemy2);
	shared_ptr<Enemy> enemy1;
	shared_ptr<Enemy> enemy2;
	bool attacking = false;
private:	
	
};

#endif // !PLAYER_H
