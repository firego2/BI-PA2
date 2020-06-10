#ifndef TABLE_H

#define TABLE_H

#include "Object.h"
#include "Number.h"

/**
 * @brief The class that represents the child of the parent class Object - Table
 */
class Table : public Object
{
public:
	/**
	 * @brief Standard constructor initializing new Table
	 *
	 * @param[in] Textures*	textures_				pointer to class that keeps all textures
	 * @param[in] position pos_					coordinate of Table
	 * @param[in] teams team_					team of Table
	 * @param[in] list <shared_ptr<Object>>* objects		list container with all objects
	 * @param[in] int number_					number on table
	 */
	Table(Textures* textures_, position pos_, teams team_, list <shared_ptr<Object>>* objects, int number_);
	/**
	 * @brief Virtual method to update Table
	 */
	void update();
	/**
	 * @brief Virtual method to render Table 
	 */
	void render();
	/**
	 * @brief Virtual method that checks collisions with other objects
	 * @param[in] teams team_		team of Object
	 * @param[in] position pos_		coordinate of Object that calls this function
	 * @param[in] position dest_		destination coordinate of Object that calls this function
	 * @param[in] position from_		coordinate of birth place of Object that calls this function
	 * @return				number of collision type
	 */
	int check_object_collision(teams team_, position pos_, position dest_, position from_);
	int number;
private:
	shared_ptr<Number> num1;
	shared_ptr<Number> num2;
};


#endif // !TABLE_H
