//
// Created by Mike Mitterer on 02.12.16.
//

#ifndef XCTEST_SCREEN_H
#define XCTEST_SCREEN_H

#include <ncurses.h>
#include "data_types.h"
#include "Window.h"

namespace mm {
    namespace curses {

        class Screen {
        private:
            std::vector<Window> windows;
            Size size{0, 0};

        public:
            void init() {
                initscr();

                // To use these routines start_color must be called, usually right after initscr
                // More: https://linux.die.net/man/3/init_color
                start_color();
                init_pair(1, COLOR_WHITE, COLOR_BLUE);
                init_pair(2, COLOR_GREEN, COLOR_BLACK);

                clear();
                noecho();
                curs_set(FALSE);

                // set up initial windows
                size.x(static_cast<uint8_t>(getmaxx(stdscr)));
                size.y(static_cast<uint8_t>(getmaxy(stdscr)));
            }


            void add(const Window& window) {
                windows.push_back(window);
            }

            const Size& getSize() const;

            virtual ~Screen();
        };

        Screen::~Screen() {
            wclear(stdscr);
            endwin();
        }

        const Size& Screen::getSize() const {
            return size;
        }
    }
}

#endif //XCTEST_SCREEN_H
