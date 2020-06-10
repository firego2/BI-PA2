#include "Game.h"
#include "Textures.h"
#include "Object.h"
#include "Table.h"
#include "Number.h"
#include "Map.h"
#include "Participant.h"
#include "Enemy.h"
#include "Player.h"
#include "Ant.h"
#include "Anthill.h"
#include "Menu.h"
#include <fstream>
#include <string>

using namespace std; 

SDL_Renderer* Game::renderer = nullptr;

Game::Game(const string& name, int xpos, int ypos, int width, int height, bool fullscreen)
{
	cnt = 0;
	int flags = 0;
	keyboard = SDL_GetKeyboardState(NULL);
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL initialised." << endl;

		window = SDL_CreateWindow(name.c_str(), xpos, ypos, width, height, flags);
		if (window) cout << "Window created!" << endl;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			cout << "Renderer created!" << endl;
		}
		isRunning = true;
		isMenu = true;
	}
	else
	{
		isMenu = false;
		isRunning = false;
	}
	position temppos;
	textures = make_shared<Textures>();
	menu = make_shared<Menu>(textures.get(), temppos);
	cursor = make_shared<Object>(textures.get(), temppos);
	objects.push_back(cursor);
}

Game::~Game()
{}

void Game::init()
{	
	player = make_shared<Player>(teams::blue, &anthills);
	enemy_red = make_shared<Enemy>(teams::red, &anthills);
	enemy_yellow = make_shared<Enemy>(teams::yellow, &anthills);
	map = make_shared<Map>(level, textures.get(), player, enemy_red, enemy_yellow, anthills, objects, tables, obstacles);

	player->set_enemies(enemy_red, enemy_yellow);
	enemy_red->set_enemies(player, enemy_yellow);
	enemy_yellow->set_enemies(player, enemy_red);
	cursor->objTexture = textures->sel;
	select = anthills.begin();
}
void Game::handleEventsmenu()
{
	SDL_PollEvent(&event);
	keyboard = SDL_GetKeyboardState(NULL);
	switch (event.type)
	{
		case SDL_QUIT:
			isMenu = false;
			break;
		default:
			break;
	}
	if (keyboard[SDL_SCANCODE_ESCAPE]) // exit game
	{
		isMenu = false;
		isRunning = false;
	}
	if (keyboard[SDL_SCANCODE_A] && menu->state == levels) // back
	{
		menu->state = main_menu;
		cursorpos = 0;
	}
	if (keyboard[SDL_SCANCODE_D] && menu->state == main_menu) // back
	{
		menu->state = levels;
		cursorpos = 0;
	}
	if (keyboard[SDL_SCANCODE_S]) // down
	{
		cursorpos = menu->state == main_menu ? (cursorpos + 4) % 3 : (cursorpos + 5) % 4;
		SDL_Delay(150);
	}
	if (keyboard[SDL_SCANCODE_W]) // up
	{
		cursorpos = menu->state == main_menu ? (cursorpos + 2) % 3 : (cursorpos + 3) % 4;
		SDL_Delay(150);
	}
	if (keyboard[SDL_SCANCODE_RETURN]) // Enter
	{
		switch (menu->state)
		{
		case(main_menu):
			if (cursorpos == 0) // new game
			{
				menu->state = levels;
			}
			if (cursorpos == 1) // load save
			{
				string savename = "examples/saves/";
				string temp;
				cout << "Type save name: ";
				cin >> temp;
				savename += temp;
				if (readSave(savename.c_str()))
				{
					isMenu = false;
					levelpath = "examples/maps/blank.txt";
					readMap(levelpath.c_str());
					cout << "Save successfully loaded." << endl;
				}
				else cout << "Bad save name." << endl;
			}
			if (cursorpos == 2) // exit
			{
				isMenu = false;
				isRunning = false;
			}
			break;
		case(levels):
			if (cursorpos == 0) // level1
			{
				levelpath = "examples/maps/level1.txt";
				readMap(levelpath.c_str());
				isMenu = false;
			}
			if (cursorpos == 1) // level2
			{
				levelpath = "examples/maps/level2.txt";
				readMap(levelpath.c_str());
				isMenu = false;
			}
			if (cursorpos == 2) // level3
			{
				levelpath = "examples/maps/level3.txt";
				readMap(levelpath.c_str());
				isMenu = false;
			}
			if (cursorpos == 3) // custom
			{
				cout << "Custom map file: ";
				cin >> levelpath;
				customexists = readMap(levelpath.c_str());
				if (customexists)
				{
					isMenu = false;
					cout << "Map successfully loaded." << endl;
				}
				else levelpath = "";
			}
			break;
		}
		SDL_Delay(150);
	}
}

