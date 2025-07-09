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
#include <string>
#include <vector>
using namespace std;
class Player: public Maze{
private:
	string name;
	int width =0, height =0;
public:
		//Constructers
		Player(const string& name , int width, int height);

		//setters 
		void setName(const string name);

		//getters 
		string getName();
		
		//game logic functions
		void start_postion();
		void move_up();
		void move_down();
		void move_left();
		void move_right();



};
#endif
