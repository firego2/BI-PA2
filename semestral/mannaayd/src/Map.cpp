#include "Map.h"

Map::Map(char level[][30], Textures* textures_, shared_ptr<Player> player_, shared_ptr<Enemy> enemy_red_, shared_ptr<Enemy> enemy_yellow_, list <shared_ptr<Anthill>>& anthills_,  list <shared_ptr<Object>>& objects_, list <shared_ptr<Table>>& tables_, list <shared_ptr<Obstacle>>& obstacles_)
{
	player = player_;
	enemy_red = enemy_red_;
	enemy_yellow = enemy_yellow_;
	objects = &objects_;
	tables = &tables_;
	obstacles = &obstacles_;
	anthills = &anthills_;
	textures = textures_;
	

	loadMap(level);

	src.x = src.y = dest.x = dest.y = 0;
	src.w = src.h = dest.h = dest.w = 64;
}

Map::~Map()
{
}

void Map::loadMap(char level[][30])
{
	shared_ptr<Anthill> base = nullptr;
	shared_ptr<Table> table = nullptr;
	shared_ptr<Obstacle> obstacle = nullptr;
	shared_ptr<Ant> ant = nullptr;
	position pos;
	for (int row = 0; row < 17; row++)
	{	
		for (int col = 0; col < 30; col++)
		{
			pos.x = col * 64;
			pos.y = row * 64;
			if (level[row][col] == 'e')
			{		
				base =  make_shared<Anthill>(textures, pos, objects, tables, anthills, nullptr, none);
				objects->push_back(base);
				anthills->push_back(base);
			}
			if (level[row][col] == 'b')
			{
				pos.x += 4;
				pos.y -= 50;
				table = make_shared<Table>(textures, pos, blue, objects, 0);
				pos.x -= 4;
				pos.y += 50;
				base = make_shared<Anthill>(textures, pos, objects, tables, anthills, table, blue);
				objects->push_back(base);
				objects->push_back(table);
				tables->push_back(table);
				player->count_hills++;
				anthills->push_back(base);
			}
			if (level[row][col] == 'y')
			{
				pos.x += 4;
				pos.y -= 50;
				table = make_shared<Table>(textures, pos, yellow, objects, 0);
				pos.x -= 4;
				pos.y += 50;
				base = make_shared<Anthill>(textures, pos, objects, tables, anthills, table, yellow);
				objects->push_back(base);
				objects->push_back(table);
				tables->push_back(table);
				enemy_yellow->count_hills++;
				anthills->push_back(base);
			}
			if (level[row][col] == 'r')
			{
				pos.x += 4;
				pos.y -= 50;
				table = make_shared<Table>(textures, pos, red, objects, 0);
				pos.x -= 4;
				pos.y += 50;
				base = make_shared<Anthill>(textures, pos, objects, tables, anthills, table, red);
				objects->push_back(base);
				objects->push_back(table);
				tables->push_back(table);
				enemy_red->count_hills++;
				anthills->push_back(base);
			}
			if (level[row][col] == 'w')
			{
				obstacle = make_shared<Obstacle>(textures, pos, true);
				obstacles->push_back(obstacle);
				objects->push_back(obstacle);

			}
			if (level[row][col] == 'v')
			{
				obstacle = make_shared<Obstacle>(textures, pos, false);
				obstacles->push_back(obstacle);
				objects->push_back(obstacle);
			}
		}
	}
}

void Map::drawBackground()
{
	for (int row = 0; row < 17; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			dest.x = col * 64;
			dest.y = row * 64;
			Textures::draw_grass(textures->grass, src, dest);
		}
	}
}
