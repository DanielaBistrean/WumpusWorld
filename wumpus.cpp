// #include <ncurses.h>

#include "agent.h"

// static int max_x, max_y;

// void print_frame()
// {
// 	int i;
// 	for (i = 1; i < max_y - 1; i++)
// 	{
// 		mvaddch(i, 0, ACS_VLINE);
// 		mvaddch(i, max_x - 1, ACS_VLINE);
// 	}

// 	for (i = 1; i < max_x - 1; i++)
// 	{
// 		mvaddch(0, i, ACS_HLINE);
// 		mvaddch(max_y - 1, i, ACS_HLINE);
// 	}

// 	mvaddch(0, 0, ACS_ULCORNER);
// 	mvaddch(max_y - 1, 0, ACS_LLCORNER);
// 	mvaddch(0, max_x - 1, ACS_URCORNER);
// 	mvaddch(max_y - 1, max_x - 1, ACS_LRCORNER);
// }

int
main(int argc, char const *argv[])
{
	// initscr();

	// printw("WumpusWorld");

	// refresh();
	// getch();

	// endwin();
	// print_frame();

	agent a;
	all_sensors as;

	a.nextAction(as);

	return 0;
}
