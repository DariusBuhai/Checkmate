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

    RectangleShape fill(Vector2f(size.width - 2*border_width, size.height - 2*border_width));
    fill.setOutlineThickness(border_width);
    fill.setOutlineColor(Color::Black);
    fill.setPosition(position.x + border_width, position.y + border_width);
    window->draw(fill);

    /// Determine exterior margin
    double ext = padding;
    double squareWidth = (size.width - 2*ext) / 8;
    double squareHeight = (size.height - 2*ext) / 8;

    cout<<squareWidth<<' '<<squareHeight;

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){
            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(squareWidth*i+ext+position.x, squareHeight*j+ext+position.y);
            if((i+j)%2==0)
                square.setFillColor(Color::Black);
            else
                square.setFillColor(Color::White);
            window->draw(square);
        }
}
