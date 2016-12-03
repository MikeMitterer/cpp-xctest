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
            const Size& init() {
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

            /// Add a new Window to the Main-Screen
            void add(const Window& window) {
                windows.push_back(window);
            }

            static const Size getSize() {
                return Size{
                        static_cast<coord_t>(getmaxx(stdscr)),
                        static_cast<coord_t>(getmaxy(stdscr))
                    };
            }

            void onResize() {
                updateSize();
                update();
            }

            void update() {
                wclear(stdscr);

                std::for_each(windows.begin(),windows.end(),[&] (Window& window) {
                    //window.setSize(size);
                    window.clear();
                });

                refresh();

                std::for_each(windows.begin(),windows.end(),[&] (Window& window) {
                    window.update();
                });

            }

            virtual ~Screen();

        private:
            void updateSize() {
                // set up initial windows
                size.width(static_cast<coord_t>(getmaxx(stdscr)));
                size.height(static_cast<coord_t>(getmaxy(stdscr)));
            }
        };

        Screen::~Screen() {
            wclear(stdscr);
            endwin();
        }

    }
}

#endif //XCTEST_SCREEN_H
