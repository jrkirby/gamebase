
#include "classes.h"

Resource::Resource(int x, int y, Tile *** tiles_)
{
	tiles = tiles_;
	tiles[x][y]->addResource(this);
	tile = tiles[x][y];
	drag = 0.2;
	loads = 10;
	sprite_normal.setTexture(*(assets->resource_texture));
	sprite_depleted.setTexture(*(assets->resource_depleted_texture));
}

void Resource::Mine()
{
	loads--;
	if(loads == 0)
	{
		tile->resource = NULL;
	}
}

bool Resource::Depleted()
{
	if(loads <= 0)
		return true;
	return false;
}

void Resource::draw()
{
	if(loads != 0)
	{
		sprite_normal.setPosition(sf::Vector2f(TILE_SIZE * tile->pos.x, TILE_SIZE * tile->pos.y));
		assets->window->draw(sprite_normal);
	}
	else
	{
		sprite_depleted.setPosition(sf::Vector2f(TILE_SIZE * tile->pos.x, TILE_SIZE * tile->pos.y));
		assets->window->draw(sprite_depleted);
	}
}

void Resource::Reset()
{
	loads = 10;
	tile->resource = this;
}
