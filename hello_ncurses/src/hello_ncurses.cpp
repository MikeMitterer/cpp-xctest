#include <ncurses.h>
#include <algorithm>
#include <unistd.h>
#include <fmt/format.h>
#include <iostream>
#include <queue>
#include <atomic>
#include <thread>
#include <chrono>
#include <main/Screen.h>
#include <iomanip>
#include <sstream>

#include "XCurses.h"

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
std::tuple<coord_t, coord_t> init_screen(NCWindow field, NCWindow score, int score_size) {
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

void update(std::atomic<bool>& program_is_running, std::shared_ptr<Window> window) {
    const unsigned int update_interval = 250; // update after every 50 milliseconds
    const auto wait_duration = std::chrono::milliseconds(update_interval);

    while (program_is_running) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        auto t = std::time(nullptr);
        auto tm = std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(tm, "%d-%m-%Y %H:%M:%S");
        //oss << asctime(tm);

        //std::cout << oss.str() << std::endl;

        std::string info = oss.str();
        window->print(static_cast<coord_t>(window->getSize().width() - BORDER_WIDTH - info.length()), 1, info);
        window->update();

        std::this_thread::sleep_for(wait_duration);
    }
}

int main(int argc, char* argv[]) {
    Curses curses;

    curses.initColor().echo(Echo::OFF).cursor(Cursor::OFF).update();

    //curses.clear();
    curses.update();

    Window window1;

    Size screenSize = curses.screenSize();
    window1.setSize(Size{screenSize.width(), static_cast<coord_t>(screenSize.height() / 2)});

    window1.clear().box().print(1, 1, "Hallo3").update();

    int key = -1;
    do {
        if (key == KEY_RESIZE) {
            screenSize = curses.screenSize();
            curses.clear();
            curses.update();

            window1.setSize(Size(screenSize.width(),static_cast<coord_t>(screenSize.height() / 2)));
            window1.updatePosition();

            window1.clear();
        }

        window1.box().print(1, 1, "Hallo");
        window1.print(1, static_cast<coord_t>(window1.getSize().height() - 2),
                      fmt::format("Screen: X: {}, Y: {}, KeyCode: {:10}",
                                  screenSize.width(), screenSize.height(),
                                  key != -1 ? std::to_string(key) : "<not set>"));


        std::string info = "'x' to Exit";
        window1.print(static_cast<coord_t>(window1.getSize().width() - BORDER_WIDTH - info.length()), 1, info);

        window1.update();

    } while ((key = curses.getch()) != KEY_X);

}

int main_old(int argc, char* argv[]) {

    Screen screen;
    Size size = screen.init();

    //auto header = NCWindow(newwin(size_y - score_size, size_x, 0, 0),&delwin);
    //auto field = NCWindow(newwin(size_y - score_size, size_x, 0, 0),&delwin);
    //auto score = NCWindow(newwin(score_size, size_x, size_y - score_size, 0),&delwin);

    auto header = std::shared_ptr<Window>(new Window());
    auto field = std::shared_ptr<Window>(new Window());
    auto score = std::shared_ptr<Window>(new Window());

    screen.add(header);
    screen.add(field);
    screen.add(score);

    header->setMinHeight(3);
    score->setMinHeight(3);


    wbkgd(field.get()->getNCWidow().get(), COLOR_PAIR(2));

    int key = -1;
    std::deque<int> logs;

    std::atomic<bool> running{true};

    std::thread update_thread(update, std::ref(running), header);


    //std::tie(size_x, size_y) = init_screen(field.getNCWidow(), score, score_size);
    screen.update();
    do {
        if (key == KEY_RESIZE) {
            screen.onResize();
            //std::tie(size_x, size_y) = init_screen(field.getNCWidow(), score, score_size);
            logs.clear();
        } else {
            logs.push_back(key);
            if (logs.size() >= field->getSize().height() - BORDER_WIDTH) {
                logs.pop_front();
            }
        }
        header->print(1, 1, "Log");

        coord_t line = 0;
        std::for_each(logs.begin(), logs.end(), [&](int value) {
            field->print(1, static_cast<coord_t>(line + 1), fmt::format("KeyCode: {:3}", value));
            line++;
        });

        score->print(1, 1, fmt::format("Screen: X: {}, Y: {}, KeyCode: {:10}",
                                       screen.getSize().width(), screen.getSize().height(),
                                       key != -1 ? std::to_string(key) : "<not set>"));


        std::string info = "'x' to Exit";
        score->print(static_cast<coord_t>(score->getSize().width() - BORDER_WIDTH - info.length()), 1, info);

        header->update();
        field->update();
        score->update();

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

    } while ((key = getch()) != KEY_X);

    // exit gracefully
    running = false;
    update_thread.join();

    wclear(stdscr);
    endwin();


    return 0;
}
