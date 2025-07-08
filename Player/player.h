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
#include <string>
#include <vector>
using namespace std;
class Player{
private:
	string name;
public:
		//Constructers
		Player(const string name);

		//setters 
		void setName(const string name);

		//getters 
		string getName();
		
		//game logic functions
		void move_set();



};
#endif
