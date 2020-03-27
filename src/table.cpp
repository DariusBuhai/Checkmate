//
// Created by Darius Buhai on 3/26/20.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "../include/table.h"
#include "../include/types.h"

using namespace std;
using namespace sf;

void Table::setSize(size_type s) {
    this->size = s;
}

void Table::setPosition(position_type p) {
    this->position = p;
}

void Table::draw(sf::RenderWindow *window) {

    draw_outline(window, size, position);
    draw_grid(window, size_type(size.width-2*padding, size.height-2*padding), position_type(position.x + padding, position.y + padding));
}

void Table::draw_outline(sf::RenderWindow *window, size_type s, position_type p){

    RectangleShape fill(Vector2f(s.width - 2*border_width, s.height - 2*border_width));
    fill.setOutlineThickness((float)border_width);
    fill.setOutlineColor(Color::Black);
    fill.setPosition(p.x + border_width, p.y + border_width);
    window->draw(fill);

}

void Table::draw_grid(sf::RenderWindow *window, size_type s, position_type p){

    double squareWidth = (s.width) / 8;
    double squareHeight = (s.height) / 8;

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){
            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(p.x +squareWidth*i, p.y + squareHeight*j);
            if((i+j)%2==0)
                square.setFillColor(Color::Black);
            else
                square.setFillColor(Color::White);
            window->draw(square);
        }
}
