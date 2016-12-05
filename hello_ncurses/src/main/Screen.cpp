//
// Created by Mike Mitterer on 05.12.16.
//

#include <vector>
#include "data_types.h"
#include "Window.h"
#include "Screen.h"

namespace mm {
    namespace curses {

        const Size& Screen::init() {
            initscr();

            // To use these routines start_color must be called, usually right after initscr
            // More: https://linux.die.net/man/3/init_color
            start_color();
            init_pair(1, COLOR_WHITE, COLOR_BLUE);
            init_pair(2, COLOR_GREEN, COLOR_BLACK);

            clear();
            noecho();
            curs_set(FALSE);

            updateSize();

            return size;
        }


        Screen::~Screen() {
            wclear(stdscr);
            endwin();
        }


    }
}
