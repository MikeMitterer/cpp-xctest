//
// Created by Mike Mitterer on 02.12.16.
//

#include "Window.h"

const mm::curses::Size& mm::curses::Window::getSize() const {
    return size;
}

void mm::curses::Window::setSize(const mm::curses::Size& size) {
    Window::size = size;
}
