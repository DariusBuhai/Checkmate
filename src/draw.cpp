#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../include/piece.h"
#include "../include/draw.h"
#include "../include/types.h"

using namespace std;
using namespace sf;

Draw::Draw() {
    this->init();
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

bool Draw::mouseInsideLimits(pair<int, int> location, std::pair<int, int> x, std::pair<int,int> y){
    y.first = screenHeight-y.first;
    y.second = screenHeight-y.second;
    return (location.first > x.first && location.first < x.second) &&
           (location.second > y.first && location.second < y.second);
}

bool Draw::mouseInsideLimits(Event event, std::pair<int, int> x, std::pair<int,int> y){
    return mouseInsideLimits({event.mouseButton.x,event.mouseButton.y}, x, y);
}

void Draw::digestAction(RenderWindow* window, Event event){
    table.digestAction(event);

    if(event.type==Event::MouseButtonPressed){
        if(mouseInsideLimits(event, {80, 320}, {120, 50}))
            table.resetGame();
        if(mouseInsideLimits(event, {400, 620}, {120, 50}))
            table.undoMove();
        if(mouseInsideLimits(event, {700, 920}, {120, 50}))
            table.togglePlayAgainstAi();
        if(mouseInsideLimits(event, {screenWidth - 130, screenWidth-20}, {screenHeight-200, screenHeight-300}))
            darkMode = !darkMode;
    }
    if(event.type==Event::MouseMoved){
        Cursor cursor;
        cursor.loadFromSystem(Cursor::Arrow);
        hoveringResetButton = false;
        hoveringPreviousMoveButton = false;
        hoveringPlayAiButton = false;
        hoveringDarkModeButton = false;

        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {100, 320}, {120, 50})){
            cursor.loadFromSystem(Cursor::Hand);
            hoveringResetButton = true;
        }
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {400, 620}, {120, 50})){
            cursor.loadFromSystem(Cursor::Hand);
            hoveringPreviousMoveButton = true;
        }
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {700, 920}, {120, 50})){
            cursor.loadFromSystem(Cursor::Hand);
            hoveringPlayAiButton = true;
        }
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {screenWidth - 130, screenWidth-20}, {screenHeight-200, screenHeight-300})){
            cursor.loadFromSystem(Cursor::Hand);
            hoveringDarkModeButton = true;
        }
        /*if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {screenWidth - 130, screenWidth-20}, {350, 250})){
            cursor.loadFromSystem(Cursor::Hand);
        }*/
        window->setMouseCursor(cursor);

    }
}

void Draw::drawText(RenderWindow* window, string title, Color color, std::pair<int, int> position, int size){
    Text text = Text();
    text.setString(title);
    Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position.first, position.second);
    window->draw(text);
}

void Draw::draw(RenderWindow* window) {

    table.setSize(SizeType(screenWidth-150, screenHeight-150));
    table.setPosition({0, 25});
    table.setDarkMode(darkMode);

    RectangleShape fill = RectangleShape(Vector2f(screenWidth, screenHeight));
    fill.setFillColor(darkMode ? Color::Black : Color::White);
    window->draw(fill);

    table.draw(window);

    drawText(window, "Reset Game", hoveringResetButton ? Color::Blue : (darkMode ? Color::White : Color::Black), {100,screenHeight-120});
    drawText(window, "Undo Move", hoveringPreviousMoveButton ? Color::Blue : (darkMode ? Color::White : Color::Black), {400,screenHeight-120});

    string aiButtonText = table.isPlayingAgainstAi() ? "Play with friend" : "Play against AI";
    drawText(window, aiButtonText, hoveringPlayAiButton ? Color::Blue : (darkMode ? Color::White : Color::Black), {700,screenHeight-120});

    if(table.isPlayingAgainstAi()){
        drawText(window, "AI", Color::Magenta, {screenWidth - 100,50});
        drawText(window, "Active", Color::Magenta, {screenWidth - 130,100});
    }

    drawText(window, "Dark\nMode", hoveringDarkModeButton ? Color::Blue : (darkMode ? Color::White : Color::Black), {screenWidth - 130,200});

    //drawText(window, "Button", hoveringButton ? Color::Magenta : (!darkMode ? Color::White : Color::Black), {screenWidth - 130,screenHeight-350});

    if(table.getIsCheckMate()){
        drawText(window, "Checkmate!", Color::Red, {(screenWidth-150)/2-220,360}, 100);
        drawText(window, "Player", Color::Blue, {screenWidth - 130,360});
        drawText(window, ""+string(1, '1'+table.getWinnerPlayer()), Color::Blue, {screenWidth - 90,400});
        drawText(window, "Wins", Color::Blue, {screenWidth - 120,440});
    }


}

