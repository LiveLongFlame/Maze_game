/* 
	Purpose: Maze method file
*/

#include "maze.h"
#include <cstddef>
#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>    // for rand()
#include <ctime>      // for time()
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine
Maze::Maze(int w, int  h){
	this->width = w;
	this->height = h;
	generate_maze(w, h);
}

void Maze::carve_passages_from(int x, int y) {
    // Directions: up, down, left, right
    std::vector<std::pair<int, int>> directions = {
        {0, -2}, {0, 2}, {-2, 0}, {2, 0}
    };

    // Shuffle directions to ensure randomness
    std::shuffle(directions.begin(), directions.end(), std::default_random_engine(std::rand()));

    maze_desgin[y][x] = ' '; // Mark current cell as a passage

    for (auto [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        // Check if the neighbor is within bounds
        if (ny > 0 && ny < height - 1 && nx > 0 && nx < width - 1) {
            if (maze_desgin[ny][nx] == '#') {
                // Knock down the wall between current and neighbor
                maze_desgin[y + dy / 2][x + dx / 2] = '.';
                carve_passages_from(nx, ny); // Recurse
            }
        }
    }
}

vector<vector<char>> Maze::generate_maze(int width, int height){
 // Fix even dimensions
    if (width % 2 == 0) width--;
    if (height % 2 == 0) height--;

    this->width = width;
    this->height = height;

    maze_desgin.resize(height, vector<char>(width, '#'));

    std::srand(std::time(nullptr)); // Seed RNG

    // Generate maze
    carve_passages_from(1, 1);

    // Generate list of possible edge positions (odd cells on edges)
    vector<pair<int, int>> edge_cells;

    for (int i = 1; i < width; i += 2) {
        if (maze_desgin[1][i] == ' ') edge_cells.emplace_back(i, 0);              // Top edge
        if (maze_desgin[height - 2][i] == ' ') edge_cells.emplace_back(i, height - 1); // Bottom edge
    }

    for (int i = 1; i < height; i += 2) {
        if (maze_desgin[i][1] == ' ') edge_cells.emplace_back(0, i);              // Left edge
        if (maze_desgin[i][width - 2] == ' ') edge_cells.emplace_back(width - 1, i);  // Right edge
    }

    if (edge_cells.size() < 2) return maze_desgin; // Can't place start/end if less than 2 exits

    // Pick random start and end from edge_cells
    int si = rand() % edge_cells.size();
    int ei = rand() % edge_cells.size();
    while (ei == si) ei = rand() % edge_cells.size(); // Ensure different positions

    auto [sx, sy] = edge_cells[si];
    auto [ex, ey] = edge_cells[ei];

    maze_desgin[sy][sx] = 'S';
    maze_desgin[ey][ex] = 'E';

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
