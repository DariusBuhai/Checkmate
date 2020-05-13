#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <utility>
#include <string>

#include "../include/piece.h"
#include "../include/draw.h"

#if defined(_WIN32)
    #include "table.cpp"
#endif // defined

using namespace std;
using namespace sf;

Draw* Draw::instance_ = nullptr;

Draw::Draw()
{
    this->initComponents();
}

void Draw::startGame()
{
    this->init();
}

Draw* Draw::getInstance()
{
    if(instance_ == nullptr)
        instance_ = new Draw;
    return instance_;
}

ostream& operator<<(ostream& out, const Draw& ob)
{
    out<<"Tabla a fost initializata cu dimensiunile: " << ob.screenHeight << " " << ob.screenWidth << '\n';
    if(!ob.darkMode)
        out<<"Dark mode-ul nu este activat\n";
    else
        out<<"Dark mode-ul este activat\n";
    return out;
}

void Draw::initComponents()
{
    table.setSize(SizeType(screenWidth - 160, screenHeight - 160));
    table.setPosition({0, 25});
    table.setDarkMode(&this->darkMode);
    table.setCursorHand(&this->cursorHand);
    table.initComponents();

    buttons.setDarkMode((&this->darkMode));

    buttons += new Button({screenWidth - 137, screenWidth - 20}, {screenHeight - 50, screenHeight - 195},&this->showBestMove, &this->cursorHand, "Show\nBest\nMove");
    buttons += new Button({screenWidth - 137, screenWidth - 20}, {screenHeight - 230, screenHeight - 330},&this->darkMode, &this->cursorHand, "Dark\nMode", "Light\nMode");
    buttons += new Button({screenWidth - 145, screenWidth - 15}, {350, 250}, &this->viewCredits,&this->cursorHand, "Show\nCredits","Close\nCredits");

    buttons += {"ai", new Button({screenWidth - 145, screenWidth - 15}, {500, 400}, &this->playAgainstStockFish,&this->cursorHand, "Stock\nFish","Brain")};

    buttons += {"chess", new Button({100, 320}, {100, 40}, &this->resetGameGulp,&this->cursorHand, "Reset Game")};
    buttons += {"chess", new Button({400, 620}, {100, 40}, &this->undoMoveGulp,&this->cursorHand, "Undo Move")};
    buttons += {"chess", new Button({700, 1050}, {100, 40}, &this->playAgainstAi,&this->cursorHand, "Play with computer", "Play against friend")};

    labels.setDarkMode(&this->darkMode);

    images += {"ai", new ImageLabel({screenWidth - 135,50}, "resources/images/brain.png", {.12,.12})};

    labels += {"checkmate", new Label({(screenWidth-150)/2-220,360}, "Checkmate", 100, Color::Red, Color::Red)};
    labels += {"checkmate", new Label({screenWidth - 130,360}, "Player", 40, Color::Blue, Color::Blue)};
    labels += {"checkmate", new Label({screenWidth - 90,400}, "x", 40, Color::Blue, Color::Blue)};
    labels += {"checkmate", new Label({screenWidth - 120,440}, "Wins", 40, Color::Blue, Color::Blue)};

    labels += {"credits", new Label({screenWidth/2-100, 50}, "Credits", 70)};
    labels += {"credits", new Label({100, 160}, "Buhai Darius")};
    images += {"credits", new ImageLabel({100, 230}, "resources/images/darius.jpeg", {.52,.52})};
    labels += {"credits", new Label({100, 530}, "Vlad Ciorica")};
    images += {"credits", new ImageLabel({100, 600}, "resources/images/vlad.jpeg", {1.2,1.2})};
    labels += {"credits", new Label({550, 300}, "Johnny")};
    images += {"credits", new ImageLabel({550, 370}, "resources/images/johnny.jpeg", {1.2,1.2})};
    labels += {"credits", new Label({100, screenHeight-120}, "@ All rights reserved", 30)};
}

void Draw::init()
{
    /** Create the window of the application */
    RenderWindow window(VideoMode((unsigned int)screenWidth, (unsigned int)screenHeight, 32), "AI Chess",Style::Titlebar | Style::Close);

    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    while(window.isOpen()){
        Event event{};
        window.clear();
        while (window.pollEvent(event)){
            this->digestAction(&window, event);
            if (event.type == Event::Closed)
                window.close();
        }
        this->draw(&window);
        window.display();
    }

}

void Draw::digestAction(RenderWindow* window, Event event){
    cursorHand = false;

    if(viewCredits){
        buttons.digestAction(event, window, "credits");
        table.toggleTimers(true);
    }
    else{
        buttons.digestAction(event, window);
        table.digestAction(event, window);
    }

    if(undoMoveGulp){
        undoMoveGulp = false;
        table.undoMove();
    }
    if(resetGameGulp){
        resetGameGulp = false;
        table.resetGame();
    }

    if(table.isPlayingAgainstStockfish() != playAgainstStockFish)
        table.togglePlayAgainstStockfish();

    if(table.isPlayingAgainstAi() != playAgainstAi)
        table.togglePlayAgainstAi();

    if(table.isShowingBestMove() != showBestMove)
        table.toggleShowBestMove();

    /** Load determined cursor */
    Cursor cursor;
    cursor.loadFromSystem(cursorHand ? Cursor::Hand : Cursor::Arrow);
    window->setMouseCursor(cursor);
}

void Draw::draw(RenderWindow* window)
{

    RectangleShape fill = RectangleShape(Vector2f(screenWidth, screenHeight));
    fill.setFillColor(darkMode ? Color(46,47,49) : Color(236,236,236));
    window->draw(fill);

    if(viewCredits){
        labels.draw(window, "credits");
        images.draw(window, "credits");
        buttons.draw(window, "credits");
    }
    else{
        table.draw(window);

        if(table.isPlayingAgainstAi()){
            images.draw(window, "ai");
            buttons.draw(window,"ai");
        }

        if(table.getIsCheckMate()){
            *labels["checkmate"][2] = ""+string(1, '1'+table.getWinnerPlayer());
            labels.draw(window, "checkmate");
        }
        buttons.draw(window, "chess");
    }
}

