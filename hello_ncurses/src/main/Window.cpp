//
// Created by Mike Mitterer on 02.12.16.
//

#include "Window.h"

namespace mm {
    namespace curses {

        Window::Window()
                : ncWindow{newwin(size_.height(), size_.width(), position_.y(), position_.x()), &delwin} {

        }

//        Window::Window(Window&& other) : position_{other.position_},
//                                         size_{other.size_},minSize_{other.minSize_},maxSize_{other.maxSize_} {
//            ncWindow = other.ncWindow;
//            other.ncWindow = nullptr;
//        }


        const Size& Window::getSize() const {
            return size_;
        }

        void Window::setSize(Size size) {
            size_.width(size.width());
            size_.height(size.height());
            ::wresize(ncWindow.get(), size.height(), size.width());
        }

        WINDOW* Window::get() const {
            return ncWindow.get();
        }

        const NCWindow& Window::getNCWidow() const {
            return ncWindow;
        }

        void Window::update() const {
            ::wrefresh(ncWindow.get());
        }

        void Window::updatePosition() const {
            mvwin(ncWindow.get(), position_.y(),position_.x());
        }

        const Window& Window::clear() const {
            wclear(ncWindow.get());
            return *this;
        }

        const Window& Window::print(const Position& position, const std::string text) const {
            print(position.x(), position.y(), text);
            return *this;
        }

        const Window& Window::print(coord_t x, coord_t y, const std::string text) const {
            mvwprintw(ncWindow.get(), y, x, text.c_str());
            return *this;
        }

        const Window& Window::box() const {
            ::box(ncWindow.get(), 0, 0);
            return *this;
        }


        const Size& Window::getMinSize() const {
            return minSize_;
        }

        const Window& Window::setMinSize(const Size& size) {
            minSize_ = size;
            return *this;
        }

        const Window& Window::setMinHeight(const coord_t height) {
            minSize_.height(height);
            return *this;
        }

        const Size& Window::getMaxSize() const {
            return maxSize_;
        }

        const Window& Window::setMaxSize(const Size& size) {
            maxSize_ = size;
            return *this;
        }

        const Window& Window::setPosition(const Position& position) {
            position_ = position;
            return  *this;
        }

        const Position& Window::getPosition() {
            return position_;
        }



    }
}
