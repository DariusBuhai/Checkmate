#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../include/draw.h"
#include "../include/table.h"
#include "../include/types.h"

using namespace std;
using namespace sf;

void Draw::draw() {

    /// Initialize items
    Table table;
    table.setSize(size_type(screen_width-50, screen_height-50));
    table.setPosition(position_type(25, 25));

    /// Create the window of the application
    RenderWindow window(VideoMode(this->screen_width, this->screen_height, 32), "Checkmate AI",Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    /// Draw contents
    window.draw(RectangleShape(Vector2f(screen_width, screen_height)));

    table.draw(&window);

    /// Display
    window.display();

    while(window.isOpen()){
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
    }
}
