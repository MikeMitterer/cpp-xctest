//
// Created by Mike Mitterer on 03.12.16.
//

#ifndef XCTEST_LAYOUTMANAGER_H
#define XCTEST_LAYOUTMANAGER_H

#include <vector>
#include "data_types.h"
#include "Window.h"

namespace mm {
    namespace curses {

        class LayoutManager {
        public:
            virtual void layout(const std::vector<std::shared_ptr<Window>>& windows)= 0;
        };


        class FlowLayoutManager : public LayoutManager {

        public:

            virtual void layout(const std::vector<std::shared_ptr<Window>>& windows) override;
        };

    }
}
#endif //XCTEST_LAYOUTMANAGER_H
