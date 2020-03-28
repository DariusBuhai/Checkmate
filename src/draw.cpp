#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../include/draw.h"
#include "../include/table.h"
//#include "table.cpp"

using namespace std;
using namespace sf;

Draw::Draw() {
    this->init();
}

void Draw::init(){

    /// Create the window of the application
    RenderWindow window(VideoMode(this->screen_width, this->screen_height, 32), "Checkmate AI",Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    
    while(window.isOpen()){
        Event event;
        window.clear();
        this->draw(&window);
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
        if(event.type == sf::Event::MouseButtonPressed){
            table.digest_action(position_type(event.mouseButton.x, event.mouseButton.y));
        }
        window.display();
    }
}

void Draw::draw(sf::RenderWindow* window) {

    table.setSize(size_type(screen_width-50, screen_height-50));
    table.setPosition(position_type(25, 25));

    /// Draw contents
    window->draw(RectangleShape(Vector2f(screen_width, screen_height)));

    table.draw(window);

    table.draw_rook_white(window, 1, 7);
    table.draw_rook_white(window, 8, 7);
    table.draw_horse_white(window, 2, 7);
    table.draw_horse_white(window, 7, 7);
    table.draw_bishop_white(window, 3, 7);
    table.draw_bishop_white(window, 6, 7);
    table.draw_queen_white(window, 4, 7);
    table.draw_king_white(window, 5, 7);
    for(int i = 1 ; i <= 8 ; i ++ )
        table.draw_pawn_white(window, i, 6);
    table.draw_rook_black(window, 1, 0);
    table.draw_rook_black(window, 8, 0);
    table.draw_horse_black(window, 2, 0);
    table.draw_horse_black(window, 7, 0);
    table.draw_bishop_black(window, 3, 0);
    table.draw_bishop_black(window, 6, 0);
    table.draw_queen_black(window, 4, 0);
    table.draw_king_black(window, 5, 0);
    for(int i = 1 ; i <= 8 ; i ++ )
        table.draw_pawn_black(window, i, 1);
}

