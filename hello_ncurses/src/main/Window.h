//
// Created by Mike Mitterer on 02.12.16.
//

#ifndef XCTEST_WINDOW_H
#define XCTEST_WINDOW_H

#include <string>
#include "data_types.h"

namespace mm {
    namespace curses {

        class Window {
        private:
            Position position_{0, 0};
            Size size_{1, 1};
            Size minSize_{1, 1};
            Size maxSize_{MAX_SCREEN_WITH, MAX_SCREEN_HEIGHT};

            NCWindow ncWindow;

        public:
            Window();

//            /// move constructor
//            Window(Window&& other);

            WINDOW* get() const;

            const NCWindow& getNCWidow() const;

            void clear() const {
                wclear(ncWindow.get());
            }

            void print(const Position& position, const std::string text);

            void print(coord_t x, coord_t y, const std::string text);

            void update() const;

            const Size& getSize() const;

            void setSize(const Size& size);

            const Window& setPosition(const Position& position);

            const Position& getPosition();

            const Size& getMinSize() const;

            const Window& setMinSize(const Size& size);

            const Window& setMinHeight(const coord_t height);

            const Size& getMaxSize() const;

            const Window& setMaxSize(const Size& size);

        };
    }
}


#endif //XCTEST_WINDOW_H
