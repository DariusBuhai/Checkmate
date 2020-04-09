//
// Created by Darius Buhai on 3/26/20.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "../include/table.h"
#include "../include/types.h"
#include "../include/rules.h"

using namespace std;
using namespace sf;

Table::Table(){}
Table::~Table(){}

void Table::setSize(size_type s) {
    this->size = s;
}

void Table::setPosition(position_type p) {
    this->position = p;
}

void Table::draw(sf::RenderWindow *window) {

    drawIndicators(window, size, position);
    drawOutline(window, size_type(size.width-indicator_spacing, size.height-indicator_spacing), position_type(position.x+indicator_spacing, position.y));
    drawGrid(window, size_type(size.width-2*padding-indicator_spacing, size.height-2*padding-indicator_spacing), position_type(position.x + indicator_spacing + padding, position.y + padding));

    for(auto piece : rules.getPieces())
        drawPiece(window, *piece);

}

void Table::drawIndicators(sf::RenderWindow *window, size_type s, position_type p){

    double indicatorHeight = (s.height-indicator_spacing) / 8;
    double indicatorWidth = (s.width-indicator_spacing) / 8;

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

void Table::drawOutline(sf::RenderWindow *window, size_type s, position_type p){

    RectangleShape fill(Vector2f(s.width - 2*border_width, s.height - 2*border_width));
    fill.setOutlineThickness((float)border_width);
    fill.setOutlineColor(Color(120, 120, 120));
    fill.setPosition(p.x + border_width, p.y + border_width);
    window->draw(fill);

}

void Table::drawGrid(sf::RenderWindow *window, size_type s, position_type p){

    double squareWidth = (s.width) / 8;
    double squareHeight = (s.height) / 8;

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){
            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(p.x +squareWidth*i, p.y + squareHeight*j);

            if((i+j)%2==0) square.setFillColor(Color(140, 140, 140));
            else square.setFillColor(Color::White);

            pair<int, int> current_pos = {i, j};
            if(selected_square==current_pos){
                square.setOutlineColor(Color::Red);
                square.setSize(Vector2f(squareWidth-4, squareHeight-4));
                square.setOutlineThickness(4);
            }
            if(find(future_positions.begin(), future_positions.end(), current_pos)!=future_positions.end()){
                square.setOutlineColor(Color::Black);
                square.setSize(Vector2f(squareWidth-4, squareHeight-4));
                square.setOutlineThickness(4);
            }
            window->draw(square);
        }
}

pair<int, int> Table::determine_grid_position(position_type pos){

    pair<int, int> r(0,0);

    size_type s(size.width-2*padding-indicator_spacing, size.height-2*padding-indicator_spacing);
    position_type p(position.x + indicator_spacing + padding, position.y + padding);

    if(pos.x>=p.x && pos.x<=p.x+s.width && pos.y>=p.y && pos.y <= p.y + s.height){
        r.first = (int) (pos.x - p.x) / (s.width/8);
        r.second = (int) (pos.y - p.y) / (s.height/8);
    }else{
        throw EXIT_FAILURE;
    }

    return r;

}

void Table::resetFuturePositions(){
    this->future_positions.clear();
}

void Table::resetSelectedSquare(){
    this->selected_square = {-1,-1};
}

void Table::updateSelectedSquare(pair<int, int> new_position){
    if(!(new_position.first>=0 && new_position.first<8 && new_position.second>=0 && new_position.second<8)) return;
    this->selected_square = new_position;
    Piece* current = rules.getPiece(new_position);
    if(find(future_positions.begin(), future_positions.end(), new_position)!=future_positions.end()){
        rules.movePiece(last_selected_piece, new_position);
        resetFuturePositions();
        resetSelectedSquare();
        return;
    }
    resetFuturePositions();
    if(current != nullptr){
        last_selected_piece = current;
        try{
            vector<pair<int, int>> future_positions = rules.getFuturePositions(current);
            this->future_positions = future_positions;
        }catch (int e){
            cout<<"An error occurred trying to find future positions!";
        }
    }
}

void Table::digestAction(sf::Event event){
    if(event.type==sf::Event::MouseButtonPressed){
        try{
            pair<int, int> grid_position = this->determine_grid_position(position_type(event.mouseButton.x, event.mouseButton.y));
            if(grid_position==selected_square){
                resetFuturePositions();
                return resetSelectedSquare();
            }
            updateSelectedSquare(grid_position);
        }catch (int e){
            cout<<"Pressed outside the table"<<'\n';
        }
    }else if(event.type==sf::Event::KeyPressed){
        if(selected_square.first!=-1 && selected_square.second!=-1){
            if(event.key.code==Keyboard::Right)
                updateSelectedSquare({selected_square.first+1, selected_square.second});
            else if(event.key.code==Keyboard::Left)
                updateSelectedSquare({selected_square.first-1, selected_square.second});
            else if(event.key.code==Keyboard::Up)
                updateSelectedSquare({selected_square.first, selected_square.second-1});
            else if(event.key.code==Keyboard::Down)
                updateSelectedSquare({selected_square.first, selected_square.second+1});
        }
    }

}

void Table::drawPiece(sf::RenderWindow* window, Piece piece){

    size_type s(this->size.width - this->border_width - this->indicator_spacing, this->size.height - this->border_width - this->indicator_spacing);
    position_type p(this->position.x + this->indicator_spacing + piece.getPos().first * (s.width/8), this->position.y + piece.getPos().second * (s.height/8));

    sf::Texture piece_img;

    string img_location = "resources/pieces/"+piece.getType()+"_";
    img_location += (piece.getPlayer()) ? "black" : "white";
    img_location += ".png";

    if (!piece_img.loadFromFile(img_location)) throw EXIT_FAILURE;

    sf::Sprite item;
    item.setTexture(piece_img);
    item.setPosition(Vector2f(p.x, p.y));
    item.setScale(0.3, .3);
    item.setOrigin(-110, -50);

    window->draw(item);
}


