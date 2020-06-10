#include "Player.h"

Player::Player(teams team, list <shared_ptr<Anthill>>* anthills) : Participant(team, anthills)
{
	enemy1 = nullptr;
	enemy2 = nullptr;
}

void Player::set_enemies(shared_ptr<Enemy> enemy1_, shared_ptr<Enemy> enemy2_)
{
	enemy1 = enemy1_;
	enemy2 = enemy2_;
}

void Player::check_select(shared_ptr<Anthill> select)
{
	if (!selectedhill)
	{
		if (select->team == blue)
		{
			selectedhill = select;
			return;
		}	
	}
	if (!enemyhill)
	{
		enemyhill = select;
	}
}

void Player::clear_select()
{
	enemyhill = nullptr;
	selectedhill = nullptr;
}

bool Player::is_selected()
{
	return selectedhill && enemyhill;
}

void Player::send_attack()
{
	selectedhill->send_ants(enemyhill->pos);
}

bool Player::is_win()
{
	return count_hills == (int)anthills->size();
}
