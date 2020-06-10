#include "Table.h"
#include "Number.h"

Table::Table(Textures* textures_, position pos_, teams team_, list <shared_ptr<Object>>* objects, int number_) : Object(textures_, pos_)
{
	number = number_;
	position temppos;
	temppos.x = pos.x + 8;
	temppos.y = pos.y + 8;
	num1 = make_shared<Number>(textures, temppos);
	temppos.x = pos.x + 32;
	num2 = make_shared<Number>(textures, temppos);
	objects->push_back(num1);
	objects->push_back(num2);
	switch(team_)
	{
		case(blue):
			objTexture = textures->table_blue;
			break;
		case(yellow):
			objTexture = textures->table_yellow;
			break;
		case(red):
			objTexture = textures->table_red;
			break;
	}
}

void Table::update()
{
	num1->change_num(number / 10);
	num2->change_num(number % 10);
	num1->update();
	num2->update();
	
	srcRect.h = 44;
	srcRect.w = 56;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = pos.x;
	dstRect.y = pos.y;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;
}

void Table::render()
{
	SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
	num1->render();
	num2->render();
}

int Table::check_object_collision(teams team_, position pos_, position dest_, position from_)
{
	return NO_COLLISION;
}
