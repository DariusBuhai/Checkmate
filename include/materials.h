#ifndef CHECKMATE_MATERIALS_H
#define CHECKMATE_MATERIALS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../include/utils.h"

class Button{
    std::pair<int,int> x, y;
    std::string text, disabledText = "";
    sf::Color backgroundColor, color;
    bool *pressed;
    bool hovering;

    void setCursorToHand(sf::RenderWindow*);
public:
    Button(std::pair<int, int> _x, std::pair<int, int> _y, bool *_pressed, std::string _text, std::string _disabledText = ""): x(_x), y(_y), pressed(_pressed), text(_text), disabledText(_disabledText){}

    void draw(sf::RenderWindow*, bool = false);
    void digestAction(sf::Event, sf::RenderWindow*);

    void setBackgroundColor(sf::Color);
    void setColor(sf::Color);
};

template <class T>
class Container{
    std::vector<T> childs;
    bool *darkMode;
    double screenWidth, screenHeight;
public:
    void draw(sf::RenderWindow * window) {
        for(T child: this->childs)
            child->draw(window, *this->darkMode);
    }

    void digestAction(sf::Event event, sf::RenderWindow * window) {
        for(T child: this->childs)
            child->digestAction(event, window);
    }

    void setDarkMode(bool* _darkMode){
        this->darkMode = _darkMode;
    }

    Container<T>* operator+=(T append){
        this->childs.push_back(append);
        return this;
    }
};

#endif //CHECKMATE_MATERIALS_H
