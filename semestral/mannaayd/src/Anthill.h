#ifndef ANTHILL_H
#define ANTHILL_H

#include "Object.h"
#include "Table.h"

class Ant;

/**
 * @brief The class that represents the child of the parent class Object - Anthill
 */
class Anthill : public Object
{
public:
	/**
	 * @brief Standard constructor initializing new Anthill
	 *
	 * @param[in] Textures*	textures_				pointer to class that keeps all textures
	 * @param[in] position pos_					coordinate of Anthill
	 * @param[in] list <shared_ptr<Object>>& objects		list container that keep all objects
	 * @param[in] list <shared_ptr<Anthill>>& anthills		list container that keep all anthills
	 * @param[in] shared_ptr<Table> tables				pointer to Table
	 * @param[in] teams						team of Anthill
	 */
	Anthill(Textures* textures_, position pos_, list <shared_ptr<Object>>* objects, list <shared_ptr<Table>>* tables, list <shared_ptr<Anthill>>* anthills, shared_ptr<Table> table, teams team);
	/**
	 * @brief Method that sends ants to coordinate
	 *
	 * @param[in] position pos_					coordinate to send ants
	 */
	bool send_ants(position pos_);
	/**
	 * @brief Method that sends one ant to coordinate
	 *
	 * @param[in] position pos_					coordinate to send ant
	 */
	void send_to(position pos_);
	/**
	 * @brief Virtual method to update Anthill
	 */
	void update();
	/**
	 * @brief Virtual method to render Anthill
	 */
	void render();
	/**
	 * @brief Method that checks all objects around Anthill
	 *
	 * @param[in] position dest_					dest coordinate of Anthill
	 */
	void check_around(position dest_);
	/**
	 * @brief Method that checks if clear on a way to dest_ coordinate
	 *
	 * @param[in] position dest_					dest coordinate of Anthill
	 */
	bool check_if_clear(position dest_);
	/**
	 * @brief Virtual method that checks team of Anthill
	 * @return 							team of Ant
	 */
	teams check_team();
	/**
	 * @brief Virtual method that checks collisions with other objects 
	 * @param[in] teams team_		team of Object
	 * @param[in] position pos_		coordinate of Object that calls this function
	 * @param[in] position dest_		destination coordinate of Object that calls this function
	 * @param[in] position from_		coordinate of birth place of Object that calls this function
	 * @return				number of collision type
	 */
	int check_object_collision(teams team_, position pos_, position dest_, position from_);
	/**
	 * @brief Method that takes damage from enemy object
	 */
	void take_damage();
	int ants_count;
	int defence;

	teams team;
	shared_ptr<Table> table;
	list <shared_ptr<Table>>* tables;
	list <shared_ptr<Ant>> ants;
	list <shared_ptr<Anthill>>* anthills;
	list <shared_ptr<Object>>* objects;
private:
	unsigned int lastTimeA = 0;
	unsigned int lastTimeD = 0;
	
};

#endif
