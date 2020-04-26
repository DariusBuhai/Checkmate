#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../include/utils.h"
#include "../include/materials.h"

using namespace std;
using namespace sf;

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

Button &Button::operator=(std::pair<std::string, std::string> _texts) {
    this->text = _texts.first;
    this->disabledText = _texts.second;
    return *this;
}

void Label::draw(sf::RenderWindow* window, bool darkMode){
    Utils::drawText(window, text, darkMode ? oppositeColor : color, position, size);
}

Label &Label::operator=(std::string _text) {
    this->text = std::move(_text);
    return *this;
}
