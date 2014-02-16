
#include "classes.h"
#include <SFML/Graphics.hpp>

PathSegment::PathSegment(Tile * from_, Tile * to_, int priority_)
{
	priority = priority_;
	from = from_;
	to = to_;

	if(from->pos.x == to->pos.x || from->pos.y == to->pos.y)
	{
		sprite.setTexture(*(assets->arrow_texture));
		sprite.setOrigin(0, TILE_SIZE / 2);
		if(from->pos.x > to->pos.x)
		{
			sprite.rotate(180);
		}
		else if(from->pos.x < to->pos.x)
		{

		}
		else
		{
			if(from->pos.y > to->pos.y)
			{
				sprite.rotate(270);
			}
			else
			{
				sprite.rotate(90);
			}
		}
	}
	else
	{
		sprite.setTexture(*(assets->diagonal_arrow_texture));
		sprite.setOrigin(0, 0);
		if(from->pos.x > to->pos.x)
		{
			if(from->pos.y > to->pos.y)
			{
				sprite.rotate(180);
			}
			else
			{
				sprite.rotate(90);
			}
		}
		else
		{
			if(from->pos.y > to->pos.y)
			{
				sprite.rotate(270);
			}
			else
			{
				
			}
		}
	}
	sprite.setPosition(from->pos.x * TILE_SIZE + (TILE_SIZE / 2), from->pos.y * TILE_SIZE + (TILE_SIZE / 2));
	if(priority == 1)
	{
		sprite.setColor(sf::Color(220, 0, 0));
	}
	else if(priority == 2)
	{
		sprite.setColor(sf::Color(220, 220, 0));		
	}
	else if(priority == 3)
	{
		sprite.setColor(sf::Color(0, 220, 0));		
	}
}

PathSegment::~PathSegment()
{
}

void PathSegment::draw()
{
	assets->window->draw(sprite);
}
