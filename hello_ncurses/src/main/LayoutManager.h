//
// Created by Mike Mitterer on 03.12.16.
//

#ifndef XCTEST_LAYOUTMANAGER_H
#define XCTEST_LAYOUTMANAGER_H

#include <vector>
#include "Window.h"
#include "Screen.h"

namespace mm {
    namespace curses {

        class LayoutManager {
            virtual void layout(const std::vector<Window>& windows)= 0;
        };


        class FlowLayoutManager : LayoutManager {
            void layout(const std::vector<Window>& windows) override {
                const Size size = Screen::getSize();
                std::for_each(windows.begin(), windows.end(), [](const Window& window) {

                });
            }
        };

    }
}
#endif //XCTEST_LAYOUTMANAGER_H
