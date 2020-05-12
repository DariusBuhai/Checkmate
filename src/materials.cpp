#include <SFML/Graphics.hpp>

#include <utility>

#include "../include/utils.h"
#include "../include/materials.h"

#if defined(_WIN32)
    #define ScreenWidth 900
    #define ScreenHeight 900
#else
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#endif

using namespace std;
using namespace sf;


void Button::digestAction(sf::Event event, sf::RenderWindow* window){
    if(event.type==sf::Event::MouseButtonPressed)
        if(Utils::mouseInsideLimits(event, this->x, this->y)){
            *this->pressed = !*this->pressed;
            *this->cursorHand = true;
        }
    if(event.type==sf::Event::MouseMoved){
        if(Utils::mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, this->x, this->y)){
            *this->cursorHand = true;
            hovering = true;
        }
        else hovering = false;
    }
}

void Button::draw(sf::RenderWindow* window, bool darkMode){
    string t = this->text;
    if(*this->pressed && !this->disabledText.empty())
        t = this->disabledText;

    const int elevation = 6;
    if(hovering){
        Utils::drawBox(window, x, y, !darkMode ? Color::Black : Color::White, Color::Transparent);
        Utils::drawBox(window, {x.first+elevation, x.second+elevation}, {y.first+elevation, y.second+elevation}, !darkMode ? Color::Black : Color::White, darkMode ? Color(46,47,49) : Color(236,236,236));
    }

    Utils::drawText(window, t, darkMode ? Color::White : Color::Black, {hovering ? x.first+elevation : x.first,1100-(hovering ? y.first+elevation : y.first)});
}

Button &Button::operator=(const std::pair<std::string, std::string>& _texts) {
    this->text = _texts.first;
    this->disabledText = _texts.second;
    return *this;
}

void Label::draw(sf::RenderWindow* window, bool darkMode){
    Utils::drawText(window, text, darkMode ? oppositeColor : color, position, size);
}

void Label::setColor(sf::Color _color, sf::Color _oppositeColor) {
    this->color = _color;
    this->oppositeColor = _oppositeColor;
}

Label &Label::operator=(std::string _text) {
    this->text = std::move(_text);
    return *this;
}
