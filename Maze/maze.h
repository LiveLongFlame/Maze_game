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
#include <vector>
using namespace std;
class Maze{
private:
	int width =0, height =0;
	string algo = ""; 

protected:
	int start_point[2];
	int end_point[2];
	vector<vector<char>> maze_desgin;
public:
	Maze(int width, int height); 

	//genrates the Maze with start and end points
	vector<vector<char>> generate_maze(int width, int height);
	//helper funciton
	void carve_passages_from(int x, int y);

	//Prints maze onto cli
	void print_maze();

	//solve maze with the specific algo 
	void solve_maze(string algo);
};
#endif
