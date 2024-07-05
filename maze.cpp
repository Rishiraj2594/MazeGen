#include "lib/maze.h"

using namespace sf;

Maze::Maze(int x_bound, int y_bound) {
   std::vector<int> row_holder;
   for (int i=0; i<y_bound; i++) {
      for (int j=0; j<x_bound; j++) {
         row_holder.push_back(3);
      }
      maze.push_back(row_holder);
      row_holder.clear();
   }
}

int Maze::value_at(int x, int y) {
   return maze[y][x];
}

bool Maze::remove_all_walls(int x, int y) {
   if ((maze[y][x] & 3) == 3) {
      maze[y][x] &= ~3;
      return true;
   } else {
      return false;
   }
}

bool Maze::remove_left_wall(int x, int y) {
   if (maze[y][x] & 1) {
      maze[y][x] &= ~1;
      return true;
   } else {
      return false;
   }
}

bool Maze::remove_bottom_wall(int x, int y) {
   if ((maze[y][x] & 2 )== 2) {
      maze[y][x] &= ~2;
      return true;
   } else {
      return false;
   }
}

void Maze::setActiveCell(int x, int y) {
   maze[y][x] |= 4;
}

void Maze::setCellInactive(int x, int y) {
   maze[y][x] &= ~4;
}

void Maze::draw_walls(int x, int y, sf::RenderWindow& window, int WALL_THICKNESS, int BLOCK_SIZE) {
   if ((maze[y][x] & 1) == 1) {
      window.draw([x, y, WALL_THICKNESS, BLOCK_SIZE] {
         RectangleShape line(
            Vector2f(WALL_THICKNESS, BLOCK_SIZE + WALL_THICKNESS)
         );
         line.setFillColor(Color::Black);
         line.setPosition(
            Vector2f((x+1) * BLOCK_SIZE + x*WALL_THICKNESS, 
                     y * (BLOCK_SIZE+WALL_THICKNESS))
                  );
         return line;
      }());
   }
   if ((maze[y][x] & 2) == 2) {
      window.draw([x, y, WALL_THICKNESS, BLOCK_SIZE] {
         RectangleShape line(
            Vector2f(BLOCK_SIZE + 2*WALL_THICKNESS, WALL_THICKNESS)
            );
         line.setFillColor(Color::Black);
         line.setPosition(
                        Vector2f(x * (BLOCK_SIZE + WALL_THICKNESS) - WALL_THICKNESS, 
                           (y + 1) * BLOCK_SIZE + y*WALL_THICKNESS)
                        );
         return line;
      }());
   }
   /*
   if((maze[y][x] & 4)==4){
       sf::RectangleShape cellColor(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
            cellColor.setPosition(sf::Vector2f(x*(BLOCK_SIZE+WALL_THICKNESS),y*(BLOCK_SIZE+WALL_THICKNESS)));
            cellColor.setFillColor(sf::Color::Cyan);
            window.draw(cellColor);
   }*/
}