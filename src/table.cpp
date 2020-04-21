//
// Created by Darius Buhai on 3/26/20.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "../include/piece.h"
#include "../include/table.h"
#include "../include/types.h"
#include "../include/rules.h"
#include "../include/brain.h"

using namespace std;
using namespace sf;

Table::Table(){
    brain = new Brain(&rules);
}

Table::~Table(){};

void Table::setSize(sizeType s) {
    this->size = s;
}

void Table::setPosition(positionType p) {
    this->position = p;
}

void Table::setDarkMode(bool dm){
    darkMode = dm;
}

void Table::draw(sf::RenderWindow *window) {

    drawIndicators(window, size, position);
    drawOutline(window, sizeType(size.width-indicatorSpacing, size.height-indicatorSpacing), positionType(position.x+indicatorSpacing, position.y));
    drawGrid(window, sizeType(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing), positionType(position.x + indicatorSpacing + padding, position.y + padding));

    for(auto piece : rules.getPieces())
        drawPiece(window, piece);

}

void Table::drawIndicators(sf::RenderWindow *window, sizeType s, positionType p){

    double indicatorHeight = (s.height-indicatorSpacing) / 8;
    double indicatorWidth = (s.width-indicatorSpacing) / 8;

    for(int i=0;i<8;i++){
        Text l;
        sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
        l.setString(string(1, '1'+(7-i)));
        l.setFont(font);
        l.setCharacterSize(40);
        l.setFillColor(darkMode ? sf::Color::White : sf::Color::Black);
        l.setPosition(p.x + indicatorSpacing / 2 + 20, p.y +indicatorHeight*i + indicatorHeight/2 - 20);
        window->draw(l);
    }
    for(int j=0;j<8;j++){
        Text l;
        sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
        l.setString(string(1, 'A'+j));
        l.setFont(font);
        l.setCharacterSize(40);
        l.setFillColor(darkMode ? sf::Color::White : sf::Color::Black);
        l.setPosition(p.x + indicatorWidth * j + indicatorSpacing + indicatorWidth / 2 - 20, s.height - indicatorHeight / 2 -20);
        window->draw(l);
    }
}

void Table::drawOutline(sf::RenderWindow *window, sizeType s, positionType p){

    RectangleShape fill(Vector2f(s.width - 2*borderWidth, s.height - 2*borderWidth));
    fill.setOutlineThickness((float)borderWidth);
    fill.setOutlineColor(darkMode ? Color(50, 50, 50) : Color(120, 120, 120));
    fill.setPosition(p.x + borderWidth, p.y + borderWidth);
    window->draw(fill);

}

void Table::drawGrid(sf::RenderWindow *window, sizeType s, positionType p){

    double squareWidth = (s.width) / 8;
    double squareHeight = (s.height) / 8;

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){
            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(p.x +squareWidth*i, p.y + squareHeight*j);

            if((i+j)%2!=0) square.setFillColor(darkMode ? Color(50, 50, 50) : Color(120, 120, 120));
            else square.setFillColor(darkMode ? Color(150, 150, 150) : Color::White);

            pair<int, int> current_pos = {i, j};
            if(selectedSquare==current_pos){
                square.setOutlineColor(Color::Red);
                square.setSize(Vector2f(squareWidth-4, squareHeight-4));
                square.setOutlineThickness(4);
            }
            if(find(futurePositions.begin(), futurePositions.end(), current_pos)!=futurePositions.end()){
                square.setOutlineColor(darkMode ? Color::White : Color::Black);
                square.setSize(Vector2f(squareWidth-4, squareHeight-4));
                square.setOutlineThickness(4);
            }
            window->draw(square);
        }
}

pair<int, int> Table::determineGridPosition(positionType pos){

    pair<int, int> r(0,0);

    sizeType s(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing);
    positionType p(position.x + indicatorSpacing + padding, position.y + padding);

    if(pos.x>=p.x && pos.x<=p.x+s.width && pos.y>=p.y && pos.y <= p.y + s.height){
        r.first = (int) (pos.x - p.x) / (s.width/8);
        r.second = (int) (pos.y - p.y) / (s.height/8);
    }else{
        throw EXIT_FAILURE;
    }

    return r;

}

