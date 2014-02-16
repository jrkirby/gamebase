
#include "classes.h"

#include <SFML/System.hpp>
#include <stdlib.h>
using namespace std;

GameMouse::GameMouse(Tile *** tiles_)
{
	tiles = tiles_;
	last_locked_tile = NULL;
	current_tile = NULL;
	drawing = false;
	tempPathSegment = NULL;
}

void GameMouse::Click()
{
	if(!drawing)
	{
		if(MouseOnScreen())
		{
			printf("Starting to draw\n");
			current_tile = GetTileFromMouse();
			if(current_tile != NULL)
			{
				drawing = true;
			}
		}
	}
}

void GameMouse::Release()
{
	if(tempPathSegment != NULL)
	{
		MakeTempPathSegmentReal();
	}
	last_locked_tile = NULL;
	current_tile = NULL;
	drawing = false;
	tempPathSegment = NULL;

	
}

void GameMouse::CreateTempPathSegment(bool replace)
{
	if(!replace)
	{
		if(tempPathSegment != NULL)
		{
			MakeTempPathSegmentReal();
		}
	}
	else
	{
		if(tempPathSegment != NULL)
			delete tempPathSegment;
		tempPathSegment = NULL;
	}
	tempPathSegment = new PathSegment(last_locked_tile, current_tile, game->priority);
}

void GameMouse::MakeTempPathSegmentReal()
{
	printf("Making a segment real\n");
	Tile * from = tempPathSegment->from;
	Tile * to = tempPathSegment->to;
	from->clearPathFrom(game->priority);
	to->clearPathTo(game->priority);
	if(from->pos.x - 1 == to->pos.x && from->pos.y - 1 == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[0] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[7] = tempPathSegment;
	}
	else if(from->pos.x == to->pos.x && from->pos.y - 1 == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[1] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[6] = tempPathSegment;
	}
	else if(from->pos.x + 1 == to->pos.x && from->pos.y - 1 == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[2] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[5] = tempPathSegment;
	}
	else if(from->pos.x - 1 == to->pos.x && from->pos.y == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[3] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[4] = tempPathSegment;
	}
	else if(from->pos.x + 1 == to->pos.x && from->pos.y == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[4] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[3] = tempPathSegment;
	}
	else if(from->pos.x - 1 == to->pos.x && from->pos.y + 1 == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[5] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[2] = tempPathSegment;
	}
	else if(from->pos.x == to->pos.x && from->pos.y + 1 == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[6] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[1] = tempPathSegment;
	}
	else if(from->pos.x + 1 == to->pos.x && from->pos.y + 1 == to->pos.y )
	{
		tiles[from->pos.x][from->pos.y]->dirs[7] = tempPathSegment;
		tiles[to->pos.x][to->pos.y]->dirs[0] = tempPathSegment;
	}
	else
	{
		printf("Real Issue: Attempting to creat path that doesn't make sense\n");
	}
}

void GameMouse::NewFrame()
{
	if(drawing)
	{
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->Release();
		}
		Tile * temp_tile = GetTileFromMouse();
		if(temp_tile != current_tile)
		{
			printf("Moving to a new tile\n");
			if(last_locked_tile != NULL && (
				abs(temp_tile->pos.x - last_locked_tile->pos.x) >= 2 ||
				abs(temp_tile->pos.y - last_locked_tile->pos.y) >= 2))
			{
				printf("Making old temp segment real\n");
				last_locked_tile = current_tile;
				current_tile = temp_tile;
				CreateTempPathSegment(false);
			}
			else
			{
				printf("Replacing old temp segment\n");
				if(last_locked_tile != NULL)
				{
					current_tile = temp_tile;
				}
				else
				{
					last_locked_tile = current_tile;
					current_tile = temp_tile;
				}
				CreateTempPathSegment(true);
			}
		}
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->Click();
	}
}

Tile * GameMouse::GetTileFromMouse()
{
	sf::Vector2i mouse_vec = sf::Mouse::getPosition(*(assets->window));
	int pix_x = mouse_vec.x;
	int pix_y = mouse_vec.y;
	return GetTileFromPix(pix_x, pix_y);
}

Tile * GameMouse::GetTileFromPix(int pix_x, int pix_y)
{
	// printf("Get tile from pix\n");
	if(MouseOnScreen())
	{
		int tile_x = pix_x / TILE_SIZE;
		int tile_y = pix_y / TILE_SIZE;
		if(tile_x > BOARD_SIZE || tile_y > BOARD_SIZE)
		{
			return NULL;
		}
		// printf("pix_x: %d, pix_y %d, tile_x: %d, tile_y: %d\n", pix_x, pix_y, tile_x, tile_y);
		return tiles[tile_x][tile_y];
	}
	else
	{
		return NULL;
	}
}

bool GameMouse::MouseOnScreen()
{
	sf::Vector2i mouse_vec = sf::Mouse::getPosition(*(assets->window));
	int x = mouse_vec.x;
	int y = mouse_vec.y;
	if(x >= TILE_SIZE * BOARD_SIZE)
		return false;

	return true;
	//?
}

void GameMouse::draw()
{
	if(tempPathSegment != NULL)
	{
		tempPathSegment->draw();
	}
}