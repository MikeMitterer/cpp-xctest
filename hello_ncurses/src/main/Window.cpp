//
// Created by Mike Mitterer on 02.12.16.
//

#include "Window.h"

namespace mm {
    namespace curses {

        Window::Window(const mm::curses::Position& position, const mm::curses::Size& size)
                : position_{position}, size_{size}, minSize_{1, 1}, maxSize_{MAX_SCREEN_WITH, MAX_SCREEN_HEIGHT},
                  ncWindow{newwin(size.height(), size.width(), position.y(), position.x()), &delwin} {
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

        void Window::update() const {
            box(ncWindow.get(), 0, 0);
            wrefresh(ncWindow.get());
        }

        void Window::print(const Position& position, const std::string text) {
            print(position.x(), position.y(), text);
        }

        void Window::print(coord_t x, coord_t y, const std::string text) {
            mvwprintw(ncWindow.get(), y, x, text.c_str());
        }

        const Size& Window::getMinSize() const {
            return minSize_;
        }

        const Window& Window::setMinSize(const Size& size) {
            minSize_ = size;
            return *this;
        }

        const Size& Window::getMaxSize() const {
            return maxSize_;
        }

        const Window& Window::setMaxSize(const Size& size) {
            maxSize_ = size;
            return *this;
        }
    }
}
