#include "Ant.h"
#include "Anthill.h"
#include "Object.h"
#include <cmath>
#include <memory>

Ant::Ant(Textures* textures_, position pos_, position dest_, teams team_, list <shared_ptr<Object>>* objects_, list <shared_ptr<Ant>>* brothers_, Anthill *home_) : Object(textures_, pos_)
{
	health = 4;
	dest.x = dest_.x;
	dest.y = dest_.y;
	home = home_;
	objects = objects_;
	brothers = brothers_;
	dxpos = pos.x;
	dypos = pos.y;
	going = true;
	have_collision = true;
	team = team_;
	switch(team)
	{
		case(blue):
			objTexture = textures->ant_blue;
			break;
		case(red):
			objTexture = textures->ant_red;
			break;
		case(yellow):
			objTexture = textures->ant_yellow;
			break;
	}
}

Ant::~Ant()
{}

int Ant::check_object_collision(teams team_, position pos_, position dest_, position from_)
{
	if (pos.x + 32 >= pos_.x && pos.x + 32 <= pos_.x + 64 && pos.y + 32 >= pos_.y && pos.y + 32 <= pos_.y + 64 && ((dest_ == home->pos && dest == from_ && dest_ != from_) || (dest_ == dest && dest_ != from_) || (from_ == pos_)))
	{
		if (team != team_)
		{
			return ENEMY_OBJ_COLLISION;
		}
		else if(going) return FRIENDLY_ANT_GOING_OBJ_COLLISION;
		else if (!going) return FRIENDLY_ANT_WAITING_OBJ_COLLISION;
	}
	return NO_COLLISION;
}

void Ant::check_around()
{
	going = true;
	attacking = false;
	bool attack = false;
	for (auto i = objects->begin(); i != objects->end(); i++)
	{
		if ((*i).get() == this || ((*i).get() == home && dest != home->pos)) continue;
		switch ((*i)->check_object_collision(team, pos, dest, home->pos))
		{
		case(NO_COLLISION):
		case(FRIENDLY_ANT_GOING_OBJ_COLLISION):
			break;
		case(ENEMY_OBJ_COLLISION):
			take_damage();
			going = false;
			attacking = true;
			break;
		case(FRIENDLY_ANTHILL_OBJ_COLLISION):
			active = false;
			break;
		case(FRIENDLY_ANT_WAITING_OBJ_COLLISION):
			for (auto a = brothers->begin(); a != brothers->end(); a++)
			{
				if ((*a)->attacking && (*a)->dest == dest)
				{
					attack = true;
					break;
				}
			}
			for (auto a = brothers->begin(); a != brothers->end(); a++)
			{
				if (!attack && (*a)->dest == dest && pos.x + 32 >= (*a)->pos.x && pos.x + 32 <= (*a)->pos.x + 64 && pos.y + 32 >= (*a)->pos.y && pos.y + 32 <= (*a)->pos.y + 64) (*a)->going = true;
				else if (attack && (*a)->dest == dest && pos.x + 32 >= (*a)->pos.x && pos.x + 32 <= (*a)->pos.x + 64 && pos.y + 32 >= (*a)->pos.y && pos.y + 32 <= (*a)->pos.y + 64) (*a)->going = false;
			}
			break;
		case(OBSTACLE_OBJ_COLLISION):
			dest.x = home->pos.x;
			dest.y = home->pos.y;
			break;
		}
	}
}

teams Ant::check_team()
{
	return team;
}

void Ant::update()
{
	check_around();
	if (pos != dest && going)
	{
		double gip = sqrt(pow(dest.x - pos.x, 2) + pow(dest.y - pos.y, 2));
		if (dest.x < pos.x && dest.y >= pos.y)
		{
			angle = asin(abs((double)dest.x - (double)pos.x) / gip) * (180.0 / 3.141592653589793238463);
			dypos += (abs((double)dest.y - (double)pos.y) / gip);
			dxpos -= (abs((double)dest.x - (double)pos.x) / gip);
		}
		if (dest.x <= pos.x && dest.y < pos.y)
		{
			angle = asin(abs((double)pos.y - (double)dest.y) / gip) * (180.0 / 3.141592653589793238463) + 90;
			dypos -= (abs((double)dest.y - (double)pos.y) / gip);
			dxpos -= (abs((double)dest.x - (double)pos.x) / gip);
		}
		if (dest.x > pos.x&& dest.y <= pos.y)
		{
			angle = asin(abs((double)dest.x - (double)pos.x) / gip) * (180.0 / 3.141592653589793238463) + 180;
			dypos -= (abs((double)dest.y - (double)pos.y) / gip);
			dxpos += (abs((double)dest.x - (double)pos.x) / gip);
		}
		if (dest.x >= pos.x && dest.y > pos.y)
		{
			angle = asin(abs((double)pos.y - (double)dest.y) / gip) * (180.0 / 3.141592653589793238463) + 270;
			dypos += (abs((double)dest.y - (double)pos.y) / gip);
			dxpos += (abs((double)dest.x - (double)pos.x) / gip);
		}	
		pos.x = (int)dxpos;
		pos.y = (int)dypos;
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

void Ant::take_damage()
{
	unsigned int  currentTime = SDL_GetTicks();
	if (currentTime > lastTimeDamage + 2000)
	{
		health--;
		if (health <= 0) active = false;
		lastTimeDamage = currentTime;
	}
}
