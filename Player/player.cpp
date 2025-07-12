/* 
	reinterpret_cast
	Purpose: Player method file 
 */

#include "player.h"
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;
Player::Player(const string& name, int w, int h , int points, int moves):Maze(w, h),Score(points, moves){
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

    if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
        new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

        if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
            game_over = true;
            has_won = true;
        }

        if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S') {
            maze_desgin[py][px] = '*';
            maze_desgin[new_y][new_x] = '^';
			print_maze();
            py = new_y;
            px = new_x;
            addMove();

            if (player_visited_path[py][px]) {
                addPoint();
                addPoint();
            } else {
                addPoint();
            }

            player_visited_path[py][px] = true;
        }
    }
}

void Player::move_down() {
    int new_y = py + 1;
    int new_x = px;

    if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
        new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

        if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
            game_over = true;
            has_won = true;
        }

        if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S') {
            maze_desgin[py][px] = '*';
            maze_desgin[new_y][new_x] = 'v';
			print_maze();
            py = new_y;
            px = new_x;
            addMove();

            if (player_visited_path[py][px]) {
                addPoint();
                addPoint();
            } else {
                addPoint();
            }

            player_visited_path[py][px] = true;
        }
    }
}

void Player::move_left() {
    int new_y = py;
    int new_x = px - 1;

    if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
        new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

        if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
            game_over = true;
            has_won = true;
        }

        if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S') {
            maze_desgin[py][px] = '*';
            maze_desgin[new_y][new_x] = '<';
			print_maze();
            py = new_y;
            px = new_x;
            addMove();

            if (player_visited_path[py][px]) {
                addPoint();
                addPoint();
            } else {
                addPoint();
            }

            player_visited_path[py][px] = true;
        }
    }
}

void Player::move_right() {
    int new_y = py;
    int new_x = px + 1;

    if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
        new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

        if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
            game_over = true;
            has_won = true;
        }

        if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S') {
            maze_desgin[py][px] = '*';
            maze_desgin[new_y][new_x] = '>';
			print_maze();
            py = new_y;
            px = new_x;
            addMove();

            if (player_visited_path[py][px]) {
                addPoint();
                addPoint();
            } else {
                addPoint();
            }

            player_visited_path[py][px] = true;
        }
    }
}


bool Player::isGameOver() {
    return game_over;
}

bool Player::didWin() {
    return has_won;
}

