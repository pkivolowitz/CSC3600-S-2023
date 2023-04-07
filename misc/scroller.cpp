#include <ncurses.h>
#include <ctime>
#include <vector>
#include <cassert>

using std::vector;

/*  SelectCharacter() - this function returns one of 0 through 9 on
    a persistent rotating basis.
*/
char SelectCharacter() {
    static int counter = 0;
	int previous_counter = counter;
	counter = (++counter % 10);
	return '0' + previous_counter;
}

/*  Delay(steps_per_second) - this function introduces a delay based
    upon its parameter. The parameter is the number of steps per second
    desired (example 5). steps_per_second cannot be less than or equal
    to 0.
*/

bool Delay(int steps_per_second = 8) {
	static timespec ts = {0, 0};
	assert(steps_per_second > 0);
	int modifier = 1000 / steps_per_second;
    // tv_nsec is in nanoseconds. Multiply modifier by 1,000,000 to
    // convert to milliseconds.
    ts.tv_nsec = 1000 * 1000 * modifier;
    return !nanosleep(&ts, nullptr);
}

/*  main() - after initializing curses and preserving a pointer to
    stdscr, a secondary window is made which is smaller and centered
    in the main window.

    New text is added to the main window at the bottom after scrolling 
    up.

    New text is added to the secondary window at the top after scrolling
    down.

    This program terminates with control-c.
*/

int main() {
    WINDOW * main_window = initscr();
	WINDOW *secondary_window = newwin(
        LINES / 3, COLS / 3, 
        LINES - 2 * LINES / 3, COLS - 2 * COLS / 3
    );
    // Silence unused variable warning for sw_lines.
	__attribute__((unused)) int sw_lines;
	int sw_cols;

    curs_set(0);
    getmaxyx(secondary_window, sw_lines, sw_cols);
	scrollok(main_window, true);
    scrollok(secondary_window, true);


	do {
        char c = SelectCharacter();
        vector<char> m_chars = vector<char>(COLS - 2, c);
        vector<char> s_chars = vector<char>(sw_cols - 2, c);

        scroll(main_window);
        mvaddstr(LINES - 2, 1, m_chars.data());
        box(main_window, 0, 0);
        mvaddstr(0, 2, " ^C to exit ");
		wrefresh(main_window);

        wscrl(secondary_window, -1);
        mvwaddstr(secondary_window, 1, 1, s_chars.data());
        box(secondary_window, 0, 0);
		wrefresh(secondary_window);
	} while (Delay());

	endwin();
    return 0;
}
