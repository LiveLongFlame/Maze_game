/* 
	Purpose: Maze method file
*/
#include <queue>
#include <utility>
#include "maze.h"
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
	//Each path is all false
	player_visited_path.resize(height, vector<bool>(width, false));	

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
	start_point[0] = sy;
	start_point[1] = sx;
    maze_desgin[ey][ex] = 'E';
	end_point[0] = ey;
	end_point[1] = ex;

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
            char ch = maze_desgin[i][j];
			// Detect wall style
			if (ch == '#') {
				bool up    = (i > 0 && maze_desgin[i - 1][j] == '#');
				bool down  = (i < height - 1 && maze_desgin[i + 1][j] == '#');
				bool left  = (j > 0 && maze_desgin[i][j - 1] == '#');
				bool right = (j < width - 1 && maze_desgin[i][j + 1] == '#');

			// if ((left || right) && !(up || down))
				// 	ch = '-';
				// else if ((up || down) && !(left || right))
				// 	ch = '|';
				// else
				// 	ch = '+';
			}

			// Only draw within terminal bounds
			if (start_y + i >= 0 && start_y + i < term_rows &&
					start_x + j >= 0 && start_x + j < term_cols) {

				// Apply colors
				if (ch == '>' || ch == '<' || ch == '^' || ch == 'v') {
					attron(COLOR_PAIR(1));
					mvaddch(start_y + i, start_x + j, ch);
					attroff(COLOR_PAIR(1));
				}
				else if (ch == 'E') {
					attron(COLOR_PAIR(2));
					mvaddch(start_y + i, start_x + j, ch);
					attroff(COLOR_PAIR(2));
				}
				else if (ch == 'S') {
					attron(COLOR_PAIR(3));
					mvaddch(start_y + i, start_x + j, ch);
					attroff(COLOR_PAIR(3));
				}else if (algo_path[i][j]) {
					attron(COLOR_PAIR(3));
					mvaddch(start_y + i, start_x + j, '*');
					attroff(COLOR_PAIR(3));
				}
				else if (ch == '*') {
					attron(COLOR_PAIR(1)); // fallback (or visited by player path maybe)
					mvaddch(start_y + i, start_x + j, ch);
					attroff(COLOR_PAIR(1));
				}else {
					mvaddch(start_y + i, start_x + j, ch);
				}	
			} 
        }
    }
}

void Maze::solve_maze(string algo){
	//todo: implement different algorithms depending on the string algo 
	//1. flodo fill 
	//2. dfs
	//3. bfs
	//option:
	//A* path finder
	if(algo == "flood"){
		flood_fill();
	}else if(algo == "dfs"){
		dfs();
	}else if(algo == "bfs"){
		bfs();
	}
}

void Maze::flood_fill(){
}
void Maze::dfs(){
}
void Maze::bfs(){
	int sx = start_point[1];
    int sy = start_point[0];
    int ex = end_point[1];
    int ey = end_point[0];

    algo_path.assign(height, vector<bool>(width, false));
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-1, -1}));

    queue<pair<int, int>> q;
    q.push({sy, sx});
    visited[sy][sx] = true;

    // Directions: up, down, left, right
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    bool found = false;

    while (!q.empty() && !found) {
        auto [y, x] = q.front();
        q.pop();

        for (auto [dy, dx] : directions) {
            int ny = y + dy;
            int nx = x + dx;

            if (ny >= 0 && ny < height && nx >= 0 && nx < width &&
                !visited[ny][nx] && (maze_desgin[ny][nx] == ' ' || maze_desgin[ny][nx] == 'E')) {

                visited[ny][nx] = true;
                parent[ny][nx] = {y, x};
                q.push({ny, nx});

                if (ny == ey && nx == ex) {
                    found = true;
                    break;
                }
            }
        }
    }

    // Backtrack path from end to start
    if (found) {
        int cy = ey;
        int cx = ex;
        while (!(cy == sy && cx == sx)) {
            algo_path[cy][cx] = true;
            if (maze_desgin[cy][cx] == ' ') maze_desgin[cy][cx] = '*';
            tie(cy, cx) = parent[cy][cx];
        }
        algo_path[sy][sx] = true;
    }
}

