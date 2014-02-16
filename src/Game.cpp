#include "classes.h"

Game::Game(Board * board_)
{
	paused = true;
	frame = -1;
	board = board_;
	priority = 1;
	speed = 0;
}

Game::~Game()
{
	delete board;
}

bool Game::Active()
{
	if(frame == -1)
	{
		return false;
	}
	return true;
}

void Game::Animate()
{
	if(speed == 0)
		return;
	if(!paused)
		frame++;
	board->MoveWorkers();
}
void Game::Reset()
{
	board->ResetWorkers();
	board->ResetResources();
}
void Game::ResetPaths()
{
	board->DeletePaths();
}

