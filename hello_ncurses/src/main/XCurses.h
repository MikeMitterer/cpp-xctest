//
// Created by Mike Mitterer on 08.12.16.
//

#ifndef XCTEST_CURSES_H
#define XCTEST_CURSES_H

#include "data_types.h"

#undef getch

namespace mm {
    namespace curses {

        enum class Cursor { ON, OFF };
        enum class Echo { ON, OFF };

        class Curses {
        public:
            void init() const;
            const Curses& initscr() const;
            const Curses& initColor() const;

            const Curses& echo(Echo state) const;
            const Curses& cursor(Cursor state) const;

            const Curses& clear() const;

            /// Update the Terminal (refresh)
            ///
            /// This means that any change to a window is not printed to the
            /// physical screen until a refresh is done.
            void update() const;

            Size screenSize() const;

            int getch() const;

            virtual ~Curses();
        };

    }
}

#endif //XCTEST_CURSES_H
