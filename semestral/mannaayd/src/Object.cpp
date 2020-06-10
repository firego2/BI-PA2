#include "Object.h"
#include "Textures.h"
#include "Game.h"

Object::Object(Textures* textures_, position pos_)
{
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = pos_.x;
	dstRect.y = pos_.y;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;

	textures = textures_;
	objTexture = textures->ant_blue; // default texture
	angle = 0; 
	pos.x = pos_.x;
	pos.y = pos_.y;
}

Object::~Object()
{
}

int Object::check_object_collision(teams team_, position pos_, position dest_, position from_)
{	
	return NO_COLLISION;
}

teams Object::check_team()
{
	return none;
}

void Object::update()
{
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = pos.x;
	dstRect.y = pos.y;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;
}

void Object::render()
{
	SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
}
