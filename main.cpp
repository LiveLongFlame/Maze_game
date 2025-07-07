/* 
	Purpose: Main game loop file
*/
#include <iostream>
#include <ncurses.h>
#include "Maze/maze.h"
#include "Scoreboard/score.h"
#include "Player/player.h"

using namespace std;

int main() {
    initscr();             
    cbreak();              
	curs_set(0);           
    keypad(stdscr, TRUE);  
    clear();
    printw("Hello world"); 
    refresh();            
    getch();              
	endwin();              

    return 0;
}

