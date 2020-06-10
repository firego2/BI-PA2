#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Textures.h" 
#include "Object.h"

/**
 * @brief The class that represents the child of the parent class Object - Obstacle
 */
class Obstacle : public Object
{
public:
	/**
	 * @brief Standard constructor initializing new Table
	 *
	 * @param[in] Textures*	textures_				pointer to class that keeps all textures
	 * @param[in] position pos_					coordinate of Obstacle
	 * @param[in] bool is_wall					is wall or water
	 */
	Obstacle(Textures* textures_, position pos_, bool is_wall);
	/**
	 * @brief Virtual method that checks collisions with other objects
	 * @param[in] teams team_		team of Object
	 * @param[in] position pos_		coordinate of Object that calls this function
	 * @param[in] position dest_		destination coordinate of Object that calls this function
	 * @param[in] position from_		coordinate of birth place of Object that calls this function
	 * @return				number of collision type
	 */
	int check_object_collision(teams team_, position pos_, position dest_, position from_);
	int wall;
private:
};

#endif // !OBSTACLE_H
