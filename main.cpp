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

enum maze_info {
	WIDTH = 30,
	HEIGHT = 5
};
void choose_algo(){
	//chooses a side menu on the side and moves the maze and prints maze more to the left so the menu can appear and thus, allows the user to choose what algo they want to show
}
int main() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(1);  // Show the cursor for name input

	// Initialize colors
	start_color();
	use_default_colors();
	init_pair(1, COLOR_BLUE, -1);    // Blue text
	init_pair(2, COLOR_RED, -1);     // Red text
	init_pair(3, COLOR_YELLOW, -1);  // Yellow (Orange-like)

	int row, col;
	getmaxyx(stdscr, row, col); // Terminal size

	string name;
	int maxLen = 20;

	int start_row = row / 2 - 1;
	int start_col = (col - 20) / 2;

	mvprintw(start_row, start_col + 5, "Player Name:");
	mvprintw(start_row + 1, start_col, "[                    ]"); // 20 spaces
	move(start_row + 1, start_col + 1); // Cursor inside brackets

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

	// Hide cursor after name input
	curs_set(0);

	// Create player, maze and scoreboard
	Player player(name, start_col + WIDTH, start_row + HEIGHT , 0, 0);
	player.setName(name);

	// Game loop
	int input;
	while ((input = getch()) != 'q' && !player.isGameOver()) {
		clear();

		// Print Welcome Message
		std::string welcomeMsg = "Welcome " + player.getName() + "!";
		int msg_col = (col - (int)welcomeMsg.length()) / 2;
		mvprintw(1, msg_col, "%s", welcomeMsg.c_str());

		// Print Scoreboard
		std::string score = "Moves: " + to_string(player.getMove()) + " Points: " + to_string(player.getPoint());
		int score_col = (col - (int)welcomeMsg.length()) / 2;
		mvprintw(2, msg_col, "%s", score.c_str());


		// Draw maze
		player.print_maze();

		refresh();

		// Movement controls
		switch (input) {
			case KEY_UP:
			case 'k':
				player.move_up();
				refresh();
				break;
			case KEY_DOWN:
			case 'j':
				player.move_down();
				refresh();
				break;
			case KEY_LEFT:
			case 'h':
				player.move_left();
				refresh();
				break;
			case KEY_RIGHT:
			case 'l':
				player.move_right();
				refresh();
				break;
		}
	//todo: Create menu where users can pick an algorithm and what algorithm they pick will show the algorithms path and points/moves it took for the algorithm so solve., 
	choose_algo();
	}
		//if the game end
		if(player.isGameOver()){
			mvprintw(0, 0, "Algo:\nMove: %d Points: %d", player.getMove_algo(), player.getPoint_algo());
			refresh();
			getch();

		}	


	//tood: win condtion if the player and algo points == then draw else, algo < user = loose or algo > user = win 
	endwin(); 
	return 0;
}
