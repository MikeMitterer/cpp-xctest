#include <ncurses.h>
#include <unistd.h>
#include <fmt/format.h>
#include <iostream>
#include <queue>
#include <main/Screen.h>

#include "main/data_types.h"

/**
 * Sample verwendet folgendes Libs:
 *      Formatter:  https://github.com/fmtlib/fmt
 *      Logger: https://github.com/gabime/spdlog
 *      ArgParser: https://github.com/Taywee/args
 *
 * More infos:
 *      https://de.wikibooks.org/wiki/Ncurses:_Inhaltsverzeichnis
 *      http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
 *      http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/tools.html
 *      http://frank.harvard.edu/~coldwell/ncurses/ncurses-intro.html
 *      https://www.gnu.org/software/guile-ncurses/manual/guile-ncurses.html
 *      https://www.viget.com/articles/c-games-in-ncurses-using-multiple-windows
 *      http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html
 *      http://www.linuxfocus.org/Deutsch/March2002/article233.shtml
 *
 * GH-Samples:
 *      Collection:     https://github.com/tony/NCURSES-Programming-HOWTO-examples
 *      Menu:           https://goo.gl/DTIQSK
 *                      http://techlister.com/linux/creating-menu-with-ncurses-in-c/1293/
 *      ToDo:           https://github.com/phillip-h/todo
 *
 *  Gist:
 *      https://gist.github.com/reagent/9819045
 *
 *  C++ Libs:
 *      Curses++:   https://sourceforge.net/projects/cursesplusplus/
 *      libcwpp:    https://github.com/giszo/libcwpp
 *      unicurses:  https://github.com/Chiel92/unicurses
 *
 *  Valgrind (CheckMemo / Avoid MemLeaks)
 *      http://valgrind.org/docs/manual/quick-start.html#quick-start.intro
 */

const int8_t KEY_X = 120;
const int8_t BORDER_WIDTH = 1;

using namespace mm::curses;

/// Initializes des given Window and returns the Main-Window size
std::tuple<coord_t, coord_t> init_screen(NCWindow field,NCWindow score,int score_size) {
    coord_t size_x, size_y;
    getmaxyx(stdscr, size_y, size_x);

    wresize(field.get(), size_y - score_size, size_x);

    wresize(score.get(), score_size, size_x);
    mvwin(score.get(), size_y - score_size, 0);


    wclear(stdscr);
    wclear(field.get());
    wclear(score.get());

    refresh(); // refresh() is equivalent to wrefresh(stdscr).

    box(field.get(), 0, 0);
    box(score.get(), 0, 0);

    // refresh each window
    wrefresh(field.get());
    wrefresh(score.get());

    return std::make_tuple(size_x, size_y);
}

int main(int argc, char *argv[]) {
    coord_t size_x, size_y;
    uint8_t score_size = 3;

    Screen screen;
    Size size = screen.init();

    size_x = size.width();
    size_y = size.height();

    //auto header = NCWindow(newwin(size_y - score_size, size_x, 0, 0),&delwin);
    //auto field = NCWindow(newwin(size_y - score_size, size_x, 0, 0),&delwin);
    //auto score = NCWindow(newwin(score_size, size_x, size_y - score_size, 0),&delwin);

    Window field;
    Window score;

    score.setMinHeight(3);

    screen.add(field);
    screen.add(score);


    wbkgd(field.get(), COLOR_PAIR(2));

    int key = -1;
    std::deque<int> logs;

    //std::tie(size_x, size_y) = init_screen(field.getNCWidow(), score, score_size);
    screen.update();
    do {
        if(key == KEY_RESIZE) {
            screen.onResize();
            //std::tie(size_x, size_y) = init_screen(field.getNCWidow(), score, score_size);
            logs.clear();
        } else {
            logs.push_back(key);
            if(logs.size() >= size_y - score_size - (BORDER_WIDTH * 2)) {
                logs.pop_front();
            }
        }
        field.print(1, 1, "Log");

        coord_t line = 0;
        std::for_each(logs.begin(),logs.end(), [&](int value) {
            field.print(1, static_cast<coord_t>(line + 2), fmt::format("KeyCode: {:3}",value));
            line++;
        });

        score.print( 1, 1, fmt::format("Screen: X: {}, Y: {}, KeyCode: {:10}",
                                                 size_x,size_y,
                                                 key != -1 ? std::to_string(key) : "<not set>"));


        std::string info = "'x' to Exit";
        score.print(static_cast<coord_t>(size_x - BORDER_WIDTH - info.length()),1, info);

        field.update();
        score.update();

        //screen.update();

//        mvwprintw(field.get(), 1, 1, "Log");
//        int line = 0;
//        std::for_each(logs.begin(),logs.end(), [&](int value) {
//            mvwprintw(field.get(), line + 2, 1, fmt::format("KeyCode: {:3}",value).c_str());
//            line++;
//        });
//
//
//        mvwprintw(score.get(), 1, 1, fmt::format("Screen: X:{}, Y:{}, KeyCode: {:10}",
//                                                 size_x,size_y,
//                                                 key != -1 ? std::to_string(key) : "<not set>").c_str() );
//
//
//        std::string info = "'x' to Exit";
//        mvwprintw(score.get(), 1, static_cast<int>(size_x - BORDER_WIDTH - info.length()), info.c_str() );
//
//        // refresh each window
//        wrefresh(field.get());
//        wrefresh(score.get());

    } while((key = getch()) != KEY_X);

    wclear(stdscr);
    endwin();

    return 0;
}
