#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "../include/piece.h"
#include "../include/draw.h"
#include "../include/materials.h"
#include "../include/utils.h"
using namespace std;
using namespace sf;

#include "table.cpp"

Draw::Draw() {
    this->initComponents();
    this->init();
}

Draw::~Draw() {
    /** Receiving malloc */
    buttons.~Container();
    labels.~Container();
    table.~Table();
    cout<<"Success";
}

void Draw::initComponents() {
    table.setSize(SizeType(screenWidth - 150, screenHeight - 150));
    table.setPosition({0, 25});
    table.setDarkMode(&this->darkMode);

    buttons.setDarkMode(&this->darkMode);

    buttons += new Button({screenWidth - 130, screenWidth - 20}, {screenHeight - 200, screenHeight - 300},&this->darkMode, "Dark\nMode", "Light\nMode");
    buttons += new Button({screenWidth - 140, screenWidth - 10}, {350, 250}, &this->viewCredits, "Show\nCredits","Hide\nCredits");

    buttons += {"chess", new Button({100, 320}, {120, 60}, &this->resetGameGulp, "Reset Game")};
    buttons += {"chess", new Button({400, 620}, {120, 60}, &this->undoMoveGulp, "Undo Move")};
    buttons += {"chess", new Button({700, 980}, {120, 60}, &this->playAgainstAi, "Play against AI", "Play with friend")};

    labels.setDarkMode(&this->darkMode);

    labels += {"ai", new Label({screenWidth - 100,50}, "AI", 40, Color::Magenta, Color::Magenta)};
    labels += {"ai", new Label({screenWidth - 130,100}, "Active", 40, Color::Magenta, Color::Magenta)};

    labels += {"checkmate", new Label({(screenWidth-150)/2-220,360}, "Checkmate", 100, Color::Red, Color::Red)};
    labels += {"checkmate", new Label({screenWidth - 130,360}, "Player", 40, Color::Blue, Color::Blue)};
    labels += {"checkmate", new Label({screenWidth - 90,400}, "x", 40, Color::Blue, Color::Blue)};
    labels += {"checkmate", new Label({screenWidth - 120,440}, "Wins", 40, Color::Blue, Color::Blue)};

    labels += {"credits", new Label({100, 50}, "Credits:", 50)};
    labels += {"credits", new Label({100, 130}, "- Buhai Darius")};
    labels += {"credits", new Label({100, 200}, "- Vlad Ciorica")};
    labels += {"credits", new Label({100, 270}, "- Johnny")};
    labels += {"credits", new Label({100, screenHeight-120}, "@ All rights reserved", 30)};
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
        labels.draw(window, "credits");
        buttons.draw(window, "credits");
    }else{
        table.draw(window);

        if(table.isPlayingAgainstAi())
            labels.draw(window, "ai");

        if(table.getIsCheckMate()){
            *labels["checkmate"][2] = ""+string(1, '1'+table.getWinnerPlayer());
            labels.draw(window, "checkmate");
        }
        buttons.draw(window, "chess");
    }
}

