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






