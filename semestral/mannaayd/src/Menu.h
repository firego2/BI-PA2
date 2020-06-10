#ifndef MENU_H

#define MENU_H
#include "Object.h"
#include "Textures.h"

/**
 * @brief The class that represents the child of the parent class Object - Menu
 */
class Menu : public Object
{
public:
	/**
	 * @brief Standard constructor initializing new Menu
	 *
	 * @param[in] Textures*	textures_				pointer to class that keeps all textures
	 * @param[in] position pos_					coordinate of Menu
	 */
	Menu(Textures* textures_, position pos_);
	/**
	 * @brief Virtual method to update Menu
	 */
	void update();
	/**
	 * @brief Virtual method that checks collisions with other objects
	 * @param[in] teams team_		team of Object
	 * @param[in] position pos_		coordinate of Object that calls this function
	 * @param[in] position dest_		destination coordinate of Object that calls this function
	 * @param[in] position from_		coordinate of birth place of Object that calls this function
	 * @return				number of collision type
	 */
	int check_object_collision(teams team_, position pos_, position dest_, position from_);
	menu_states state;
private:
	
};


#endif // !MENU_H
