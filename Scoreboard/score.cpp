/*  
	Purpose: Score method file 
 */
#include "score.h";

Score::Score(int points, int moves){
	this->points = points;
	this->moves = moves;
}

int	Score::getPoint(){
	return points;
}
int	Score::getMove(){
	return moves;
}

void Score::addPoint(){
	points++;
}
void Score::addMove(){
	moves++;
}

int	Score::getPoint_algo(){
	return algo_points;

}
int	Score::getMove_algo(){
	return algo_moves;
}

void Score::addPoint_algo(){
	algo_points++;
}
void Score::addMove_algo(){
	algo_moves++;
}


