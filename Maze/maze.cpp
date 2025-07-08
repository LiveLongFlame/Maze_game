/* 
	Purpose: Maze method file
*/

#include "maze.h"
#include <cstddef>
#include <ncurses.h>
#include <string>
#include <vector>
Maze::Maze(int w, int  h){
	this->width = w;
	this->height = h;
	generate_maze(w, h);
}


vector<vector<char>> Maze::generate_maze(int width, int height){
	//todo: generetes maze and puts it into vector
	//Define size of maze 
	maze_desgin.resize(height);
	for(int i =0;i < height;i++){
		maze_desgin[i].resize(width);
	}

	for(int i =0; i <height;i++){
		for(int j =0; j < width;j++){
			maze_desgin[i][j] = '#';
		}
	}
	return maze_desgin;
}

//This methods prints the maze
void Maze::print_maze() {
    int term_rows, term_cols;
    getmaxyx(stdscr, term_rows, term_cols); // Terminal height and width

    int start_y = (term_rows - height) / 2;
    int start_x = (term_cols - width) / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Only draw within terminal bounds
            if (start_y + i >= 0 && start_y + i < term_rows &&
                start_x + j >= 0 && start_x + j < term_cols) {
                mvaddch(start_y + i, start_x + j, maze_desgin[i][j]);
            }
        }
    }
}

void Maze::solve_maze(string algo){}
