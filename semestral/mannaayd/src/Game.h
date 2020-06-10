#ifndef GAME_H
#define GAME_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <memory>


using namespace std;

enum menu_states				{ main_menu, levels};
enum teams					{ red, yellow, blue, none };

/**
 * @brief Struct that represents position of an object.
 */
struct position
{
	int x = 0;
	int y = 0;
	friend bool operator== (const position& pos1, const position& pos2)
	{
		return pos1.x == pos2.x && pos1.y == pos2.y;
	}
	friend bool operator!= (const position& pos1, const position& pos2)
	{
		return !(pos1.x == pos2.x && pos1.y == pos2.y);
	}
};

class Object;
class Table;
class Number;
class Obstacle;
class Anthill;
class Textures;
class Map;
class Enemy;
class Player;
class Menu;

/**
 * @brief The central class that represents Game and stores data about each object in game.
 */
class Game
{

public:
	/**
	 * @brief Standard constructor initializing new Game
	 *
	 * @param[in] const string& name	name of window
	 * @param[in] int xpos			x coordinate of window
	 * @param[in] int ypos			y coordinate of window
	 * @param[in] int width			width of window
	 * @param[in] int height		height of window
	 * @param[in] bool fullscreen		fullscreen mode
	 */
	Game(const string& name, int xpos, int ypos, int width, int heght, bool fullscreen);
	/**
	 * @brief Standard destructor that destructs Game
	 */
	~Game();
	/**
	 * @brief Method that handling all events in Menu
	 */
	void init();
	/**
	 * @brief Method that handling all in game events
	 */
	void handleEventsmenu();
	/**
	 * @brief Method that updates Menu
	 */
	void updatemenu();
	/**
	 * @brief Method that render Menu
	 */
	void rendermenu();
	/**
	 * @brief Method that initializing all in game objects
	 */
	void handleEvents();
	/**
	 * @brief Method that updates all in game objects
	 */
	void update();
	/**
	 * @brief Method that render all in game objects
	 */
	void render();
	/**
	 * @brief Method that reads map from file
	 *
	 * @param[in] const char* inFileName	name of file
	 */
	bool readMap(const char* inFileName);
	/**
	 * @brief Method that reads save from file
	 *
	 * @param[in] const char* inFileName	name of file
	 */
	bool readSave(const char* inFileName);
	/**
	 * @brief Method that makes save to file
	 *
	 * @param[in] const char* inFileName	name of file
	 */
	void makeSave(const char* outFileName);
	/**
	 * @brief Method that cleans all SDL objects
	 */
	void clean();
	/**
	 * @brief Method that checks if game is running
	 */
	bool running();
	/**
	 * @brief Method that checks if user in menu
	 */
	bool inmenu();

	static SDL_Renderer* renderer;

private:
	int cursorpos = 0;
	unsigned int cursordelay = 0;
	char level[17][30];
	string levelpath;
	bool customexists = false;
	SDL_Event event;
	const Uint8* keyboard;
	bool isRunning;
	bool isMenu;
	SDL_Window *window;
	int cnt;
	shared_ptr<Textures> textures = nullptr;
	shared_ptr<Map> map = nullptr;
	shared_ptr<Enemy> enemy_red = nullptr;
	shared_ptr<Enemy> enemy_yellow = nullptr;
	shared_ptr<Player> player = nullptr;
	shared_ptr<Menu> menu = nullptr;
	shared_ptr<Object> cursor = nullptr;
	list <shared_ptr<Anthill>>::iterator select;
	list <shared_ptr<Object>> objects;
	list <shared_ptr<Obstacle>> obstacles;
	list <shared_ptr<Table>> tables;
	list <shared_ptr<Number>> numbers;
	list <shared_ptr<Anthill>> anthills;
};


#endif // !GAME_H
