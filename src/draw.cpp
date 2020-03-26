#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../include/draw.h"
#include "../include/table.h"

int Draw::draw() {

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(this->screen_width, this->screen_height, 32), "Checkmate AI",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    Table table;
    window.draw(table.getVisual());

    window.display();

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
