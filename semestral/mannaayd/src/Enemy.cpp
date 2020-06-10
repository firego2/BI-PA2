#include "Enemy.h"

#define LUCK 5			// 1-10
#define STUPIDITY 8		// 1-10

Enemy::Enemy(teams team, list <shared_ptr<Anthill>>* anthills) : Participant(team, anthills)
{
	enemy1 = nullptr;
	enemy2 = nullptr;
}

void Enemy::set_enemies(shared_ptr<Player> enemy1_, shared_ptr<Enemy> enemy2_)
{
	enemy1 = enemy1_;
	enemy2 = enemy2_;
}

void Enemy::ai()
{
	int hill = 0;
	unsigned int  currentTime = SDL_GetTicks();
	if (currentTime > lastAction + 1000 + 1000 * STUPIDITY && (!selectedhill || !enemyhill))
	{
		if (selectedhill)
		{
			if (selectedhill->team != team || selectedhill->ants_count < 2)
			{
				ants_to_send = 0;
				selectedhill = nullptr;
				enemyhill = nullptr;
			}
		}
		hill = rand() % count_hills;
		if(!selectedhill)
		for (auto i = anthills->begin(); i != anthills->end(); i++)
		{
			selectedhill = (*i);
			if (selectedhill->team != team) continue;
			else
			{
				if (hill == 0) break;
				hill--;
			}
		}
		hill = rand() % (anthills->size() - count_hills);
		if(!enemyhill)
		for (auto i = anthills->begin(); i != anthills->end(); i++)
		{	
			if ((*i)->team == team) continue;
			else
			{
				enemyhill = (*i);
				if (hill == 0) break;				
				hill--;
			}
		}
		ants_to_send = 5 + (rand() % LUCK) - (rand() % STUPIDITY);
		lastAction = currentTime;
	}
	if (selectedhill && enemyhill)
	{
		if (selectedhill->team == team)
		{
			if (ants_to_send == 0)
			{
				selectedhill = nullptr;
				enemyhill = nullptr;
			}
			else if (selectedhill->send_ants(enemyhill->pos)) ants_to_send--;
		}
	}
}
