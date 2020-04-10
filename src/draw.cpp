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
    RenderWindow window(VideoMode((unsigned int)screenWidth, (unsigned int)screenHeight, 32), "Checkmate AI",Style::Titlebar | Style::Close);
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

bool Draw::mouseInsideLimits(sf::Event event, std::pair<int, int> x, std::pair<int,int> y){
    return mouseInsideLimits({event.mouseButton.x,event.mouseButton.y}, x, y);
}

void Draw::digestAction(sf::RenderWindow* window, sf::Event event){
    table.digestAction(event);

    if(event.type==sf::Event::MouseButtonPressed){
        if(mouseInsideLimits(event, {80, 320}, {120, 50}))
            table.resetGame();
        if(mouseInsideLimits(event, {400, 620}, {120, 50}))
            table.undoMove();
        if(mouseInsideLimits(event, {700, 920}, {120, 50}))
            table.togglePlayAgainstAi();
        if(mouseInsideLimits(event, {screenWidth - 130, screenWidth-20}, {screenHeight-200, screenHeight-300}))
            darkMode = !darkMode;
    }
    if(event.type==sf::Event::MouseMoved){
        sf::Cursor cursor;
        hoveringResetButton = false;
        hoveringPreviousMoveButton = false;
        hoveringPlayAiButton = false;
        hoveringDarkModeButton = false;
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {100, 320}, {120, 50})){
            cursor.loadFromSystem(sf::Cursor::Hand);
            hoveringResetButton = true;
        }
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {400, 620}, {120, 50})){
            cursor.loadFromSystem(sf::Cursor::Hand);
            hoveringPreviousMoveButton = true;
        }
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {700, 920}, {120, 50})){
            cursor.loadFromSystem(sf::Cursor::Hand);
            hoveringPlayAiButton = true;
        }
        if(mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, {screenWidth - 130, screenWidth-20}, {screenHeight-200, screenHeight-300})){
            cursor.loadFromSystem(sf::Cursor::Hand);
            hoveringDarkModeButton = true;
        }
        window->setMouseCursor(cursor);
    }
}

void Draw::drawButton(sf::RenderWindow* window, string title, sf::Color color, std::pair<int, int> position){
    sf::Text button = sf::Text();
    button.setString(title);
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) throw EXIT_FAILURE;
    button.setFont(font);
    button.setCharacterSize(40);
    button.setFillColor(color);
    button.setPosition(position.first, position.second);
    window->draw(button);
}

void Draw::draw(sf::RenderWindow* window) {

    table.setSize(size_type(screenWidth-150, screenHeight-150));
    table.setPosition(position_type(0, 25));
    table.setDarkMode(darkMode);

    RectangleShape fill = RectangleShape(Vector2f(screenWidth, screenHeight));
    fill.setFillColor(darkMode ? Color::Black : Color::White);
    window->draw(fill);

    drawButton(window, "Reset Game", hoveringResetButton ? sf::Color::Blue : (darkMode ? Color::White : Color::Black), {100,screenHeight-120});
    drawButton(window, "Undo Move", hoveringPreviousMoveButton ? sf::Color::Blue : (darkMode ? Color::White : Color::Black), {400,screenHeight-120});

    string aiButtonText = table.isPlayingAgainstAi() ? "Play with friend" : "Play against AI";
    drawButton(window, aiButtonText, hoveringPlayAiButton ? sf::Color::Blue : (darkMode ? Color::White : Color::Black), {700,screenHeight-120});

    if(table.isPlayingAgainstAi()) drawButton(window, "AI", sf::Color::Magenta, {screenWidth - 100,100});

    drawButton(window, "Dark\nMode", hoveringDarkModeButton ? sf::Color::Blue : (darkMode ? Color::White : Color::Black), {screenWidth - 130,200});

    table.draw(window);

}

