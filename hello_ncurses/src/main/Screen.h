//
// Created by Mike Mitterer on 02.12.16.
//

#ifndef XCTEST_SCREEN_H
#define XCTEST_SCREEN_H

#include <ncurses.h>
#include <algorithm>
#include "data_types.h"
#include "Window.h"
#include "LayoutManager.h"

namespace mm {
    namespace curses {

        class Screen {
        private:
            Size size{0, 0};
            std::vector<std::shared_ptr<Window>> windows;
            std::unique_ptr<LayoutManager> layoutManager =
                    std::unique_ptr<LayoutManager>(new FlowLayoutManager());

        public:
            const Size& init();

            /// Add a new Window to the Main-Screen
            void add(std::shared_ptr<Window> window) {
                windows.push_back(window);
            }

             static Size getSize() {
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

                layoutManager.get()->layout(windows);

                std::for_each(windows.begin(),windows.end(),[&] (const std::shared_ptr<Window>& window) {
                    //window.setSize(size);
                    window->updatePosition();
                    window->clear();
                });

                refresh();

                std::for_each(windows.begin(),windows.end(),[&] (const std::shared_ptr<Window>& window) {
                    window->update();
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





    }
}

#endif //XCTEST_SCREEN_H
