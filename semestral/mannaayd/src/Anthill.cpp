#include "Anthill.h"
#include "Ant.h"
#include "Table.h"


Anthill::Anthill(Textures* textures_, position pos_, list <shared_ptr<Object>>* objects_, list <shared_ptr<Table>>* tables_, list <shared_ptr<Anthill>>* anthills_, shared_ptr<Table> table_, teams team_) : Object(textures_, pos_)
{
	team = team_;
	table = table_;
	tables = tables_;
	anthills = anthills_;
	objects = objects_;
	have_collision = true;
	defence = 4;
	if(team != none) ants_count = 30;
	else
	{
		defence = 0;
		ants_count = 0;
	}
	switch(team)
	{
		case(blue):
			objTexture = textures->anthill_blue;
			break;
		case(red):
			objTexture = textures->anthill_red;
			break;
		case(yellow):
			objTexture = textures->anthill_yellow;
			break;
		case(none):
			objTexture = textures->anthill_empty;
			break;
	}
}

void Anthill::update()
{
	check_around(pos);
	if (ants_count <= 0 && defence <= 0 && team != none)
	{
		active = false;
		return;
	}
	unsigned int  currentTime = SDL_GetTicks();
	if (currentTime > lastTimeA + 4000 && team != none) 
	{ 
		if (ants_count < 30) ants_count++;
		lastTimeA = currentTime;
	}
	if(table) table->number = ants_count; // update ant count on table
	if(team != none)
	for (auto it1 = ants.begin(); it1 != ants.end(); it1++)
	{
		if (!(*it1)->active)
		{
			for (auto it2 = objects->begin(); it2 != objects->end(); it2++)
			{
				if ((*it2) == (*it1))
				{			
					for (auto a = ants.begin(); a != ants.end(); a++)
					{
						if ((*a)->dest.x == (*it1)->dest.x && (*a)->dest.y == (*it1)->dest.y) (*a)->going = true;
					}
					objects->erase(it2);
					it1 = ants.erase(it1);
					break;
				}
			}
			if (it1 == ants.end()) break;
		}
	}
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = pos.x;
	dstRect.y = pos.y;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;
}

void Anthill::render()
{
	for (auto i = ants.begin(); i != ants.end(); i++) if((*i)) (*i)->render();
	SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

int Anthill::check_object_collision(teams team_, position pos_, position dest_, position from_)
{
	if (pos_.x + 32 >= pos.x && pos_.x + 32 <= pos.x + 64 && pos_.y + 32 >= pos.y && pos_.y + 32 <= pos.y + 64 && dest_ == pos)
	{
		if (team == team_)
		{
			if (ants_count < 30) ants_count++;
			else ants_count = 30;
			return FRIENDLY_ANTHILL_OBJ_COLLISION;
		}
		else
		{
			return ENEMY_OBJ_COLLISION;
		}
	}
	return NO_COLLISION;
}

void Anthill::take_damage()
{
	unsigned int currentTime = SDL_GetTicks();
	if (currentTime > lastTimeD + 1000)
	{
		if (ants_count <= 0)
		{
			defence--;
			ants_count = 0;
		}
		else ants_count -= (rand() % 3);
		if (ants_count < 0) ants_count = 0;
		lastTimeD = currentTime;
	}
}

void Anthill::send_to(position pos_)
{
	if (ants_count > 0)
	{
		shared_ptr<Ant> ant = nullptr;
		switch (team)
		{
			case (blue):
			{
				ant = make_shared<Ant>(textures, pos, pos_, team, objects, &ants, this);
				break;
			}
			case (yellow):
			{
				ant = make_shared<Ant>(textures, pos, pos_, team, objects, &ants, this);
				break;
			}
			case (red):
			{
				ant = make_shared<Ant>(textures, pos, pos_, team, objects, &ants, this);
				break;
			}
		}
		ants.push_back(ant);
		objects->push_back(ant);
		ants_count--;
		table->number = ants_count;	
	}
}

bool Anthill::send_ants(position pos_)
{
	bool is_clear = check_if_clear(pos_);
	if (is_clear) send_to(pos_);
	return is_clear;
}

bool Anthill::check_if_clear(position dest_)
{
	bool clear = true;
	for (auto i = objects->begin(); i != objects->end(); i++)
	{
		if (i == objects->end()) break;
		if ((*i).get() == this) continue;
		switch ((*i)->check_object_collision(team, pos, dest_, pos))
		{		
		case(FRIENDLY_ANTHILL_OBJ_COLLISION):
		case(ENEMY_OBJ_COLLISION):
		case(FRIENDLY_ANT_GOING_OBJ_COLLISION):
		case(FRIENDLY_ANT_WAITING_OBJ_COLLISION):
			clear = false;
			break;
		case(OBSTACLE_OBJ_COLLISION):
		case(NO_COLLISION):
			break;
		}	
		if (!clear) break;
	}
	return clear;
}

teams Anthill::check_team()
{
	return team;
}

void Anthill::check_around(position dest_)
{
	for (auto i = objects->begin(); i != objects->end(); i++)
	{
		if (i == objects->end()) break;
		if ((*i).get() == this) continue;
		switch ((*i)->check_object_collision(team, pos, dest_, pos))
		{
		case(OBSTACLE_OBJ_COLLISION):
		case(FRIENDLY_ANTHILL_OBJ_COLLISION):
		case(FRIENDLY_ANT_GOING_OBJ_COLLISION):
		case(FRIENDLY_ANT_WAITING_OBJ_COLLISION):
		case(NO_COLLISION):
			break;
		case(ENEMY_OBJ_COLLISION):
			take_damage();
			if (defence < 0)
			{
				team = (*i)->check_team();
				position temp;
				temp.x = pos.x + 4;
				temp.y = pos.y - 50;
				switch (team)
				{
				case (blue):
					objTexture = textures->anthill_blue;
					if(!table) table = make_shared<Table>(textures, temp, team, objects, 0);
					else table->objTexture = textures->table_blue;
					break;
				case (yellow):
					objTexture = textures->anthill_yellow;
					if (!table) table = make_shared<Table>(textures, temp, team, objects, 0);
					else table->objTexture = textures->table_yellow;
					break;
				case (red):
					objTexture = textures->anthill_red;
					if (!table) table = make_shared<Table>(textures, temp, team, objects, 0);
					else table->objTexture = textures->table_red;
					break;
				}
				objects->push_back(table);
				tables->push_back(table);
				defence = 4;
				ants_count = 0;
			}
			break;
		}
	}
}
