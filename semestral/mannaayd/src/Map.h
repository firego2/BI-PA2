#ifndef MAP_H
#define MAP_H

#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "Anthill.h"
#include "Textures.h"
#include "Table.h"

/**
 * @brief The class that represents map - Map
 */
class Map
{

public:
	/**
	 * @brief Standard constructor initializing new Map
	 *
	 * @param[in] char level[][30]					2D array with map data
	 * @param[in] Textures*	textures_				pointer to class that keeps all textures
	 * @param[in] shared_ptr<Player> player				pointer to player
	 * @param[in] shared_ptr<Enemy> enemy_red			pointer to enemy red
	 * @param[in] shared_ptr<Enemy> enemy_yellow			pointer to enemy yellow
	 * @param[in] list <shared_ptr<Anthill>>& anthills		list container that keep all anthills
	 * @param[in] list <shared_ptr<Object>>& objects		list container that keep all objects
	 * @param[in] list <shared_ptr<Table>>& tables			list container that keep all tables
	 * @param[in] list <shared_ptr<Obstacle>>& obstacles		list container that keep all obstacles
	 */
	Map(char level[][30], Textures* textures_, shared_ptr<Player> player, shared_ptr<Enemy> enemy_red, shared_ptr<Enemy> enemy_yellow, list <shared_ptr<Anthill>>& anthills, list <shared_ptr<Object>>& objects, list <shared_ptr<Table>>& tables, list <shared_ptr<Obstacle>>& obstacles);
	/**
	 * @brief Standard destructor of Map
	 */
	~Map();
	/**
	 * @brief Method that loads map
	 *
	 * @param[in] char level[][30]					2D array with map data
	 */
	void loadMap(char level[][30]);
	/**
	 * @brief Method that draw bakground
	 */
	void drawBackground();



private:
	Textures* textures;
	SDL_Rect src, dest;

	shared_ptr<Enemy> enemy_red;
	shared_ptr<Enemy> enemy_yellow;
	shared_ptr<Player> player;
	list <shared_ptr<Anthill>> *anthills;
	list <shared_ptr<Object>> *objects;
	list <shared_ptr<Table>> *tables;
	list <shared_ptr<Obstacle>>* obstacles;
};

#endif // !MAP_H
