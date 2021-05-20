#pragma once

//
// Created by Mike Mitterer on 20.05.21.
//

#include <sstream>

namespace mm::string {

    /*! note: delimiter cannot contain NUL characters
     */
    template <typename Range, typename Value = typename Range::value_type>
    std::string Join(Range const& elements, const char *const delimiter) {
        std::ostringstream os;
        auto b = begin(elements), e = end(elements);

        if (b != e) {
            std::copy(b, prev(e), std::ostream_iterator<Value>(os, delimiter));
            b = prev(e);
        }
        if (b != e) {
            os << *b;
        }

        return os.str();
    }

    /*! note: imput is assumed to not contain NUL characters
     */
    template <typename Input, typename Output, typename Value = typename Output::value_type>
    void Split(char delimiter, Output &output, Input const& input) {
        using namespace std;
        for (auto cur = begin(input), beg = cur; ; ++cur) {
            if (cur == end(input) || *cur == delimiter || !*cur) {
                output.insert(output.end(), Value(beg, cur));
                if (cur == end(input) || !*cur)
                    break;
                else
                    beg = next(cur);
            }
        }
    }
} // namespace TextUtils
