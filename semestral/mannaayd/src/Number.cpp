#include "Number.h"

Number::Number(Textures* textures_, position pos_) : Object(textures_, pos_)
{}

void Number::update()
{
	srcRect.h = 28;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = pos.x;
	dstRect.y = pos.y;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;
}

int Number::check_object_collision(teams team_, position pos_, position dest_, position from_)
{
	return NO_COLLISION;
}

void Number::change_num(int num)
{
	string textureFile;
	switch (num)
	{
	case (0):
		objTexture = textures->zero;
		break;
	case (1):
		objTexture = textures->one;
		break;
	case (2):
		objTexture = textures->two;
		break;
	case (3):
		objTexture = textures->three;
		break;
	case (4):
		objTexture = textures->four;
		break;
	case (5):
		objTexture = textures->five;
		break;
	case (6):
		objTexture = textures->six;
		break;
	case (7):
		objTexture = textures->seven;
		break;
	case (8):
		objTexture = textures->eight;
		break;
	case (9):
		objTexture = textures->nine;
		break;
	}
}
