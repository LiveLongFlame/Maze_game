/*  
	Purpose: Score object file 
 */
#ifndef SCORE_H
#define SCORE_H
/* 
	Todo: 
		-points 
		-moves 
 */
class Score{
private:
	int points =0;
	int moves = 0;
	int algo_points =0;
	int algo_moves =0;
public:
	Score(int points, int moves);

	//Gettter funcitons
	int getPoint();
	int getMove();
	int getMove_algo();
	int getPoint_algo();

	//Add to points and moves
	void addPoint(); 
	void addMove();
	void addPoint_algo();
	void addMove_algo();
};
#endif
