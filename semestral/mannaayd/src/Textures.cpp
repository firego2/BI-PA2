#include "Textures.h"

SDL_Texture* Textures::loadTexture(string file)
{
	SDL_Surface* tempSurface = IMG_Load(file.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

Textures::Textures()
{
	grass = loadTexture("examples/materials/grass.png");
	anthill_empty = loadTexture("examples/materials/ant_house_empty.png");
	ant_red = loadTexture("examples/materials/ant_red.png");
	ant_blue = loadTexture("examples/materials/ant_blue.png");
	ant_yellow = loadTexture("examples/materials/ant_yellow.png");
	anthill_red = loadTexture("examples/materials/ant_house_red.png");
	anthill_blue = loadTexture("examples/materials/ant_house_blue.png");
	anthill_yellow = loadTexture("examples/materials/ant_house_yellow.png");
	wall = loadTexture("examples/materials/wall.png");
	water = loadTexture("examples/materials/water.png");
	table_red = loadTexture("examples/materials/table_red.png");
	table_blue = loadTexture("examples/materials/table_blue.png");
	table_yellow = loadTexture("examples/materials/table_yellow.png");
	one = loadTexture("examples/materials/1.png");
	two = loadTexture("examples/materials/2.png");
	three = loadTexture("examples/materials/3.png");
	four = loadTexture("examples/materials/4.png");
	five = loadTexture("examples/materials/5.png");
	six = loadTexture("examples/materials/6.png");
	seven = loadTexture("examples/materials/7.png");
	eight = loadTexture("examples/materials/8.png");
	nine = loadTexture("examples/materials/9.png");
	zero = loadTexture("examples/materials/0.png");
	main_menu = loadTexture("examples/materials/menu.png");
	levels = loadTexture("examples/materials/maps.png");
	sel = loadTexture("examples/materials/select.png");
}

Textures::~Textures()
{}

void Textures::draw_grass(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