void Game::updatemenu()
{
	menu->update();
	if (menu->state == main_menu)
	{
		if (cursorpos == 0)
		{
			cursor->pos.x = 587;
			cursor->pos.y = 478;
		}
		else if (cursorpos == 1)
		{
			cursor->pos.x = 587;
			cursor->pos.y = 676;
		}
		else if (cursorpos == 2)
		{
			cursor->pos.x = 748;
			cursor->pos.y = 856;
		}
	}
	else
	{
		if (cursorpos == 0)
		{
			cursor->pos.x = 681;
			cursor->pos.y = 413;
		}
		else if (cursorpos == 1)
		{
			cursor->pos.x = 681;
			cursor->pos.y = 574;
		}
		else if (cursorpos == 2)
		{
			cursor->pos.x = 681;
			cursor->pos.y = 740;
		}
		else if (cursorpos == 3)
		{
			cursor->pos.x = 681;
			cursor->pos.y = 894;
		}
	}
	cursor->update();
}

void Game::rendermenu()
{
	SDL_RenderClear(renderer);
	menu->render();
	cursor->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	keyboard = SDL_GetKeyboardState(NULL);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
	if (keyboard[SDL_SCANCODE_S]) // sends attack
	{
		if (player->is_selected()) player->attacking = true;
	}
	if (keyboard[SDL_SCANCODE_C]) // cancel all attacks
	{
		player->attacking = false;
		player->clear_select();
	}
	if (keyboard[SDL_SCANCODE_A]) // prev anthill
	{
		unsigned int currentTime = SDL_GetTicks();
		if (currentTime > cursordelay + 150)
		{
			if (select == anthills.begin()) select = anthills.end();
			select--;
			cursordelay = currentTime;
		}
	}
	if (keyboard[SDL_SCANCODE_D]) // next anthill
	{
		unsigned int currentTime = SDL_GetTicks();
		if (currentTime > cursordelay + 150)
		{
			select++;
			if (select == anthills.end()) select = anthills.begin();
			cursordelay = currentTime;
		}
	}
	if (keyboard[SDL_SCANCODE_F1]) // save game and exit
	{
		string savename = "examples/saves/";
		string temp;
		cout << "Save name: ";
		cin >> temp;
		savename += temp;
		makeSave(savename.c_str());
		cout << "Saved successfully." << endl;
		isRunning = false;
	}
	if (keyboard[SDL_SCANCODE_ESCAPE] || player->is_defeated() || player->is_win()) // exit game
	{
		if (player->is_win()) cout << "You win." << endl;
		if (player->is_defeated()) cout << "You lose." << endl;
		isRunning = false;
	}
	if (keyboard[SDL_SCANCODE_RETURN]) // Enter
	{
		unsigned int currentTime = SDL_GetTicks();
		if (currentTime > cursordelay + 150)
		{
			player->check_select((*select));
			cursordelay = currentTime;
		}
	}
	if (player->attacking)				player->send_attack();

	if (!enemy_red->is_defeated())			enemy_red->ai();
	if (!enemy_yellow->is_defeated())		enemy_yellow->ai();
}

void Game::update()
{
	for (auto i = objects.begin(); i != objects.end(); i++) if((*i))(*i)->update();
	if(*select) cursor->pos.x = (*select)->pos.x;
	if(*select) cursor->pos.y = (*select)->pos.y;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawBackground();
	for (auto i = obstacles.begin(); i != obstacles.end(); i++)		(*i)->render();
	for (auto i = anthills.begin(); i != anthills.end(); i++)		(*i)->render();
	for (auto i = tables.begin(); i != tables.end(); i++)			(*i)->render();
	
	cursor->render();
	SDL_RenderPresent(renderer);
}

