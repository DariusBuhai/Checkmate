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

    /// Create the window of the application
    RenderWindow window(VideoMode(this->screen_width, this->screen_height, 32), "Checkmate AI",Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    /// Draw contents
    table.draw(&window, encapsulation(screen_width, screen_height));

    /// Display
    window.display();

    while(window.isOpen()){
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
    }
}
