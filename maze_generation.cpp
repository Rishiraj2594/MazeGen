#include "lib/maze_generation.h"
#include<vector>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include<iostream>

MazeGeneration::MazeGeneration(Maze &maze,int x_bound,int y_bound):maze(maze), x_bound(x_bound), y_bound(y_bound){
    srand(time(0));
}

int MazeGeneration::get_neighbour(int x, int y){
    std::vector<int> neighbours;
    if( y-1 >=0 && (maze.value_at(x,y-1) & CELL_VISITED) == 0 ){
        neighbours.push_back(CELL_UP);
        // std::cout<<"Cell Up"<<CELL_UP<<std::endl; // for Debugging
    }
    if( y+1< y_bound &&(maze.value_at(x,y+1) & CELL_VISITED) == 0){ 
        neighbours.push_back(CELL_BOTTOM);
        // std::cout<<"Cell Bottom"<<CELL_BOTTOM<<std::endl; for Debugging

    }
    if( x-1 >=0 && (maze.value_at(x-1,y) & CELL_VISITED) == 0 ){
        neighbours.push_back(CELL_LEFT);
        // std::cout<<"Cell Left"<<CELL_LEFT<<std::endl; // For debugging

    }
    if( x+1 < x_bound && (maze.value_at(x+1,y) & CELL_VISITED) == 0){  
        neighbours.push_back(CELL_RIGHT);
        // std::cout<<"Cell Right"<<CELL_RIGHT<<std::endl; //for Debugging

    }
    if(neighbours.size()>0){
        int rand_index = rand() % neighbours.size();
        int neighbour = neighbours.at(rand_index);
        return neighbour;
    }
    else{
        return -1;
    }
}

void MazeGeneration::remove_wall(int current_x, int current_y,int neighbour_x, int neighbour_y){

    if((current_x - neighbour_x) == 1){
        maze.remove_left_wall(neighbour_x,neighbour_y);
    }

    else if((current_x - neighbour_x) == -1){
        maze.remove_left_wall(current_x,current_y);
    }

    if((current_y-neighbour_y) == 1){
        maze.remove_bottom_wall(neighbour_x,neighbour_y);
    }
    else if((current_y-neighbour_y) == -1)
    {
        maze.remove_bottom_wall(current_x,current_y);
    }
}

void MazeGeneration::dfs_genrate_maze(int WALL_THICKNESS, int BLOCK_SIZE){
    // setting random initial x & y values
    int current_x = rand() % x_bound; 
    int current_y = rand() % y_bound;
    int neighbour;
    maze.setActiveCell(current_x,current_y);
    m_stack.push({current_x,current_y});
    while(!m_stack.empty()){
        current_x = m_stack.top().first;
        current_y = m_stack.top().second;
        neighbour = get_neighbour(current_x,current_y);
        if(neighbour>=0){
            switch(neighbour){
                case CELL_UP:
                             remove_wall(current_x,current_y,current_x,current_y-1);
                             maze.setActiveCell(current_x,current_y-1);
                             m_stack.push({current_x,current_y-1});
                             break;
                case CELL_LEFT:
                             remove_wall(current_x,current_y,current_x-1,current_y);
                             maze.setActiveCell(current_x-1,current_y);
                             m_stack.push({current_x-1,current_y});
                             break;
                case CELL_BOTTOM:
                             remove_wall(current_x,current_y,current_x,current_y+1);
                             maze.setActiveCell(current_x,current_y+1);
                             m_stack.push({current_x,current_y+1});
                             break;
                case CELL_RIGHT:
                             remove_wall(current_x,current_y,current_x+1,current_y);
                             maze.setActiveCell(current_x+1,current_y);
                             m_stack.push({current_x+1,current_y});
                             break;
            }
        }
        else{
            m_stack.pop();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}
void MazeGeneration::generate_maze(int WALL_THICKNESS, int BLOCK_SIZE, MazeGeneration* d) {
    std::thread mazeGenerationThread(&MazeGeneration::dfs_genrate_maze, d, WALL_THICKNESS, BLOCK_SIZE);
    
    mazeGenerationThread.detach();
}