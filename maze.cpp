#include "lib/maze.h"
#include <vector>

using namespace std;

Maze::Maze(int x_bound, int y_bound) {
   vector<int> row_holder;
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
   if (maze[y][x] == 3) {
      maze[y][x] = 0;
      return true;
   } else {
      return false;
   }
}

bool Maze::remove_left_wall(int x, int y) {
   if (maze[y][x] & 1) {
      maze[y][x] &= 2;
      return true;
   } else {
      return false;
   }
}
bool Maze::remove_bottom_wall(int x, int y) {
   if (maze[y][x] & 2) {
      maze[y][x] &= 1;
      return true;
   } else {
      return false;
   }
}
