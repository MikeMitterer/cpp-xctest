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
            Size size;

        public:
            const Size& getSize() const;

            void setSize(const Size& size);
        };
    }
}


#endif //XCTEST_WINDOW_H
