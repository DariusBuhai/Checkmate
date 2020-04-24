//
// Created by Darius Buhai on 3/26/20.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "../include/piece.h"
#include "../include/table.h"

using namespace std;
using namespace sf;

Table::Table(){
    brain = new Brain(&rules);
}

Table::~Table(){};

/** Setters */
void Table::setSize(SizeType s) {
    this->size = s;
}

void Table::setPosition(std::pair<int,int> p) {
    this->position = p;
}

void Table::setDarkMode(bool* _darkMode){
    darkMode = _darkMode;
}

void Table::togglePlayAgainstAi(){
    playAgainstAi = !playAgainstAi;
}

bool Table::isPlayingAgainstAi() const{
    return playAgainstAi;
}

bool Table::getIsCheckMate() const {
    return checkMate;
}

int Table::getWinnerPlayer() const {
    return winnerPlayer;
}

/** Content generators */
void Table::draw(RenderWindow *window) {
    drawIndicators(window, size, position);
    drawOutline(window, SizeType(size.width-indicatorSpacing, size.height-indicatorSpacing), {position.first+indicatorSpacing, position.second});
    drawGrid(window, SizeType(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing), std::pair<int,int>(position.first + indicatorSpacing + padding, position.second + padding));

    bool containsSelectedPiece = false;
    for(auto piece : rules.getPieces())
        if(piece!=selectedPiece) drawPiece(window, piece);
        else containsSelectedPiece = true;

    /** Draw the selected piece at the end, to be above */
    if(selectedPiece!= nullptr && containsSelectedPiece)
        drawPiece(window, selectedPiece);
}

void Table::drawIndicators(RenderWindow *window, SizeType s, std::pair<int,int> p) const{

    double indicatorHeight = (s.height-indicatorSpacing) / 8;
    double indicatorWidth = (s.width-indicatorSpacing) / 8;

    for(int i=0;i<8;i++){
        Text l;
        Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
        l.setString(string(1, '1'+(7-i)));
        l.setFont(font);
        l.setCharacterSize(40);
        l.setFillColor(*darkMode ? Color::White : Color::Black);
        l.setPosition(p.first + indicatorSpacing / 2 + 20, p.second +indicatorHeight*i + indicatorHeight/2 - 20);
        window->draw(l);
    }
    for(int j=0;j<8;j++){
        Text l;
        Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
        l.setString(string(1, 'A'+j));
        l.setFont(font);
        l.setCharacterSize(40);
        l.setFillColor(*darkMode ? Color::White : Color::Black);
        l.setPosition(p.first + indicatorWidth * j + indicatorSpacing + indicatorWidth / 2 - 20, s.height - indicatorHeight / 2 -20);
        window->draw(l);
    }
}

void Table::drawOutline(RenderWindow *window, SizeType s, std::pair<int,int> p) const{
    RectangleShape fill(Vector2f(s.width - 2*borderWidth, s.height - 2*borderWidth));
    fill.setOutlineThickness((float)borderWidth);
    fill.setOutlineColor(*darkMode ? Color(50, 50, 50) : Color(120, 120, 120));
    fill.setPosition(p.first + borderWidth, p.second + borderWidth);
    window->draw(fill);
}

void Table::drawGrid(RenderWindow *window, SizeType s, std::pair<int,int> p){
    double squareWidth = (s.width) / 8;
    double squareHeight = (s.height) / 8;

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){
            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(p.first +squareWidth*i, p.second + squareHeight*j);

            if((i+j)%2!=0) square.setFillColor(*darkMode ? Color(50, 50, 50) : Color(120, 120, 120));
            else square.setFillColor(*darkMode ? Color(150, 150, 150) : Color::White);

            pair<int, int> current_pos = {i, j};
            if(selectedSquare==current_pos){
                square.setOutlineColor(Color::Red);
                square.setSize(Vector2f(squareWidth-4, squareHeight-4));
                square.setOutlineThickness(4);
            }
            if(find(futurePositions.begin(), futurePositions.end(), current_pos)!=futurePositions.end()){
                square.setOutlineColor(*darkMode ? Color::White : Color::Black);
                square.setSize(Vector2f(squareWidth-4, squareHeight-4));
                square.setOutlineThickness(4);
            }
            window->draw(square);
        }
}

bool Table::isInsideTable(std::pair<int,int> pos) const{
    SizeType s(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing);
    std::pair<int,int> p(position.first + indicatorSpacing + padding, position.second + padding);
    return pos.first>=p.first && pos.first<=p.first+s.width && pos.second>=p.second && pos.second <= p.second + s.height;
}

