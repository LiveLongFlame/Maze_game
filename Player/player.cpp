/* plaeyr
	reinterpret_cast
	Purpose: Player method file 
 */
#include <ncurses.h>
#include <queue>
#include <map>
#include "player.h"
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

		// Check if next tile is walkable and not 'S' (start)
		if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S' && maze_desgin[new_y][new_x] != 'E') {

			// Mark previous position
			maze_desgin[py][px] = '*';

			// Move player
			py = new_y;
			px = new_x;


			// Mark new position
			maze_desgin[py][px] = '^';

			// Print maze after move
			print_maze();

			// Add move count
			addMove();

			// Add points based on visited status
			if (player_visited_path[py][px]) {
				addPoint();  // Already visited — less points?
			} else {
				addPoint();  // First visit
				addPoint();  // Bonus for first time
			}

			// Mark this tile as visited
			player_visited_path[py][px] = true;
		}
		// Check for end after moving
		if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
			game_over = true;
			has_won = true;
		}
	}

}

void Player::move_down() {
	int new_y = py + 1;
	int new_x = px;
	if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
			new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

		// Check if next tile is walkable and not 'S' (start)
		if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S' && maze_desgin[new_y][new_x] != 'E') {

			// Mark previous position
			maze_desgin[py][px] = '*';

			// Move player
			py = new_y;
			px = new_x;

			// Check for end after moving

			// Mark new position
			maze_desgin[py][px] = 'v';

			// Print maze after move
			print_maze();

			// Add move count
			addMove();

			// Add points based on visited status
			if (player_visited_path[py][px]) {
				addPoint();  // Already visited — less points?
			} else {
				addPoint();  // First visit
				addPoint();  // Bonus for first time
			}

			// Mark this tile as visited
			player_visited_path[py][px] = true;
		}
	}
	if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
		game_over = true;
		has_won = true;
	}


}

void Player::move_left() {
	int new_y = py;
	int new_x = px - 1;

	if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
			new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

		// Check if next tile is walkable and not 'S' (start)
		if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S' && maze_desgin[new_y][new_x] != 'E') {

			// Mark previous position
			maze_desgin[py][px] = '*';

			// Move player
			py = new_y;
			px = new_x;

			// Check for end after moving

			// Mark new position
			maze_desgin[py][px] = '<';

			// Print maze after move
			print_maze();

			// Add move count
			addMove();

			// Add points based on visited status
			if (player_visited_path[py][px]) {
				addPoint();  // Already visited — less points?
			} else {
				addPoint();  // First visit
				addPoint();  // Bonus for first time
			}

        // Mark this tile as visited
        player_visited_path[py][px] = true;
    }
}
if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
	game_over = true;
	has_won = true;
}

 
}

void Player::move_right() {
	int new_y = py;
	int new_x = px + 1;

	if (new_y >= 0 && new_y < (int)maze_desgin.size() &&
			new_x >= 0 && new_x < (int)maze_desgin[0].size()) {

		// Check if next tile is walkable and not 'S' (start)
		if (maze_desgin[new_y][new_x] != '#' && maze_desgin[new_y][new_x] != 'S' && maze_desgin[new_y][new_x] != 'E') {

			// Mark previous position
			maze_desgin[py][px] = '*';

			// Move player
			py = new_y;
			px = new_x;

			// Check for end after moving

			// Mark new position
			maze_desgin[py][px] = '>';

			// Print maze after move
			print_maze();

			// Add move count
			addMove();

			// Add points based on visited status
			if (player_visited_path[py][px]) {
				addPoint();  // Already visited — less points?
			} else {
				addPoint();  // First visit
				addPoint();  // Bonus for first time
			}

			// Mark this tile as visited
			player_visited_path[py][px] = true;
		}
	}
	if (maze_desgin[new_y][new_x] == 'E' && !game_over) {
		game_over = true;
		has_won = true;
	}


}


bool Player::isGameOver() {
    return game_over;
}

bool Player::didWin() {
    return has_won;
}

void Player::solve_maze(string algo){
	//todo: implement different algorithms depending on the string algo 
	//2. dfs
	//3. bfs
	//option:
	//A* path finder
	if(algo == "dfs"){
		dfs();
	}else if(algo == "bfs"){
		bfs();
	}
	refresh();
	algo_show = true;
	print_maze();
}

void Player::dfs(){
}
void Player::bfs(){
	 algo_show = true;

    int rows = maze_desgin.size();
    int cols = maze_desgin[0].size();
    algo_path = vector<vector<bool>>(rows, vector<bool>(cols, false));

    queue<pair<int, int>> q;
    map<pair<int, int>, pair<int, int>> parent; // for path reconstruction
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    q.push({start_point[0], start_point[1]});
    visited[start_point[0]][start_point[1]] = true;

    int dy[] = {-1, 1, 0, 0}; // up, down, left, right
    int dx[] = {0, 0, -1, 1};

    pair<int, int> end = {-1, -1};

    while (!q.empty()) {
        auto [y, x] = q.front(); q.pop();

        if (maze_desgin[y][x] == 'E') {
            end = {y, x};
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny >= 0 && ny < rows && nx >= 0 && nx < cols &&
                !visited[ny][nx] &&
                maze_desgin[ny][nx] != '#' &&
                maze_desgin[ny][nx] != 'S') {

                visited[ny][nx] = true;
                parent[{ny, nx}] = {y, x};
                q.push({ny, nx});
            }
        }
    }

   // Reconstruct path and apply scoring logic
   // error: got to fix the point system as it is not adding up correctring
    if (end.first != -1) {
        pair<int, int> curr = end;
        while (curr != make_pair(start_point[0], start_point[1])) {
            int y = curr.first;
            int x = curr.second;
            algo_path[y][x] = true;

            if (player_visited_path[y][x]) {
                addPoint_algo(); // backtracked
                addPoint_algo();
            } else {
                addMove_algo();  // newly explored
                addPoint_algo();
                player_visited_path[y][x] = true;
            }

            curr = parent[curr];
        }

        // Include starting position as well
        if (player_visited_path[py][px]) {
            addPoint_algo();
            addPoint_algo();
        } else {
            addMove_algo();
            addPoint_algo();
            player_visited_path[py][px] = true;
        }

        algo_path[py][px] = true;
    } 
}
