#include "Obstacle.h"

Obstacle::Obstacle(Textures* textures_, position pos_, bool is_wall) : Object(textures_, pos_)
{
	have_collision = true;
	if(is_wall) objTexture = textures->wall;
	else objTexture = textures->water;
	wall = is_wall;
}

int Obstacle::check_object_collision(teams team_, position pos_, position dest_, position from_)
{
	if (pos.x + 52 >= pos_.x && pos.x + 12 <= pos_.x + 64 && pos.y + 52 >= pos_.y && pos.y + 12 <= pos_.y + 64)
	{
		return OBSTACLE_OBJ_COLLISION;
	}
	return NO_COLLISION;
}
