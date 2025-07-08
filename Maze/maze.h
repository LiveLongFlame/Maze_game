/* 
	Purpose: Maze object file 
 */
#ifndef MAZE_H
#define MAZE_H
/* 
Todo: 
	-generate_maze(width, length)
	-sove_maze("algo")
*/
#include <string>
using namespace std;
class Maze{
private:
	int width =0, height =0;
	string algo = ""; 

public:
	Maze(int width, int height); 

	//genrates the Maze with start and end points
	void generate_maze(int width, int height);

	//Prints maze onto cli
	// void print_maze()

	//solve maze with the specific algo 
	void solve_maze(string algo);
};
#endif
