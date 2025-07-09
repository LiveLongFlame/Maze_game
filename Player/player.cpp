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
	}
	else if (y == maze_height - 1 && y - 1 >= 0 && maze_desgin[y - 1][x] == ' ') {
		maze_desgin[y - 1][x] = '^'; // Entering from bottom
	}
	else if (x == 0 && x + 1 < maze_width && maze_desgin[y][x + 1] == ' ') {
		maze_desgin[y][x + 1] = '>'; // Entering from left
	}
	else if (x == maze_width - 1 && x - 1 >= 0 && maze_desgin[y][x - 1] == ' ') {
		maze_desgin[y][x - 1] = '<'; // Entering from right
	}	
}
void Player::move_up(){
}
void Player::move_down(){
}
void Player::move_left(){
}
void Player::move_right(){
}


