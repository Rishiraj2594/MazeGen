#include <vector>
#include <SFML/Graphics.hpp>
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
   void draw_walls(int x, int y, sf::RenderWindow& window, int WALL_THICKNESS, int BLOCK_SIZE);
};

#endif