
#include "classes.h"

Base::Base(int x, int y, Tile *** tiles_)
{
	tiles = tiles_;
	tiles[x][y]->addBase(this);

	tile = tiles[x][y];
	sprite.setTexture(*(assets->base_texture));
}

void Base::draw()
{
	sprite.setPosition(sf::Vector2f(TILE_SIZE * tile->pos.x, TILE_SIZE * tile->pos.y));
	assets->window->draw(sprite);
}