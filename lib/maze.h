#include <vector>
#ifndef MAZE_H
#define MAZE_H

class Maze{
   private:
   std::vector<std::vector<int>> maze;

   public:
   Maze(int x_bound, int y_bound);

   int value_at(int x, int y);
   bool remove_all_walls(int x, int y);
   bool remove_left_wall(int x, int y);
   bool remove_bottom_wall(int x, int y);

};

#endif