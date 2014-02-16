#include "classes.h"
#include <SFML/Graphics.hpp>

Assets::Assets()
{
	tile_texture = new sf::Texture();
	if(!tile_texture->loadFromFile("assets/Tile.png"))
	{
		printf("Problem with assets\n");
	}
	arrow_texture = new sf::Texture();
	if(!arrow_texture->loadFromFile("assets/Arrow.png"))
	{
		printf("Problem with assets\n");
	}
	diagonal_arrow_texture = new sf::Texture();
	if(!diagonal_arrow_texture->loadFromFile("assets/ArrowDiagonal.png"))
	{
		printf("Problem with assets\n");
	}
	worker_texture = new sf::Texture();
	if(!worker_texture->loadFromFile("assets/Worker.png"))
	{
		printf("Problem with assets\n");
	}
	base_texture = new sf::Texture();
	if(!base_texture->loadFromFile("assets/Base.png"))
	{
		printf("Problem with assets\n");
	}
	resource_texture = new sf::Texture();
	if(!resource_texture->loadFromFile("assets/Resource.png"))
	{
		printf("Problem with assets\n");
	}
	resource_depleted_texture = new sf::Texture();
	if(!resource_depleted_texture->loadFromFile("assets/ResourceDepleted.png"))
	{
		printf("Problem with assets\n");
	}

	play_texture = new sf::Texture();
	if(!play_texture->loadFromFile("assets/Play.png"))
	{
		printf("Problem with assets\n");
	}
	pause_texture = new sf::Texture();
	if(!pause_texture->loadFromFile("assets/Pause.png"))
	{
		printf("Problem with assets\n");
	}
	stop_texture = new sf::Texture();
	if(!stop_texture->loadFromFile("assets/Stop.png"))
	{
		printf("Problem with assets\n");
	}
	fast_texture = new sf::Texture();
	if(!fast_texture->loadFromFile("assets/Fast.png"))
	{
		printf("Problem with assets\n");
	}

	delete_texture = new sf::Texture();
	if(!delete_texture->loadFromFile("assets/Delete.png"))
	{
		printf("Problem with assets\n");
	}

}

Assets::~Assets()
{

}

void Assets::setWindow(sf::RenderWindow * window_)
{
	window = window_;
}
