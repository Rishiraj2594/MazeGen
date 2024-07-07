#include<SFML/Graphics.hpp>
#include<vector>
#include "maze.h"

using namespace sf;

#ifndef A_STARH
#define A_STARH

class Block {
   public:
   Block* parent;
   Vector2f position;
   std::vector<int> cost;

   Block(Block*, Vector2f);
   Block(Vector2f);
   void calculate_cost(Vector2f end_point);
};

class A_Star {
   private:
      Vector2f start_position;
      Vector2f end_position;
      Vector2f bounds;
      int line_thickness;
      Maze* maze;
      bool end_found;

   public:
      A_Star(Vector2f, Vector2f, Maze*, Vector2f, int);
      void find_path(std::vector<Block*>&, std::vector<Block*>&, std::vector<Block*>&);
      void start_path_finding(std::vector<Block*>&, std::vector<Block*>&, std::vector<Block*>&);
      void draw_path(Block*, std::vector<Block*>&);
      std::vector<Block*> walkable_blocks(Block*);
};

#endif