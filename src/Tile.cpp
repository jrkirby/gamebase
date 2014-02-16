
#include "classes.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>


Tile::Tile(int x, int y, Tile *** tiles)
{
	pos.x = x;
	pos.y = y;
	worker = NULL;
	base = NULL;
	resource = NULL;
	dirs = (PathSegment **) malloc(sizeof(PathSegment *) * 8);
	for(int i = 0; i < 8; i++)
	{
		dirs[i] = NULL;
	}
	sprite.setTexture(*(assets->tile_texture));
	sprite.setPosition(sf::Vector2f(TILE_SIZE * x, TILE_SIZE * y));
}

Tile::~Tile()
{

}

void Tile::draw()
{
	assets->window->draw(sprite);
	if(base != NULL)
	{
		base->draw();
	}
	if(resource != NULL)
	{
		resource->draw();
	}
}
void Tile::draw_arrows()
{
	for(int i = 0; i < 8; i++)
	{
		if(dirs[i] != NULL)
		{
			dirs[i]->draw();
		}
	}
}

void Tile::draw_worker()
{
	if(worker != NULL)
	{
		worker->draw();
	}
}

void Tile::draw_base()
{
	if(base != NULL)
	{
		base->draw();
	}
}
void Tile::draw_resource()
{
	if(resource != NULL)
	{
		resource->draw();
	}
}

Tile * Tile::PathForward()
{
	int best_priority = -1;
	Tile * to = NULL;
	for(int i = 0; i < 8; i++)
	{
		if(dirs[i] != NULL)
		{
			if(dirs[i]->from == this)
			{
				if(dirs[i]->priority > best_priority)
				{
					best_priority = dirs[i]->priority;
					to = dirs[i]->to;
				}
			}
		}
	}
	return to;
}

Tile * Tile::PathBackward()
{
	int best_priority = -1;
	Tile * to = NULL;
	for(int i = 0; i < 8; i++)
	{
		if(dirs[i] != NULL)
		{
			if(dirs[i]->to == this)
			{
				if(dirs[i]->priority > best_priority)
				{
					best_priority = dirs[i]->priority;
					to = dirs[i]->from;
				}
			}
		}
	}
	return to;
}


bool Tile::empty()
{
	if(worker != NULL)
	{
		return false;
	}
	if(base != NULL)
	{
		return false;
	}
	if(resource != NULL && !resource->Depleted())
	{
		return false;
	}
	return true;
}

void Tile::clearPathFrom(int priority)
{
	for(int i = 0; i < 8; i++)
	{
		if(dirs[i] != NULL)
		{
			if(dirs[i]->priority == priority)
			{
				if(dirs[i]->from == this)
				{
					dirs[i]->to->dirs[7 - i] = NULL;
					delete dirs[i];
					dirs[i] = NULL;
				}
			}
		}
	}
}

void Tile::clearPathTo(int priority)
{
	for(int i = 0; i < 8; i++)
	{
		if(dirs[i] != NULL)
		{
			if(dirs[i]->priority == priority)
			{
				if(dirs[i]->to == this)
				{
					dirs[i]->from->dirs[7 - i] = NULL;
					delete dirs[i];
					dirs[i] = NULL;
				}
			}
		}
	}
}


void Tile::addResource(Resource * to_add)
{
	if(!this->empty())
		printf("Added resource to tile that wasn't empty. BAD BAD.\n");
	resource = to_add;
}

void Tile::addWorker(Worker * to_add)
{
	if(!this->empty())
		printf("Added worker to tile that wasn't empty. BAD BAD.\n");
	worker = to_add;
}

void Tile::addBase(Base * to_add)
{
	if(!this->empty())
		printf("Added base to tile that wasn't empty. BAD BAD.\n");
	base = to_add;
}

void Tile::removeWorker()
{
	worker = NULL;
}