pair<int, int> Table::determineGridPosition(std::pair<int,int> pos) const{
    pair<int, int> r(0,0);

    SizeType s(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing);
    std::pair<int,int> p(position.first + indicatorSpacing + padding, position.second + padding);

    if(isInsideTable(pos)){
        r.first = (int) (pos.first - p.first) / (s.width/8);
        r.second = (int) (pos.second - p.second) / (s.height/8);
    }else{
        throw EXIT_FAILURE;
    }

    return r;
}

void Table::drawPiece(RenderWindow* window, Piece* piece) const{

    SizeType s(this->size.width - this->borderWidth - this->indicatorSpacing, this->size.height - this->borderWidth - this->indicatorSpacing);
    std::pair<int,int> p = std::pair<int,int>(this->position.first + this->indicatorSpacing + piece->getPos().first * (s.width/8), this->position.second + piece->getPos().second * (s.height/8));

    /** If the piece is selected with the mouse */
    if(piece==selectedPiece && selectedPieceCurrentLocation.first!=-1 && selectedPieceCurrentLocation.second!=-1)
        p = std::pair<int,int>(selectedPieceCurrentLocation.first - 50, selectedPieceCurrentLocation.second - 40);

    Texture piece_img;

    if (!piece_img.loadFromFile(piece->getImage())) throw EXIT_FAILURE;

    Sprite item;
    item.setTexture(piece_img);
    item.setPosition(Vector2f(p.first, p.second));
    item.setScale(0.3, .3);
    item.setOrigin(-110, -50);

    window->draw(item);
}

/** Action digesters */
void Table::resetFuturePositions(){
    this->futurePositions.clear();
}

void Table::resetSelectedSquare(){
    this->selectedSquare = {-1,-1};
}

void Table::resetSelectedPieceLocation(){
    this->selectedPieceCurrentLocation = {-1, -1};
}

void Table::updateSelectedSquare(pair<int, int> new_position){
    if(!(new_position.first>=0 && new_position.first<8 && new_position.second>=0 && new_position.second<8)) return;
    this->selectedSquare = new_position;
    Piece* current = rules[new_position];
    if(find(futurePositions.begin(), futurePositions.end(), new_position)!=futurePositions.end()){
        rules.movePiece(selectedPiece, new_position);
        resetFuturePositions();
        resetSelectedSquare();

        if(rules.isCheckMate(!selectedPiece->getPlayer())){
            winnerPlayer = selectedPiece->getPlayer();
            resetSelectedSquare();
            resetFuturePositions();
            checkMate = true;
        }
        return;
    }
    resetFuturePositions();
    selectedPiece = current;
    if(current != nullptr){
        try{
            vector<pair<int, int>> futurePositions = rules.getFuturePositions(current);
            this->futurePositions = futurePositions;
        }catch (int e){
            cout<<"An error occurred trying to find future positions!";
        }
    }
}

void Table::digestAction(Event event){
    if(event.type==Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left){
        gameClock.restart();
        this->resetSelectedPieceLocation();
        try{
            if(!checkMate){
                pair<int, int> grid_position = this->determineGridPosition(std::pair<int,int>(event.mouseButton.x, event.mouseButton.y));
                if(grid_position==selectedSquare){
                    resetFuturePositions();
                    return resetSelectedSquare();
                }
                updateSelectedSquare(grid_position);
            }
        }catch (int e){
            cout<<"Pressed outside the table"<<'\n';
        }
        mouseButtonPressing = true;
    }
    if(event.type==Event::MouseButtonReleased){
        try{
            pair<int, int> grid_position = this->determineGridPosition(std::pair<int,int>(selectedPieceCurrentLocation.first, selectedPieceCurrentLocation.second));
            updateSelectedSquare(grid_position);
        } catch (int e) {
            cout<<"Moved piece outside the table"<<'\n';
        }
        mouseButtonPressing = false;
        resetSelectedPieceLocation();
    }
    if(event.type==Event::MouseMoved && mouseButtonPressing){
        if(selectedPiece != nullptr && selectedPiece->getPlayer()==rules.getCurrentPlayer() && gameClock.getElapsedTime().asMilliseconds()>=100 && isInsideTable({event.mouseMove.x, event.mouseMove.y}))
            selectedPieceCurrentLocation = {event.mouseMove.x, event.mouseMove.y};
    }
    if(event.type==Event::KeyPressed){
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

/** Button actions */
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