bool Game::readMap(const char* inFileName)
{
	ifstream file;
	file.open(inFileName);
	if (!file.is_open() || !file)
	{
		cout << "Invalid map path." << endl;
		return false;
	}
	char ch;
	int row = 0;
	int col = 0;
	while (true)
	{
		if (!(file.read(&ch, sizeof(char)))) break;
		if (ch == '\r') continue;
		if (ch == '\n')
		{
			if (col > 30)
			{
				cout << row << endl;
				cout << col << " " << ch << endl;
				cout << "Bad cols count." << endl;
				return false;
			}
			row++;
			if (row >= 17)
			{
				cout << "Bad rows count." << endl;
				return false;
			}
			col = 0;
		}
		else
		{
			if (ch != 'g' && ch != 'r' && ch != 'v' && ch != 'w' && ch != 'b' && ch != 'y' && ch != 'e')
			{
				cout << "Invalid character in map.";
				return false;
			}
			level[row][col] = ch;
			col++;
		}
		
	}
	file.close();
	return true;
}

bool Game::readSave(const char* inFileName)
{
	ifstream file;
	file.open(inFileName);
	if (!file || !file.is_open())
	{
		cout << "Invalid save path." << endl;
		return false;
	}
	string temp;
	shared_ptr<Anthill> anthill = nullptr;
	shared_ptr<Ant> ant = nullptr;
	shared_ptr<Obstacle> obstacle = nullptr;
	shared_ptr<Table> table = nullptr;
	position temppos;
	int co = 0;
	while (!file.eof()) 
	{
		getline(file, temp);
		int is_wall = 0;
		
		if (temp == "obstacle:")
		{
			getline(file, temp);
			if(temp[0] == '\r') getline(file, temp);
			obstacle = make_shared <Obstacle>(textures.get(), temppos, true);
			if (sscanf(temp.c_str(), "%d %d %lf %d", &obstacle->pos.x, &obstacle->pos.y, &obstacle->angle, &is_wall) != 4)
			{
				cout << "Bad obstacle param." << endl;
				file.close();
				return false;
			}
			obstacle->have_collision = true;
			if (is_wall == 0) obstacle->objTexture = textures->water;
			objects.push_back(obstacle);
			obstacles.push_back(obstacle);
		}
		else if (temp == "anthill:")
		{
			getline(file, temp);
			if(temp[0] == '\r') getline(file, temp);
			temppos.x = 0;
			temppos.y = 0;
			anthill = make_shared<Anthill>(textures.get(), temppos, &objects, &tables, &anthills, nullptr, none);
			if (sscanf(temp.c_str(), "%d %d %lf %d %d %d", &anthill->pos.x, &anthill->pos.y, &anthill->angle, &anthill->team, &anthill->ants_count, &anthill->defence) != 6)
			{
				cout << "Bad anthill param." << endl;
				file.close();
				return false;
			}
			cout << anthill->pos.x << " " << anthill->pos.y << endl;
			if (anthill->team != none)
			{
				temppos.x = anthill->pos.x + 4;
				temppos.y = anthill->pos.y - 50;
				table = make_shared<Table>(textures.get(), temppos, anthill->team, &objects, anthill->ants_count);
				anthill->table = table;
				objects.push_back(table);
				tables.push_back(table);
				table = nullptr;
				if (anthill->team == red) anthill->objTexture = textures->anthill_red;
				else if (anthill->team == yellow) anthill->objTexture = textures->anthill_yellow;
				else if (anthill->team == blue) anthill->objTexture = textures->anthill_blue;
			}
			objects.push_back(anthill);
			anthills.push_back(anthill);
			getline(file, temp);
			if (temp == "ants:")
			{
				while (true)
				{
					getline(file, temp);
					if(temp[0] == '\r') getline(file, temp);
					if (temp == "ant:") continue;
					if (temp == "ants end.") break;
					ant = make_shared<Ant>(textures.get(), temppos, temppos, anthill->team, &objects, &anthill->ants, anthill.get());
					int attack, go;
					if (sscanf(temp.c_str(), "%d %d %lf %d %d %d %d %d %u", &ant->pos.x, &ant->pos.y, &ant->angle, &ant->health, &attack, &go, &ant->dest.x, &ant->dest.y, &ant->lastTimeDamage) != 9) break;
					ant->dxpos = ant->pos.x;
					ant->dypos = ant->pos.y;
					if (attack == 1) ant->attacking = true;
					else ant->attacking = false;
					if (go == 1) ant->going = true;
					else ant->going = false;
					if (ant->team != blue)
					{
						if (ant->team == red) ant->objTexture = textures->ant_red;
						else if(ant->team == yellow) ant->objTexture = textures->ant_yellow;
					}
					anthill->ants.push_back(ant);
					objects.push_back(ant);
				}
			}
		}
	}
	file.close();
	return true;
}

