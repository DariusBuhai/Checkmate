#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../include/utils.h"
#include "../include/materials.h"

using namespace std;
using namespace sf;

void Button::setBackgroundColor(sf::Color _background) {
    this->backgroundColor = _background;
}

void Button::setColor(sf::Color _color) {
    this->color = _color;
}

void Button::setCursorToHand(sf::RenderWindow* window) {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Hand);
    window->setMouseCursor(cursor);
}

void Button::digestAction(sf::Event event, sf::RenderWindow* window){
    if(event.type==sf::Event::MouseButtonPressed)
        if(Utils::mouseInsideLimits(event, this->x, this->y)){
            *this->pressed = !*this->pressed;
            setCursorToHand(window);
        }
    if(event.type==sf::Event::MouseMoved){
        if(Utils::mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, this->x, this->y)){
            setCursorToHand(window);
            hovering = true;
        }
        else
            hovering = false;
    }
}

void Button::draw(sf::RenderWindow* window, bool darkMode){
    string t = this->text;
    if(*this->pressed && !this->disabledText.empty())
        t = this->disabledText;

    Utils::drawText(window, t, hovering ? Color::Blue : (darkMode ? Color::White : Color::Black), {x.first,1100-(hovering ? y.first+5 : y.first)});
}