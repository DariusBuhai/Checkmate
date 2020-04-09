#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../include/piece.h"
#include "../include/draw.h"
#include "../include/types.h"

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
            digestAction(&window, event);
        }
        window.display();
    }
}

bool Draw::mouseInsideLimits(pair<int, int> location, std::pair<int, int> x, std::pair<int,int> y, bool reverse_y, bool reverse_x){
    if(reverse_y){
        y.first = screen_height-y.first;
        y.second = screen_height-y.second;
    }
    if(reverse_x){
        x.first = screen_height-x.first;
        x.second = screen_height-x.second;
    }

    return (location.first > x.first && location.first < x.second) &&
           (location.second >  y.first && location.second <= y.second);
}

bool Draw::mouseInsideLimits(sf::Event event, std::pair<int, int> x, std::pair<int,int> y, bool reverse_y, bool reverse_x){
    return mouseInsideLimits({event.mouseButton.x,event.mouseButton.y}, x, y, reverse_y, reverse_x);
}

void Draw::digestAction(sf::RenderWindow* window, sf::Event event){
    table.digestAction(event);

    if(event.type==sf::Event::MouseButtonPressed){
        if(mouseInsideLimits(event, {80, 320}, {200, 120}, true))
            table.resetGame();
    }
    if(event.type==sf::Event::MouseMoved){
        sf::Cursor cursor;
        hoveringResetButton = false;
        hoveringPreviousMoveButton = false;
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {80, 320}, {200, 120}, true)){
            cursor.loadFromSystem(sf::Cursor::Hand);
            hoveringResetButton = true;
        }
        window->setMouseCursor(cursor);
    }
}

void Draw::drawButton(sf::RenderWindow* window, string title, sf::Color color, std::pair<int, int> position){
    sf::Text button = sf::Text();
    button.setString(title);
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
    button.setFont(font);
    button.setCharacterSize(40);
    button.setFillColor(color);
    button.setPosition(position.first, position.second);
    window->draw(button);
}

void Draw::draw(sf::RenderWindow* window) {

    table.setSize(size_type(screen_width-150, screen_height-150));
    table.setPosition(position_type(25, 25));

    window->draw(RectangleShape(Vector2f(screen_width, screen_height)));

    drawButton(window, "Reset Game", hoveringResetButton ? sf::Color::Red : sf::Color::Blue, {100,screen_height-160});
    drawButton(window, "Undo Move", hoveringPreviousMoveButton ? sf::Color::Red : sf::Color::Blue, {400,screen_height-160});
    drawButton(window, "Play with AI", hoveringPreviousMoveButton ? sf::Color::Red : sf::Color::Blue, {700,screen_height-160});

    table.draw(window);

}

