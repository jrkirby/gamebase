
#include <vector>
#include <stdlib.h>
#include <random>

#include "classes.h"

using namespace std;

Board::Board(int seed, bool tutorial)
{
	tiles = (Tile ***) malloc(sizeof(Tile **) * BOARD_SIZE);
	for(int x = 0; x < BOARD_SIZE; x++)
	{
		tiles[x] = (Tile **) malloc(sizeof(Tile *) * BOARD_SIZE);
		for(int y = 0; y < BOARD_SIZE; y++)
		{
			tiles[x][y] = new Tile(x, y, tiles);
		}
	}
	if(tutorial)
	{
		Base * tutorial_base = new Base(8, 8, tiles);
		bases.push_back(tutorial_base);
		Worker * tutorial_worker = new Worker(8, 6, tiles);
		workers.push_back(tutorial_worker);
		Resource * tutorial_resource = new Resource(8, 2, tiles);
		resources.push_back(tutorial_resource);
	}
	else
	{
		seed_seq seed;
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, BOARD_SIZE - 1);

		for(int i = 0; i < 13; i++)
		{
			int x = distribution(generator);
			int y = distribution(generator);
			// printf("resources: x: %d, y: %d\n", x, y);s
			if(tiles[x][y]->empty())
			{
				Resource * temp = new Resource(x, y, tiles);
				resources.push_back(temp);
			}
		}

		for(int i = 0; i < 6; i++)
		{
			int x = distribution(generator);
			int y = distribution(generator);
			if(tiles[x][y]->empty())
			{
				Worker * temp = new Worker(x, y, tiles);
				workers.push_back(temp);
			}
		}
		int x = distribution(generator);
		int y = distribution(generator);
		while(!(tiles[x][y]->empty()))
		{
			x = distribution(generator);
			y = distribution(generator);
		}
		Base * temp = new Base(x, y, tiles);
		bases.push_back(temp);
	}
}

Board::~Board()
{

}

void Board::draw()
{
	for(int x = 0; x < BOARD_SIZE; x++)
	{
		for(int y = 0; y < BOARD_SIZE; y++)
		{
			tiles[x][y]->draw();
		}
	}
	for(int x = 0; x < BOARD_SIZE; x++)
	{
		for(int y = 0; y < BOARD_SIZE; y++)
		{
			tiles[x][y]->draw_arrows();
		}
	}
	for(uint i = 0; i < resources.size(); i++)
	{
		resources[i]->draw();
	}
	for(int x = 0; x < BOARD_SIZE; x++)
	{
		for(int y = 0; y < BOARD_SIZE; y++)
		{
			tiles[x][y]->draw_worker();
			tiles[x][y]->draw_base();
		}
	}
}

void Board::MoveWorkers()
{
	for(uint i = 0; i < workers.size(); i++)
	{
		workers[i]->Move();
	}
}

void Board::ResetWorkers()
{
	for(uint i = 0; i < workers.size(); i++)
	{
		workers[i]->Reset();
	}
}

void Board::ResetResources()
{
	for(uint i = 0; i < resources.size(); i++)
	{
		resources[i]->Reset();
	}
}

void Board::DeletePaths()
{
	for(int x = 0; x < BOARD_SIZE; x++)
	{
		for(int y = 0; y < BOARD_SIZE; y++)
		{
			tiles[x][y]->clearPathFrom(1);
			tiles[x][y]->clearPathFrom(2);
			tiles[x][y]->clearPathFrom(3);
			tiles[x][y]->clearPathTo(1);
			tiles[x][y]->clearPathTo(2);
			tiles[x][y]->clearPathTo(3);
		}
	}
}
