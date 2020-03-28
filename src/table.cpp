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

    draw_indicators(window, size, position);
    draw_outline(window, size_type(size.width-indicator_spacing, size.height-indicator_spacing), position_type(position.x+indicator_spacing, position.y));
    draw_grid(window, size_type(size.width-2*padding-indicator_spacing, size.height-2*padding-indicator_spacing), position_type(position.x + indicator_spacing + padding, position.y + padding));

}

void Table::draw_indicators(sf::RenderWindow *window, size_type s, position_type p){

    double indicatorHeight = (s.height-indicator_spacing) / 8;
    double indicatorWidth = (s.width-indicator_spacing) / 8;

    /// Ok, hai sa ti explic ca sa nu iti incingi creierul
    /// Deci,
    /// p si s sunt pozitiile si dimensiunile in care trebuie sa se incadreze in total
    /// la astea adaugam dimensiunea permisa pentru indicator (indicator_spacing)
    /// dupa aia trebuie sa ii mai adaugam si 1/2 din inaltime si lungime pentru a-l pozitiona pe mijloc
    /// dar ... mai trebuie scazut si 1/2 din dimensiunea fontului

    for(int i=0;i<8;i++){
        Text l;
        sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
        l.setString(string(1, '1'+(7-i)));
        l.setFont(font);
        l.setCharacterSize(40);
        l.setFillColor(sf::Color::Black);
        l.setPosition(p.x + indicator_spacing / 2 -20, p.y +indicatorHeight*i + indicatorHeight/2 - 20);
        window->draw(l);
    }
    for(int j=0;j<8;j++){
        Text l;
        sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
        l.setString(string(1, 'A'+j));
        l.setFont(font);
        l.setCharacterSize(40);
        l.setFillColor(sf::Color::Black);
        l.setPosition(p.x + indicatorWidth * j + indicator_spacing + indicatorWidth / 2 - 20, s.height - indicatorHeight / 2 + 20);
        window->draw(l);
    }
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
                square.setFillColor(Color::Blue);
            else
                square.setFillColor(Color::White);
            window->draw(square);
        }
}

void Table::draw_piece(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/pawn_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_pawn_black(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/pawn_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);

}

void Table::draw_pawn_white(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/White_pawn.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);

}

void Table::draw_horse_white(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/horse_white.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_horse_black(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/horse_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_bishop_white(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/bishop_white.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_bishop_black(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/bishop_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);

}

void Table::draw_king_white(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/king_white.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_king_black(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/king_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_queen_white(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/queen_white.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_queen_black(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/queen_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_rook_white(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/rook_white.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}

void Table::draw_rook_black(sf::RenderWindow* window, int i, int j){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + i * (s.width/8), this->position.y + j * (s.height/8));

    sf::Texture piece_img;
    if (!piece_img.loadFromFile("resources/pieces/rook_black.png")) throw EXIT_FAILURE;

    sf::Sprite piece;
    piece.setTexture(piece_img);
    piece.setPosition(Vector2f(p.x, p.y));
    piece.setScale(1.3, 1.3);
    piece.setOrigin(-15, -25);

    window->draw(piece);
}



