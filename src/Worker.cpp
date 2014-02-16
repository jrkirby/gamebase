
#include "classes.h"
#include <SFML/Graphics.hpp>

Worker::Worker(int x, int y, Tile *** tiles_)
{
	tiles = tiles_;
	tiles[x][y]->addWorker(this);

	start_pos = tiles[x][y];
	from = start_pos;
	to = NULL;
	lerp = 0.0;
	speed = 0.02;
	empty = true;

	sprite.setTexture(*(assets->worker_texture));

}

void Worker::Move()
{
	if(empty)
	{
		if(to == NULL)
		{
			to = from->PathForward();
		}
		if(to != NULL)
		{
			lerp += speed;
		}
		if(lerp >= 1.0)
		{
			if(to->resource != NULL)
			{
				empty = false;
				to->resource->Mine();
				Tile * temp = to;
				to = from;
				from = temp;
				lerp = 0.0;
			}
			else
			{
				if(to->worker != this)
				{
					from->removeWorker();
					to->addWorker(this);
				}
				from = to;
				lerp = 0.0;
				to = NULL;
			}
		}
	}
	else
	{
		if(to == NULL)
		{
			to = from->PathBackward();
		}
		if(to != NULL)
		{
			lerp += speed;
		}
		if(lerp >= 1.0)
		{
			if(to->base != NULL)
			{
				empty = true;
				//increase amount mined
				Tile * temp = to;
				to = from;
				from = temp;
				lerp = 0.0;
			}
			else
			{
				if(to->worker != this)
				{
					from->removeWorker();
					to->addWorker(this);
				}
				from = to;
				lerp = 0.0;
				to = NULL;
			}
		}
	}
}

void Worker::draw()
{
	int x;
	int y;
	if(to != NULL)
	{
		x = (int)((TILE_SIZE * from->pos.x) * (1.0 - lerp) + (TILE_SIZE * to->pos.x) * (lerp));
		y = (int)((TILE_SIZE * from->pos.y) * (1.0 - lerp) + (TILE_SIZE * to->pos.y) * (lerp));
	}
	else
	{
		x = (int)(TILE_SIZE * from->pos.x);
		y = (int)(TILE_SIZE * from->pos.y);
	}
	// printf("drawing worker\n");
	sprite.setPosition(sf::Vector2f(x, y));
	assets->window->draw(sprite);
}

void Worker::Reset()
{
	from = start_pos;
	lerp = 0.0;
	to = NULL;
	speed = 0.06;
	empty = true;
	return;
}