#ifndef TEXTURES_H
#define TEXTURES_H

#include "Game.h"
/**
 * @brief The class that represents Textures of all objects in game - Textures
 */
class Textures
{
public:
	/**
	 * @brief Standard constructor initializing Textures
	 */
	Textures();
	/**
	 * @brief Standard constructor initializing Textures
	 */
	~Textures();
	/**
	 * @brief Method that load textures from .png files
	 * @param[in] string file		file of texture to load
	 * @return				pointer to SDL_Texture
	 */
	SDL_Texture* loadTexture(string file);
	/**
	 * @brief Method that draw grass for background
	 * @param[in] SDL_Texture* texture	pointer to texture
	 * @param[in] SDL_Rect src		source SDL_Rect
	 * @param[in] SDL_Rect dest		destination SDL_Rect
	 */
	static void draw_grass(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);

	SDL_Texture* grass = nullptr;
	SDL_Texture* anthill_empty = nullptr;
	SDL_Texture* ant_red = nullptr;
	SDL_Texture* ant_blue = nullptr;
	SDL_Texture* ant_yellow = nullptr;
	SDL_Texture* anthill_red = nullptr;
	SDL_Texture* anthill_blue = nullptr;
	SDL_Texture* anthill_yellow = nullptr;
	SDL_Texture* wall = nullptr;
	SDL_Texture* water = nullptr;
	SDL_Texture* table_red = nullptr;
	SDL_Texture* table_blue = nullptr;
	SDL_Texture* table_yellow = nullptr;
	SDL_Texture* one = nullptr;
	SDL_Texture* two = nullptr;
	SDL_Texture* three = nullptr;
	SDL_Texture* four = nullptr;
	SDL_Texture* five = nullptr;
	SDL_Texture* six = nullptr;
	SDL_Texture* seven = nullptr;
	SDL_Texture* eight = nullptr;
	SDL_Texture* nine = nullptr;
	SDL_Texture* zero = nullptr;
	SDL_Texture* main_menu = nullptr;
	SDL_Texture* levels = nullptr;
	SDL_Texture* sel = nullptr;
private:
};

#endif // !TEXTURES_H
