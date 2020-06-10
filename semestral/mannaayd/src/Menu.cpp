#include "Menu.h"

Menu::Menu(Textures* textures_, position pos_) : Object(textures_, pos_)
{
	state = main_menu;
}

void Menu::update()
{
	switch (state)
	{
		case(main_menu):
			objTexture = textures->main_menu;
			break;
		case(levels):
			objTexture = textures->levels;
			break;
		default:
			break;
	}
	srcRect.h = 1080;
	srcRect.w = 1920;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = pos.x;
	dstRect.y = pos.y;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;
}

int Menu::check_object_collision(teams team_, position pos_, position dest_, position from_)
{
	return 0;
}
