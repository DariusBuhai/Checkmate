#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../include/draw.h"
#include "../include/table.h"

using namespace std;
using namespace sf;

Draw::Draw() {
    this->init();
}

void Draw::init(){

    /** Create the window of the application */
    RenderWindow window(VideoMode((unsigned int)screen_width, (unsigned int)screen_height, 32), "Checkmate AI",Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    while(window.isOpen()){
        Event event;
        window.clear();
        this->draw(&window);
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
            digestAction(event);
        }
        window.display();
    }
}

void Draw::digestAction(sf::Event event){
    table.digestAction(event);
}

void Draw::draw(sf::RenderWindow* window) {

    table.setSize(size_type(screen_width-150, screen_height-150));
    table.setPosition(position_type(25, 25));

    /// Draw contents
    window->draw(RectangleShape(Vector2f(screen_width, screen_height)));

    sf::Text button = sf::Text();
    button.setString("Reset Game");
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
    button.setFont(font);
    button.setCharacterSize(40);
    button.setFillColor(sf::Color::Blue);
    button.setPosition(100, screen_height-100);
    window->draw(button);

    table.draw(window);

}

