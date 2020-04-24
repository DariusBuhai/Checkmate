#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>
#include <iostream>

#include "../include/piece.h"
#include "../include/draw.h"
#include "../include/utils.h"

using namespace std;
using namespace sf;

Draw::Draw() {
    this->initComponents();
    this->init();
}

void Draw::initComponents() {
    table.setSize(SizeType(screenWidth - 150, screenHeight - 150));
    table.setPosition({0, 25});
    table.setDarkMode(&this->darkMode);

    buttons.setDarkMode(&this->darkMode);

    buttons += new Button({screenWidth - 130, screenWidth - 20}, {screenHeight - 200, screenHeight - 300},&this->darkMode, "Dark\nMode", "Light\nMode");
    buttons += new Button({screenWidth - 130, screenWidth - 20}, {350, 250}, &this->viewCredits, "Show\nCredits","Hide\nCredits");

    buttons += new Button({100, 320}, {120, 50}, &this->resetGameGulp, "Reset Game");
    buttons += new Button({400, 620}, {120, 50}, &this->undoMoveGulp, "Undo Move");
    buttons += new Button({700, 920}, {120, 50}, &this->playAgainstAi, "Play against AI", "Play with friend");
}

void Draw::init(){
    /** Create the window of the application */
    RenderWindow window(VideoMode((unsigned int)screenWidth, (unsigned int)screenHeight, 32), "AI Chess",Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    while(window.isOpen()){
        Event event;
        window.clear();
        this->draw(&window);
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
            digestAction(&window, event);
        }
        window.display();
    }
}

void Draw::digestAction(RenderWindow* window, Event event){

    Cursor cursor;
    cursor.loadFromSystem(Cursor::Arrow);
    window->setMouseCursor(cursor);

    table.digestAction(event);
    buttons.digestAction(event, window);

    if(undoMoveGulp){
        undoMoveGulp = false;
        table.undoMove();
    }
    if(resetGameGulp){
        resetGameGulp = false;
        table.resetGame();
    }
    if(table.isPlayingAgainstAi() != playAgainstAi)
        table.togglePlayAgainstAi();
}

void Draw::draw(RenderWindow* window) {

    RectangleShape fill = RectangleShape(Vector2f(screenWidth, screenHeight));
    fill.setFillColor(darkMode ? Color::Black : Color::White);
    window->draw(fill);

    if(viewCredits){
        Utils::drawText(window, "Credits:", (darkMode ? Color::White : Color::Black), {100, 50}, 50);
        Utils::drawText(window, "- Buhai Darius", (darkMode ? Color::White : Color::Black), {100, 130});
        Utils::drawText(window, "- Vlad Cioraca", (darkMode ? Color::White : Color::Black), {100, 200});
        Utils::drawText(window, "- Johnny", (darkMode ? Color::White : Color::Black), {100, 270});
    }else{
        table.draw(window);

        if(table.isPlayingAgainstAi()){
            Utils::drawText(window, "AI", Color::Magenta, {screenWidth - 100,50});
            Utils::drawText(window, "Active", Color::Magenta, {screenWidth - 130,100});
        }

        if(table.getIsCheckMate()){
            Utils::drawText(window, "Checkmate!", Color::Red, {(screenWidth-150)/2-220,360}, 100);
            Utils::drawText(window, "Player", Color::Blue, {screenWidth - 130,360});
            Utils::drawText(window, ""+string(1, '1'+table.getWinnerPlayer()), Color::Blue, {screenWidth - 90,400});
            Utils::drawText(window, "Wins", Color::Blue, {screenWidth - 120,440});
        }
    }
    buttons.draw(window);
}

