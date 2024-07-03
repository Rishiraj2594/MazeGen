#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "lib/maze.h"

#include <iostream> // Remove it after debugging

const int BLOCK_SIZE = 50;
const int BLOCK_COUNT_X = 10;
const int BLOCK_COUNT_Y = 10;
const float WALL_THICKNESS = BLOCK_SIZE*0.2;

const int SCREEN_WIDTH = (BLOCK_COUNT_X-1)*WALL_THICKNESS + BLOCK_COUNT_X*BLOCK_SIZE;
const int SCREEN_HEIGHT = (BLOCK_COUNT_Y-1)*WALL_THICKNESS + BLOCK_COUNT_Y*BLOCK_SIZE;

const std::string TITLE = "MAZE"; 

using namespace sf;

int main()
{
    Maze maze(BLOCK_COUNT_X, BLOCK_COUNT_Y);   

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE, Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);    // VSync

    int temp_wall_value;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        for (int y=0; y<BLOCK_COUNT_Y; y++) {
            for (int x=0; x<BLOCK_COUNT_X; x++) {
                temp_wall_value = maze.value_at(x, y);
                if (temp_wall_value & 1) {
                    window.draw([x, y] {
                        RectangleShape line(Vector2f(WALL_THICKNESS, BLOCK_SIZE+(WALL_THICKNESS)));
                        line.setFillColor(Color::Black);
                        line.setPosition(Vector2f((x+1)*(BLOCK_SIZE)+(x)*(WALL_THICKNESS), y*(BLOCK_SIZE+WALL_THICKNESS)));
                        return line;
                    }());
                }
                if ((temp_wall_value & 2) == 2) {
                    window.draw([x, y] {
                        RectangleShape line(Vector2f(BLOCK_SIZE+(WALL_THICKNESS), WALL_THICKNESS));
                        line.setFillColor(Color::Black);
                        line.setPosition(Vector2f((x)*(BLOCK_SIZE+WALL_THICKNESS), (y+1)*(BLOCK_SIZE)+(y)*(WALL_THICKNESS)));
                        return line;
                    }());
                }
            }
            }
        window.display();
        }

    return 0;
}