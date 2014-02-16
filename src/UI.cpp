
#include "classes.h"
UI::UI()
{
	stop.setTexture(*(assets->stop_texture));
	stop.setPosition(sf::Vector2f(640 +  0, 32));
	pause.setTexture(*(assets->pause_texture));
	pause.setPosition(sf::Vector2f(640 + 32, 32));
	play.setTexture(*(assets->play_texture));
	play.setPosition(sf::Vector2f(640 + 64, 32));
	fast.setTexture(*(assets->fast_texture));
	fast.setPosition(sf::Vector2f(640 + 96, 32));

	priority1.setTexture(*(assets->arrow_texture));
	priority1.setPosition(sf::Vector2f(640, 64));
	priority1.setColor(sf::Color(220, 0, 0));
	priority1.scale(2.0, 2.0);
	priority2.setTexture(*(assets->arrow_texture));
	priority2.setPosition(sf::Vector2f(640, 128));
	priority2.setColor(sf::Color(220, 220, 0));
	priority2.scale(2.0, 2.0);
	priority3.setTexture(*(assets->arrow_texture));
	priority3.setPosition(sf::Vector2f(640, 192));
	priority3.setColor(sf::Color(0, 220, 0));
	priority3.scale(2.0, 2.0);

	deletebutton.setTexture(*(assets->delete_texture));
	deletebutton.setPosition(sf::Vector2f(640, 300));
	deletebutton.scale(2.0, 2.0);
}

void UI::PressStop()
{
	game->speed = 0;
	game->Reset();
}
void UI::PressPause()
{
	game->speed = 0;
	game->paused = true;
}
void UI::PressPlay()
{
	game->paused = false;
	game->speed = 1;
}
void UI::PressFast()
{
	game->paused = false;
	game->speed++;
}

void UI::PressPriority1()
{
	game->priority = 1;
}
void UI::PressPriority2()
{
	game->priority = 2;
}
void UI::PressPriority3()
{
	game->priority = 3;
}
void UI::PressDelete()
{
	game->ResetPaths();
}


void UI::click()
{

	sf::Vector2i mouse_vec = sf::Mouse::getPosition(*(assets->window));
	int x = mouse_vec.x;
	int y = mouse_vec.y;
	if(y >= 32 && y <= 64)
	{
		if(x >= 640 + 96)
		{
			PressFast();
		}
		else if(x >= 640 + 64)
		{
			PressPlay();
		}
		else if(x >= 640 + 32)
		{
			PressPause();
		}
		else if(x >= 640)
		{
			PressStop();
		}
	}
	else if(y < 128 && x > 640)
	{
		PressPriority1();
	}
	else if(y < 192 && x > 640)
	{
		PressPriority2();
	}
	else if(y < 280 && x > 640)
	{
		PressPriority3();
	}
	else if(y < 450 && x > 640)
	{
		PressDelete();
	}
}

void UI::draw()
{
	assets->window->draw(stop);
	assets->window->draw(pause);
	assets->window->draw(play);
	assets->window->draw(fast);

	assets->window->draw(priority1);
	assets->window->draw(priority2);
	assets->window->draw(priority3);

	assets->window->draw(deletebutton);
}