void Game::makeSave(const char* outFileName)
{
	ofstream file;
	file.open(outFileName);
	if (!file || !file.is_open())
	{
		cout << "Invalid save path." << endl;
		return;
	}
	for (auto i = obstacles.begin(); i != obstacles.end(); i++) // make anthills save
	{
		if (!(*i)->active) continue;
		file << "obstacle:" << endl;
		file << (int)(*i)->pos.x << " ";
		file << (int)(*i)->pos.y << " ";
		file << (double)(*i)->angle << " ";
		file << (*i)->wall << endl;
	}
	for (auto i = anthills.begin(); i != anthills.end(); i++) // make anthills save
	{
		file << "anthill:" << endl;
		file << (int)(*i)->pos.x << " ";
		file << (int)(*i)->pos.y << " ";
		file << (double)(*i)->angle << " ";
		file << (*i)->team << " ";
		file << (*i)->ants_count << " ";
		file << (*i)->defence << endl;
		file << "ants:" << endl;
		if((*i)->team != none)
		for (auto a = (*i)->ants.begin(); a != (*i)->ants.end(); a++) // make ants save
		{
			if (!(*i)->active) continue;
			file << "ant:" << endl;
			file << (int)(*a)->pos.x << " ";
			file << (int)(*a)->pos.y << " ";
			file << (double)(*a)->angle << " ";
			file << (*a)->health << " ";
			file << (int)(*a)->attacking << " ";
			file << (int)(*a)->going << " ";
			file << (int)(*a)->dest.x << " ";
			file << (int)(*a)->dest.y << " ";
			file << (*a)->lastTimeDamage << " " << endl;
		}
		file << "ants end." << endl;
	}
	
	file.close();
	return;
}

void Game::clean()
{
	SDL_DestroyTexture(textures->grass);
	SDL_DestroyTexture(textures->anthill_empty);
	SDL_DestroyTexture(textures->ant_red);
	SDL_DestroyTexture(textures->ant_blue);
	SDL_DestroyTexture(textures->ant_yellow);
	SDL_DestroyTexture(textures->anthill_red);
	SDL_DestroyTexture(textures->anthill_blue);
	SDL_DestroyTexture(textures->anthill_yellow);
	SDL_DestroyTexture(textures->wall);
	SDL_DestroyTexture(textures->water);
	SDL_DestroyTexture(textures->table_red);
	SDL_DestroyTexture(textures->table_blue);
	SDL_DestroyTexture(textures->table_yellow);
	SDL_DestroyTexture(textures->one);
	SDL_DestroyTexture(textures->two);
	SDL_DestroyTexture(textures->three);
	SDL_DestroyTexture(textures->four);
	SDL_DestroyTexture(textures->five);
	SDL_DestroyTexture(textures->six);
	SDL_DestroyTexture(textures->seven);
	SDL_DestroyTexture(textures->eight);
	SDL_DestroyTexture(textures->nine);
	SDL_DestroyTexture(textures->zero);
	SDL_DestroyTexture(textures->main_menu);
	SDL_DestroyTexture(textures->levels);
	SDL_DestroyTexture(textures->sel);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	cout << "GAME stopped." << endl;
}

bool Game::running()
{
	return isRunning;
}

bool Game::inmenu()
{
	return isMenu;
}
