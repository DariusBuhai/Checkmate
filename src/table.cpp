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

void Table::draw(sf::RenderWindow *window, encapsulation e) {

    /// Determine exterior margin
    double ext = this->margin + this->padding + this->border_width;

    double squareWidth = (e.width-2*ext) / 8;
    double squareHeight = (e.height-2*ext) / 8;

    window->draw(RectangleShape(Vector2f(e.width, e.height)));

    cout<<squareWidth<<' '<<squareHeight;

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){

            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(squareWidth*i+ext, squareHeight*j+ext);
            if((i+j)%2==0)
                square.setFillColor(Color::Black);
            else
                square.setFillColor(Color::White);
            window->draw(square);
        }

}
