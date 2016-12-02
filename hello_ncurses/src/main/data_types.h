//
// Created by Mike Mitterer on 02.12.16.
//

#ifndef XCTEST_DATA_TYPES_H
#define XCTEST_DATA_TYPES_H

#include <cstdint>
#include <ncurses.h>
#include <memory>

namespace mm {
    namespace curses {

        using NCWindow = std::shared_ptr<WINDOW>;

        class Size {
        private:
            uint8_t x_;
            uint8_t y_;

        public:
            Size(uint8_t x, uint8_t y) : x_{x}, y_{y} {

            }

            uint8_t x() const {
                return x_;
            }

            void x(uint8_t x_) {
                Size::x_ = x_;
            }

            uint8_t y() const {
                return y_;
            }

            void y(uint8_t y_) {
                Size::y_ = y_;
            }

        };
    }
}

#endif //XCTEST_DATA_TYPES_H
