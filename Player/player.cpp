/* 
	reinterpret_cast
	Purpose: Player method file 
 */

#include "player.h"
#include <iostream>
#include <string>
using namespace std;
Player::Player(const string& name, int w, int h):Maze(w, h){
	this-> name = name;
	start_postion();
}


void Player::setName(const string name){
	this->name = name;
}

string Player::getName(){
	return name;
}

//todo: visulaise and print out the player move and add it to the score board
//This function allows for the starting postion of the player
void Player::start_postion(){
	int y = start_point[0];
	int x = start_point[1];

	int maze_height = maze_desgin.size();
	int maze_width = maze_desgin[0].size();

	if (y == 0 && y + 1 < maze_height && maze_desgin[y + 1][x] == ' ') {
		maze_desgin[y + 1][x] = 'v'; // Entering from top
		py = y +1; 
		px = x;
	}

	else if (y == maze_height - 1 && y - 1 >= 0 && maze_desgin[y - 1][x] == ' ') {
		maze_desgin[y - 1][x] = '^'; // Entering from bottom
		py = y - 1; 
		px = x;
	}else if (x == 0 && x + 1 < maze_width && maze_desgin[y][x + 1] == ' ') {
		maze_desgin[y][x + 1] = '>'; // Entering from left
		py = y;
		px = x +1;
	}
	else if (x == maze_width - 1 && x - 1 >= 0 && maze_desgin[y][x - 1] == ' ') {
		maze_desgin[y][x - 1] = '<'; // Entering from right
		py = y; 
		px = x -1;
	}	
}
void Player::move_up() {
    int new_y = py - 1;
    int new_x = px;
    if (new_y >= 0 && maze_desgin[new_y][new_x] != '#') {
        maze_desgin[py][px] = '*';  // Clear old position
        maze_desgin[new_y][new_x] = '^'; // Player facing up
        py = new_y;
        px = new_x;
    }
}

void Player::move_down() {
    int new_y = py + 1;
    int new_x = px;
    if (new_y < (int)maze_desgin.size() && maze_desgin[new_y][new_x] != '#') {
        maze_desgin[py][px] = '*';  // Clear old position
        maze_desgin[new_y][new_x] = 'v'; // Player facing down
        py = new_y;
        px = new_x;
    }
}

void Player::move_left() {
    int new_y = py;
    int new_x = px - 1;
    if (new_x >= 0 && maze_desgin[new_y][new_x] != '#') {
        maze_desgin[py][px] = '*';  // Clear old position
        maze_desgin[new_y][new_x] = '<'; // Player facing left
        py = new_y;
        px = new_x;
    }
}

void Player::move_right() {
    int new_y = py;
    int new_x = px + 1;
    if (new_x < (int)maze_desgin[0].size() && maze_desgin[new_y][new_x] != '#') {
        maze_desgin[py][px] = '*';  // Clear old position
        maze_desgin[new_y][new_x] = '>'; // Player facing right
        py = new_y;
        px = new_x;
    }
}
