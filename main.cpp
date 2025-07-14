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
void choose_algo(Player& player) {
    curs_set(0);

    std::vector<std::string> options = {
        "Breadth-First Search (BFS)",
        "Depth-First Search (DFS)",
        "A* Search"
    };

    int selected = 0;
    int ch;
    int start_row = 5, start_col = 2;

    while (true) {
        clear();
        mvprintw(start_row - 2, start_col, "Choose an Algorithm (Press 'q' to cancel):");

        for (size_t i = 0; i < options.size(); ++i) {
            if ((int)i == selected) {
                attron(A_REVERSE);
                mvprintw(start_row + i, start_col, "%s", options[i].c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(start_row + i, start_col, "%s", options[i].c_str());
            }
        }

        refresh();
        ch = getch();

        if (ch == 'j' || ch == KEY_DOWN) {
            selected = (selected + 1) % options.size();
        } else if (ch == 'k' || ch == KEY_UP) {
            selected = (selected - 1 + options.size()) % options.size();
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        } else if (ch == 'q') {
            return; // Exit without running any algorithm
        }
    }

    // Run selected algorithm
    if (selected == 0) {
        player.solve_maze("bfs");
    } else if (selected == 1) {
        player.solve_maze("dfs");
    } else if (selected == 2) {
        player.solve_maze("astar");
    }

    clear();
    player.print_maze();

    // Get terminal size for centering
    int term_row, term_col;
    getmaxyx(stdscr, term_row, term_col);

    int player_moves = player.getMove();
    int player_points = player.getPoint();
    int algo_moves = player.getMove_algo();
    int algo_points = player.getPoint_algo();

    std::string algo_name = options[selected];
    std::string line1 = "Algorithm: " + algo_name;
    std::string line2 = "Algorithm - Moves: " + std::to_string(algo_moves) + "  Points: " + std::to_string(algo_points);
    std::string line3 = "Player    - Moves: " + std::to_string(player_moves) + "  Points: " + std::to_string(player_points);
    std::string line4 = "Press any key to continue...";
	attron(COLOR_PAIR(2));
    mvprintw(term_row / 2 - 2, (term_col - line1.size()) / 2, "%s", line1.c_str());
    mvprintw(term_row / 2 - 1, (term_col - line2.size()) / 2, "%s", line2.c_str());
    mvprintw(term_row / 2 + 0, (term_col - line3.size()) / 2, "%s", line3.c_str());
    mvprintw(term_row / 2 + 2, (term_col - line4.size()) / 2, "%s", line4.c_str());
	attroff(COLOR_PAIR(2));
    refresh();
    getch();

    // Determine winner
    std::string result;
    if (player_points < algo_points && player.isGameOver()) {
        result = "You Win! ";
    } else if (player_points > algo_points && player.isGameOver()) {
        result = "Algorithm Wins!";
    } else if(player_points == algo_points && player.isGameOver()){
        result = "It's a Draw!";
    } else{
		result = "YOU LOOSE";
	}

    clear();
    std::string winner_line = "Result: " + result;
    mvprintw(term_row / 2, (term_col - winner_line.size()) / 2, "%s", winner_line.c_str());
    mvprintw(term_row / 2 + 2, (term_col - 28) / 2, "Press any key to countinue...");
    refresh();
    getch();
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
	init_pair(4, COLOR_GREEN, -1);  

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
	while ((input = getch()) != 'q' ) {
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
		if(player.isGameOver()){
			// Flush one last frame after move ends game
        clear();
        player.print_maze(); // To show player reaching end
        refresh();
        napms(500); // Short pause so user sees win
        break;
		}
	}
	//Error: ONCE THE PLAYER GOES CHANGE DOES THE MAZE AND DOES IT THE ALGORITHM DOESNT SHOW. HOWEVER IF I JUST QUIT THEN THE ALGORITHM SHOWS if the game end 
	choose_algo(player);
	refresh();
	endwin(); 
	return 0;
}
