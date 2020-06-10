#ifndef OBJECT_H
#define OBJECT_H

#include "Game.h"

#define NO_COLLISION 0
#define ENEMY_OBJ_COLLISION 1
#define FRIENDLY_ANTHILL_OBJ_COLLISION 2
#define FRIENDLY_ANT_WAITING_OBJ_COLLISION 3
#define FRIENDLY_ANT_GOING_OBJ_COLLISION 4
#define OBSTACLE_OBJ_COLLISION 5

class Game;
class Textures;

/**
 * @brief The class that represents the parent class of all objects in game - Object
 */
class Object
{
public:
	/**
	 * @brief Standard constructor initializing new Object
	 *
	 * @param[in] Textures*	textures_	pointer to class that keeps all textures
	 * @param[in] position pos_		coordinate of Object
	 */
	Object(Textures* textures_, position pos_);
	/**
	 * @brief Standart destructor that destructs Object
	 */
	~Object();
	/**
	 * @brief Virtual method to update Object 
	 */	
	virtual void update();
	/**
	 * @brief Virtual method to render Object 
	 */
	virtual void render();
	/**
	 * @brief Virtual method that checks collisions with other objects 
	 * @param[in] teams team_		team of Object
	 * @param[in] position pos_		coordinate of Object that calls this function
	 * @param[in] position dest_		destination coordinate of Object that calls this function
	 * @param[in] position from_		coordinate of birth place of Object that calls this function
	 * @return				number of collision type
	 */
	virtual int check_object_collision(teams team_, position pos_, position dest_, position from_);
	/**
	 * @brief Virtual method that checks team of Object
	 * @return 				team of Object
	 */
	virtual teams check_team();

	bool have_collision = false;	
	position pos;
	double angle;
	bool active = true;
	SDL_Texture* objTexture;
protected:
	Textures* textures;
	SDL_Rect srcRect, dstRect;
};

#endif
