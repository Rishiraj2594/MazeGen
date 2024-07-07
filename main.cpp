#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "lib/maze.h"
#include "lib/maze_generation.h"
#include "lib/a_star.h"
#include <iostream> // Remove it after debugging

const int BLOCK_SIZE = 20;
const int BLOCK_COUNT_X = 20;
const int BLOCK_COUNT_Y = 20;
const int WALL_THICKNESS = BLOCK_SIZE*0.08;

const int SCREEN_WIDTH = (BLOCK_COUNT_X-1)*WALL_THICKNESS + BLOCK_COUNT_X*BLOCK_SIZE;
const int SCREEN_HEIGHT = (BLOCK_COUNT_Y-1)*WALL_THICKNESS + BLOCK_COUNT_Y*BLOCK_SIZE;

const std::string TITLE = "MAZE"; 

const Vector2f start(0, 0);
const Vector2f end(BLOCK_COUNT_X-1, BLOCK_COUNT_Y-1);
std::vector<Block*> open_list;
std::vector<Block*> closed_list;
std::vector<Block*> path;

using namespace sf;

int main()
{
    Maze maze(BLOCK_COUNT_X, BLOCK_COUNT_Y);   

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE, Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);    // VSync

    window.setPosition(Vector2i(300, 100));


    MazeGeneration g_maze(maze,BLOCK_COUNT_X,BLOCK_COUNT_Y);
    g_maze.generate_maze(WALL_THICKNESS, BLOCK_SIZE, &g_maze);

    A_Star a(start, end, &maze, Vector2f(BLOCK_COUNT_X-1, BLOCK_COUNT_Y-1), 4*WALL_THICKNESS);
    a.start_path_finding(open_list, closed_list, path);

    RectangleShape start_block(Vector2f(BLOCK_SIZE, BLOCK_SIZE)), end_block(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    start_block.setFillColor(Color::Red);
    end_block.setFillColor(Color::Green);
    start_block.setPosition(Vector2f(start.x*(BLOCK_SIZE+WALL_THICKNESS), start.y*(BLOCK_SIZE+WALL_THICKNESS)));
    end_block.setPosition(Vector2f(end.x*(BLOCK_SIZE+WALL_THICKNESS), end.y*(BLOCK_SIZE+WALL_THICKNESS)));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for (int y=0; y<BLOCK_COUNT_Y; y++) {
            for (int x=0; x<BLOCK_COUNT_X; x++) {
                maze.draw_walls(x,y,window,WALL_THICKNESS,BLOCK_SIZE);
            }
        }
        
        window.draw(start_block);
        window.draw(end_block);

        // Drawing Path
        if (path.size() > 1) 
        {
            for(int i=0; i<(path.size()-1); i++) 
            {
                RectangleShape tmp;
                if (path[i]->position.x == path[i+1]->position.x)   // Horizontal Wall
                {
                    tmp.setSize(Vector2f(WALL_THICKNESS*3, BLOCK_SIZE+4*WALL_THICKNESS));
                    if (path[i]->position.y < path[i+1]->position.y)    // Left to Right Wall
                    {
                        tmp.setPosition(path[i]->position.x*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2, path[i]->position.y*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2);
                    } else if (path[i]->position.y > path[i+1]->position.y) // Right to Left Wall
                    {
                        tmp.setPosition(path[i+1]->position.x*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2, path[i+1]->position.y*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2);
                    }
                } else if (path[i]->position.y == path[i+1]->position.y)    // Vertical Wall
                {
                    tmp.setSize(Vector2f(BLOCK_SIZE+4*WALL_THICKNESS, WALL_THICKNESS*3));
                    if (path[i]->position.x < path[i+1]->position.x)    // Top to Bottom Wall
                    { 
                        tmp.setPosition(path[i]->position.x*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2, path[i]->position.y*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2);
                    } else if (path[i]->position.x > path[i+1]->position.x) // Bottom to Top Wall
                    {
                        tmp.setPosition(path[i+1]->position.x*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2, path[i+1]->position.y*(BLOCK_SIZE+WALL_THICKNESS) + BLOCK_SIZE/2);
                    }
                }
                    tmp.setFillColor(Color::Blue);
                    window.draw(tmp);
            }
        }

        window.display();
        }

    return 0;
}


        // For Visualization (Under Development)
        // for(int i=0; i<open_list.size(); i++) 
        // {
        //     RectangleShape tmp(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        //     tmp.setFillColor(Color::Red);
        //     tmp.setPosition(open_list[i]->position.x*(BLOCK_SIZE+WALL_THICKNESS), open_list[i]->position.y*(BLOCK_SIZE+WALL_THICKNESS));
        //     window.draw(tmp);
        // }
        // for(int i=0; i<closed_list.size(); i++) 
        // {
        //     RectangleShape tmp(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        //     tmp.setFillColor(Color::Green);
        //     tmp.setPosition(closed_list[i]->position.x*(BLOCK_SIZE+WALL_THICKNESS), closed_list[i]->position.y*(BLOCK_SIZE+WALL_THICKNESS));
        //     window.draw(tmp);
        // }
        // for(int i=0; i<path.size(); i++) 
        // {
        //     RectangleShape tmp(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        //     tmp.setFillColor(Color::Blue);
        //     tmp.setPosition(path[i]->position.x*(BLOCK_SIZE+WALL_THICKNESS), path[i]->position.y*(BLOCK_SIZE+WALL_THICKNESS));
        //     window.draw(tmp);
        // }
        // Till Here


















