//
// Created by Mike Mitterer on 05.12.16.
//

#include <vector>
#include "LayoutManager.h"
#include "Screen.h"

namespace mm {
    namespace curses {

        void mm::curses::FlowLayoutManager::layout(
                const std::vector<std::shared_ptr<Window>>& windows) {

            const Size screenSize = Screen::getSize();

            coord_t defHeight = 0;
            uint8_t winWithoutSize = 0;
            std::for_each(windows.begin(), windows.end(), [&](const std::shared_ptr<Window>& window) {
                if (window->getMinSize().height() > 1) {
                    defHeight += window->getMinSize().height();
                } else {
                    winWithoutSize++;
                }
            });

            coord_t averageHeight = 1;
            if (winWithoutSize > 0) {
                averageHeight = (screenSize.height() - defHeight) / winWithoutSize;
            }

            coord_t newYPos = 0;
            std::for_each(windows.begin(), windows.end(), [&](const std::shared_ptr<Window>& window) {
                window->setPosition(Position(window->getPosition().x(), newYPos));
                if (window->getMinSize().height() > 1) {
                    window->setSize(Size(screenSize.width(), window->getMinSize().height()));
                    newYPos += window->getMinSize().height();

                } else {
                    window->setSize(Size(screenSize.width(), averageHeight));
                    newYPos += averageHeight;
                }
            });

        }

    }
}
