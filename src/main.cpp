#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "classes.h"

Assets * assets;
Game * game;
// Program entry point
int main(int argc, char ** argv) {

    assets = new Assets();

    sf::Clock * frame_timer = new sf::Clock();
    frame_timer->restart();

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(10 * 64 + 4 * 32, 10 * 64), "OptimalMiners");

    assets->setWindow(&window);
    Board * game_board = new Board(-1, true);
    UI * ui = new UI();
    game = new Game(game_board);

    GameMouse * mouse = new GameMouse(game_board->tiles);
    sf::Event event;    // For polling events that SFML sends us

    while (window.isOpen()) {

        // Process any events sent by SFML since the last frame
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // SFML sent us a close event, so clean up
                window.close();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // printf("Mouse click\n");
            mouse->Click();
            ui->click();
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            mouse->Release();
        }

        game->Animate();


        if(frame_timer->getElapsedTime() > sf::milliseconds(33))
        {
            frame_timer->restart();
            // printf("drawing\n");

            mouse->NewFrame();

            // Clear the window before we start drawing to it
            window.clear();

            game_board->draw();
            mouse->draw();
            ui->draw();
            // Notify the window that we're ready to render
            window.display();
        }
        else
        {
            // printf("Waiting\n");
        }

    }

    return 0;
}
