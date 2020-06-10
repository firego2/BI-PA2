#include "Participant.h"

Participant::Participant(teams team, list <shared_ptr<Anthill>>* anthills)
{
	this->team = team;
	this->anthills = anthills;
	count_hills = 0;
}

bool Participant::is_defeated()
{
	int count = 0;
	for (auto i = anthills->begin(); i != anthills->end(); i++)
	{
		if ((*i)->team == this->team) count++;
	}
	count_hills = count;
	if (count_hills == 0) defeated = true;
	else defeated = false;
	return defeated;
}