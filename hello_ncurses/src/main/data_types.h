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
        using coord_t = uint16_t;

        const coord_t MAX_SCREEN_WITH = 2560;
        const coord_t MAX_SCREEN_HEIGHT = 1440;

        class Position {
        private:
            coord_t x_;
            coord_t y_;

        public:
            Position(coord_t x, coord_t y) : x_{x}, y_{y} {

            }

            coord_t x() const {
                return x_;
            }

            void x(coord_t x) {
                x_ = x;
            }

            coord_t y() const {
                return y_;
            }

            void y(coord_t y) {
                y_ = y;
            }

        };

        class Size {
        private:
            coord_t width_;
            coord_t height_;

        public:
            Size(coord_t width, coord_t height) : width_{width}, height_{height} { }

            /// Size size(Size(10,11)) - ruft den CopyConstructor auf
            Size(const Size& other) : width_{other.width()},height_{other.height()} { }

            /// move constructor
            Size(Size&& other) : width_{other.width()},height_{other.height()} {
            }

            /// copy assignment
            Size& operator=(const Size& other) {
                width_ = other.width_;
                height_ = other.height_;
                return *this;
            }

            /// move assignment
            Size& operator=(const Size&& other) {
                if(this != &other) {

                }
                return *this;
            }

            coord_t width() const {
                return width_;
            }

            void width(coord_t x) {
                width_ = x;
            }

            coord_t height() const {
                return height_;
            }

            void height(coord_t y) {
                height_ = y;
            }

        };

    }
}

#endif //XCTEST_DATA_TYPES_H
