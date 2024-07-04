#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "lib/maze.h"
#include "lib/maze_generation.h"
#include <iostream> // Remove it after debugging

const int BLOCK_SIZE = 50;
const int BLOCK_COUNT_X = 10;
const int BLOCK_COUNT_Y = 10;
const int WALL_THICKNESS = BLOCK_SIZE*0.04;

const int SCREEN_WIDTH = (BLOCK_COUNT_X-1)*WALL_THICKNESS + BLOCK_COUNT_X*BLOCK_SIZE;
const int SCREEN_HEIGHT = (BLOCK_COUNT_Y-1)*WALL_THICKNESS + BLOCK_COUNT_Y*BLOCK_SIZE;

const std::string TITLE = "MAZE"; 

using namespace sf;

int main()
{
    Maze maze(BLOCK_COUNT_X, BLOCK_COUNT_Y);   

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE, Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);    // VSync
    MazeGeneration g_maze(maze,BLOCK_COUNT_X,BLOCK_COUNT_Y);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        // window.clear(Color::White);
        g_maze.dfs_genrate_maze(window,WALL_THICKNESS, BLOCK_SIZE);
        // window.display();
        }

    return 0;
}