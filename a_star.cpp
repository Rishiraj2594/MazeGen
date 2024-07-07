#include "lib/a_star.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <cmath>
#include <iostream>

using namespace sf;

Block::Block(Block* parent, Vector2f pos) {
   this->parent = parent;
   this->position = pos;
}

Block::Block(Vector2f pos) {
   parent = NULL;
   position = pos;
}

void Block::calculate_cost(Vector2f end_point) {
   int gCost, hCost, fCost;
   
   if (parent!=NULL) {
      gCost = ++parent->cost[2]; 
   } else {
      gCost = 0;
   }

   hCost = abs(position.x-end_point.x) + abs(position.y-end_point.y);
   fCost = gCost + hCost;

   cost.push_back(gCost);
   cost.push_back(hCost);
   cost.push_back(fCost);
}

A_Star::A_Star(Vector2f start, Vector2f end, Maze* maze, Vector2f bound,int line_thickness) {
   start_position = end;
   end_position = start;
   this->maze = maze;
   bounds = bound;
   this->line_thickness = line_thickness;
   end_found = false;
}

void A_Star::start_path_finding(std::vector<Block*>& open_list, std::vector<Block*>& closed_list, std::vector<Block*>& path) {
   std::thread find_path_thread(&A_Star::find_path, this, std::ref(open_list), std::ref(closed_list), std::ref(path));
   
   find_path_thread.detach();
}

std::vector<Block*> A_Star::walkable_blocks(Block* current_block) {
   Vector2f current_block_pos = current_block->position;
   std::vector<Block*> walkable;

   if (current_block_pos.y > 0)   // Top block check
   {
      if (!((maze->value_at(current_block_pos.x, current_block_pos.y-1) & 2) == 2)) 
      {  
         walkable.push_back(
            new Block(current_block, 
               Vector2f(current_block_pos.x, current_block_pos.y-1)
            )
         );
      } 
   }

   if (current_block_pos.x > 0)   // Left block check
   { 
      if (!(maze->value_at(current_block_pos.x-1, current_block_pos.y) & 1)) 
      {
         walkable.push_back(
            new Block(current_block, 
               Vector2f(current_block_pos.x-1, current_block_pos.y)  
            )
         );
      }
   }

   if (current_block_pos.y < bounds.y)   // Bottom block check
   {
      if (!((maze->value_at(current_block_pos.x, current_block_pos.y) & 2) == 2)) 
      {
         walkable.push_back(
            new Block(current_block, 
               Vector2f(current_block_pos.x, current_block_pos.y+1)
            )
         );
      }
   }

   if (current_block_pos.x < bounds.x) // Right block check
   {
      if (!(maze->value_at(current_block_pos.x, current_block_pos.y) & 1))
      {
         walkable.push_back(
            new Block(current_block, 
               Vector2f(current_block_pos.x+1, current_block_pos.y)
            )
         );
      }
   }

   return walkable;
}

void A_Star::find_path(std::vector<Block*>& open_list, std::vector<Block*>& closed_list, std::vector<Block*>& path) {
   std::vector<Block*> list_walkable_blocks;
   Block* current_block;

   open_list.push_back(new Block(start_position));
   open_list[0]->calculate_cost(end_position);
   while((open_list.size() > 0 ) && !end_found) 
   // for (int k=0; k<4; k++)
   {
      current_block = open_list[0];
      // std::cout<<open_list.size()<<closed_list.size()<<std::endl;
      for (int i=0; i<open_list.size(); i++) 
      {
         if (open_list[i]->cost[2] < current_block->cost[2]) 
         {
            current_block = open_list[i];
         } 
         else if (open_list[i]->cost[2] == current_block->cost[2]) 
         {
            if (open_list[i]->cost[1] < current_block->cost[1]) {
               current_block = open_list[i];
            }
         }
      }

      if (current_block->position == end_position) 
      {
         end_found = true;
      } else 
      {
         list_walkable_blocks = walkable_blocks(current_block);
         for (int i=list_walkable_blocks.size()-1; i>=0; i--) 
         {
            for (int j=0; j<open_list.size(); j++) {
               if (open_list[j]->position == list_walkable_blocks[i]->position)
               {
                  open_list[j]->parent = current_block;
                  open_list[j]->calculate_cost(end_position);
                  list_walkable_blocks.erase(list_walkable_blocks.begin() + i);
               }
            }
            for (int j=0; j<closed_list.size(); j++) 
            {
               if (closed_list[j]->position == list_walkable_blocks[i]->position)
               {
                  delete list_walkable_blocks[i];
                  list_walkable_blocks.erase(list_walkable_blocks.begin() + i);
                  break;
               }
            }
         }

         for (int i=0; i<list_walkable_blocks.size(); i++) {
            list_walkable_blocks[i]->calculate_cost(end_position);
            open_list.push_back(list_walkable_blocks[i]);
         }

         for (int i=open_list.size()-1; i>=0; i--)  
         {
            if (open_list[i]->position == current_block->position) 
            {
               closed_list.push_back(current_block);
               open_list.erase(open_list.begin() + i);
            }
         }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }
   draw_path(current_block, path);
}  

void A_Star::draw_path(Block* currnet_block, std::vector<Block*>& path) 
{
   while (currnet_block->parent != NULL)
   {
      path.push_back(currnet_block);
      currnet_block = currnet_block->parent;
   } 
   path.push_back(currnet_block);
}