void Table::resetFuturePositions(){
    this->futurePositions.clear();
}

void Table::resetSelectedSquare(){
    this->selectedSquare = {-1,-1};
}

void Table::updateSelectedSquare(pair<int, int> new_position){
    if(!(new_position.first>=0 && new_position.first<8 && new_position.second>=0 && new_position.second<8)) return;
    this->selectedSquare = new_position;
    Piece* current = rules[new_position];
    if(find(futurePositions.begin(), futurePositions.end(), new_position)!=futurePositions.end()){
        rules.movePiece(lastSelectedPiece, new_position);
        resetFuturePositions();
        resetSelectedSquare();

        if(rules.isCheckMate(!lastSelectedPiece->getPlayer())){
            winnerPlayer = lastSelectedPiece->getPlayer();
            resetSelectedSquare();
            resetFuturePositions();
            checkMate = true;
        }

        return;
    }
    resetFuturePositions();
    if(current != nullptr){
        lastSelectedPiece = current;
        try{
            vector<pair<int, int>> futurePositions = rules.getFuturePositions(current);
            this->futurePositions = futurePositions;
        }catch (int e){
            cout<<"An error occurred trying to find future positions!";
        }
    }
}

void Table::digestAction(sf::Event event){
    if(event.type==sf::Event::MouseButtonPressed){
        try{
            if(!checkMate){
                pair<int, int> grid_position = this->determineGridPosition(positionType(event.mouseButton.x, event.mouseButton.y));
                if(grid_position==selectedSquare){
                    resetFuturePositions();
                    return resetSelectedSquare();
                }
                updateSelectedSquare(grid_position);
            }
        }catch (int e){
            cout<<"Pressed outside the table"<<'\n';
        }
    }else if(event.type==sf::Event::KeyPressed){
        if(selectedSquare.first==-1 || selectedSquare.second==-1){
            if(rules.getCurrentPlayer()==1) selectedSquare = {3,1};
            else selectedSquare = {3,6};
        }
        if(event.key.code==Keyboard::Right)
            updateSelectedSquare({selectedSquare.first+1, selectedSquare.second});
        else if(event.key.code==Keyboard::Left)
            updateSelectedSquare({selectedSquare.first-1, selectedSquare.second});
        else if(event.key.code==Keyboard::Up)
            updateSelectedSquare({selectedSquare.first, selectedSquare.second-1});
        else if(event.key.code==Keyboard::Down)
            updateSelectedSquare({selectedSquare.first, selectedSquare.second+1});
    }
    if(rules.getCurrentPlayer()==1 && playAgainstAi){
        Move m = brain->determineBestMove();
        if(m.piece!=nullptr && m.piece->isInTable())
            rules.movePiece(m.piece, m.to);
    }
}

void Table::drawPiece(sf::RenderWindow* window, Piece* piece){

    if(!piece->getIsVisible()) return;

    sizeType s(this->size.width - this->borderWidth - this->indicatorSpacing, this->size.height - this->borderWidth - this->indicatorSpacing);
    positionType p(this->position.x + this->indicatorSpacing + piece->getPos().first * (s.width/8), this->position.y + piece->getPos().second * (s.height/8));

    sf::Texture piece_img;

    if (!piece_img.loadFromFile(piece->getImage())) throw EXIT_FAILURE;

    sf::Sprite item;
    item.setTexture(piece_img);
    item.setPosition(Vector2f(p.x, p.y));
    item.setScale(0.3, .3);
    item.setOrigin(-110, -50);

    window->draw(item);
}

void Table::resetGame() {
    checkMate = false;
    rules.resetGame();
    resetSelectedSquare();
    resetFuturePositions();
}

void Table::undoMove() {
    checkMate = false;
    if(playAgainstAi && rules.getCurrentPlayer()==0)
        rules.undoMove();
    rules.undoMove();
    resetSelectedSquare();
    resetFuturePositions();
}

void Table::togglePlayAgainstAi(){
    playAgainstAi = !playAgainstAi;
}

bool Table::isPlayingAgainstAi() const{
    return playAgainstAi;
}

bool Table::getIsCheckMate() {
    return checkMate;
}

int Table::getWinnerPlayer() {
    return winnerPlayer;
}

