//
// Created by Mike Mitterer on 02.12.16.
//

#ifndef XCTEST_WINDOW_H
#define XCTEST_WINDOW_H

#include "data_types.h"

namespace mm {
    namespace curses {

        class Window {
        private:
            Position position_;
            Size size_;

            NCWindow ncWindow;

        public:
            Window(const Position& position, const Size& size);

            WINDOW* get() const;

            const NCWindow& getNCWidow() const;

            void clear() const {
                wclear(ncWindow.get());
            }

            void draw() const ;

            const Size& getSize() const;

            void setSize(const Size& size);
        };
    }
}


#endif //XCTEST_WINDOW_H
