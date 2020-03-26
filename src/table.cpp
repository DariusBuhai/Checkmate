//
// Created by Darius Buhai on 3/26/20.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../include/table.h"

sf::RectangleShape Table::getVisual() {

    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    return rectangle;
    //window.draw(rectangle);
}
