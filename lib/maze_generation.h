#include <stack>
#include <utility> 
#include "maze.h"
#ifndef MAZE_GENERATION_H
#define MAZE_GENERATION_H

class MazeGeneration {
    private:
        const int x_bound;
        const int y_bound;
        Maze &maze;
        std::stack<std::pair<int, int>> m_stack;
        enum
	    {
		    CELL_PATH_RIGHT = 1,
		    CELL_PATH_BOTTOM  = 2,
		    CELL_VISITED = 4,
	    };
        enum{
            CELL_UP,
            CELL_LEFT,
            CELL_BOTTOM,
            CELL_RIGHT,
        };
    public:
        MazeGeneration(Maze &maze,int x_bound,int y_bound);
        int get_neighbour(int x, int y);
        void remove_wall(int current_x, int current_y,int neighbour_x, int neighbour_y);
        void dfs_genrate_maze(int WALL_THICKNESS, int BLOCK_SIZE);
        void generate_maze(int WALL_THICKNESS, int BLOCK_SIZE, MazeGeneration* d);
};


#endif