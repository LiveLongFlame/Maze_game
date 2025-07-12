/* 
	Purpose: Player object file 
 */
#ifndef PLAYER_H
#define PLAYER_H
/*
 Todo: 
	-score [object]
	-move_set [up,down,left,right] 
	-path
	-Name 
 */
#include "../Maze/maze.h"
#include "../Scoreboard/score.h"
#include <string>
#include <vector>
using namespace std;
class Player: public Maze , public Score{ 
private: 
	bool game_over = false;
	bool has_won = false;	
	string name; 
	bool game_win_loose = false;
	int width =0, height =0;
	int py = 0, px = 0;
public:
		//Constructers
		Player(const string& name , int width, int height, int points, int moves);

		//setters 
		void setName(const string name);

		//getters 
		string getName();
		bool isGameOver();
		bool didWin();
		//game logic functions
		void start_postion();
		void move_up();
		void move_down();
		void move_left();
		void move_right();
		
		void solve_maze(string algo);
		void dfs();
		void bfs();


};
#endif
