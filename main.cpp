/* 
	Purpose: Main game loop file
*/
#include <iostream>
#include <ncurses.h>
#include <string>
#include "Maze/maze.h"
#include "Scoreboard/score.h"
#include "Player/player.h"

using namespace std;
enum maze_info{
	WIDTH = 30,
	HEIGHT = 5
};


int main() {
    initscr();             
    cbreak();              
    noecho();              
    keypad(stdscr, TRUE);  
    curs_set(1);           // Show the cursor

    int row, col;
    getmaxyx(stdscr, row, col); // Get terminal size

    string name;
    int maxLen = 20;

    int start_row = row / 2 - 1;
    int start_col = (col - 20) / 2;

    mvprintw(start_row, start_col + 5, "Player Name:");
    mvprintw(start_row + 1, start_col, "[                    ]"); // 20 spaces

    move(start_row + 1, start_col + 1); // Move cursor inside the brackets

    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == 10 || ch == KEY_ENTER) {
            break;
        } else if ((ch == KEY_BACKSPACE || ch == 127 || ch == 8) && !name.empty()) {
            name.pop_back();
            int x, y;
            getyx(stdscr, y, x);
            mvaddch(y, x - 1, ' ');
            move(y, x - 1);
        } else if (isprint(ch) && name.length() < maxLen) {
            name += static_cast<char>(ch);
            addch(ch);
        }
        refresh();
    }

    clear();
    Player player(name, start_col + WIDTH , start_row + HEIGHT);
    player.setName(name);
    clear();
	std::string welcomeMsg = "Welcome " + player.getName() + "!";

	int msg_row = 2;  
	int msg_col = (col - (int)welcomeMsg.length()) / 2;

	// Print the message
	mvprintw(msg_row, msg_col, "%s", welcomeMsg.c_str()); 
	
	player.print_maze();
    getch();
    endwin();

    return 0;
}
