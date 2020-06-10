#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "Anthill.h"
#include "Game.h"
#include <list>

/**
 * @brief The class that represents the parent class of player and enemies - Participant
 */
class Participant
{
public:	
	/**
	 * @brief Standard constructor initializing new Participant
	 *
	 * @param[in] teams team					team of Object
	 * list <shared_ptr<Anthill>>* anthills_			list container that keep all anthills
	 */
	Participant(teams team, list <shared_ptr<Anthill>>* anthills);
	list <shared_ptr<Anthill>> *anthills;
	bool is_defeated();
	bool defeated = false;
	int count_hills;
protected:	
	teams team;	
	
	shared_ptr<Anthill> selectedhill = nullptr;
	shared_ptr<Anthill> enemyhill = nullptr;
};


#endif // !PARTICIPANT_H
