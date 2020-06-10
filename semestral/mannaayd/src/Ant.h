#ifndef ANT_H

#define ANT_H

#include "Object.h"
#include "Anthill.h"

/**
 * @brief The class that represents the child of the parent class Object - Ant
 */
class Ant : public Object
{
public:
	/**
	 * @brief Standard constructor initializing new Ant
	 *
	 * @param[in] Textures*	textures_				pointer to class that keeps all textures
	 * @param[in] position pos_					coordinate of Ant
	 * @param[in] position dest_					destination coordinate of Ant
	 * @param[in] teams team_					team of Anthill
	 * @param[in] list <shared_ptr<Object>>& objects		list container that keep all objects
	 * @param[in] list <shared_ptr<Ant>>& brothers			list container that keep all ants from same Anthill
	 * @param[in] Anthill* home_					pointer to home Anthill
	 */
	Ant(Textures* textures_, position pos_, position dest_, teams team_, list <shared_ptr<Object>>* objects_, list <shared_ptr<Ant>>* brothers_,  Anthill* home_);
	/**
	 * @brief Standart destructor that destructs Ant
	 */
	~Ant();
	/**
	 * @brief Virtual method to render Ant
	 */
	void update();
	/**
	 * @brief Method that checks all objects around Ant
	 */
	void check_around();
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
	 * @brief Virtual method that checks team of Ant
	 * @return 				team of Ant
	 */
	teams check_team();
	/**
	 * @brief Method that takes damage from enemy object
	 */
	void take_damage();

	int health;
	bool going = false;
	bool attacking = false;
	position dest;
	unsigned int lastTimeDamage = 0;
	double dxpos, dypos;
	teams team;
private:
	Anthill* home = nullptr;
	list <shared_ptr<Object>>* objects;
	list <shared_ptr<Ant>>* brothers;	
};

#endif // !ANT_H
