//
// Created by Mike Mitterer on 02.12.16.
//

#include "Window.h"

namespace mm {
    namespace curses {

        Window::Window(const mm::curses::Position& position, const mm::curses::Size& size)
                : position_{position},size_{size},
                    ncWindow{newwin(size.height(), size.width(), position.y(), position.x()),&delwin}
                    {
        }


        const Size& Window::getSize() const {
            return size_;
        }

        void Window::setSize(const mm::curses::Size& size) {
            size_ = size;
            wresize(ncWindow.get(), size_.height() - 5, size_.width());
        }

        WINDOW* Window::get() const {
            return ncWindow.get();
        }

        const NCWindow& Window::getNCWidow() const {
            return ncWindow;
        }

        void Window::draw() const {
            box(ncWindow.get(), 0, 0);
            wrefresh(ncWindow.get());
        }

    }
}
