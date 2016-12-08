//
// Created by Mike Mitterer on 08.12.16.
//

#include <ncurses.h>
#include "XCurses.h"

namespace mm {
    namespace curses {

        void Curses::init() const {
            initscr();

            clear();
            noecho();
            curs_set(FALSE);
        }

        Curses::~Curses() {
            wclear(stdscr);
            endwin();
        }

        const Curses& Curses::initscr() const {
            ::initscr();
            return *this;
        }

        const Curses& Curses::initColor() const {
            initscr();

            // To use these routines start_color must be called, usually right after initscr
            // More: https://linux.die.net/man/3/init_color
            ::start_color();
            ::init_pair(1, COLOR_WHITE, COLOR_BLUE);
            ::init_pair(2, COLOR_GREEN, COLOR_BLACK);

            return *this;
        }

        const Curses& Curses::clear() const {
            ::clear();
            return *this;
        }

        const Curses& Curses::echo(Echo state) const {
            if(state == Echo::ON) {
                ::echo();
            } else {
                ::noecho();
            }
            return *this;
        }

        const Curses& Curses::cursor(Cursor state) const {
            ::curs_set(state == Cursor::ON ? TRUE : FALSE);
            return *this;
        }

        Size Curses::screenSize() const {
            return Size{
                    static_cast<coord_t>(getmaxx(stdscr)),
                    static_cast<coord_t>(getmaxy(stdscr))
            };
        }

        int Curses::getch() const {
            return wgetch(stdscr);
        }

        void Curses::update() const {
            ::wrefresh(stdscr);
        }
    }
}