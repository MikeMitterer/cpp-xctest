#include <iostream>
#include <stdlib.h>
#include <spdlog/spdlog.h>
#include <args.hxx>
#include <ncurses.h>
#include <menu.h>
#include <list>

namespace spd = spdlog;

//ITEM **it;
MENU *me;
//WINDOW *win;

//void quit(void) {
//    auto logger = spd::stdout_color_mt("quit");
//    //int i;
//
//    logger->info("Closing window...");
//    std::cout << "Closing window..." << std::endl;
//
//    unpost_menu(me);
//    free_menu(me);
//
////    for (i = 0; i <= 4; i++) {
////        free_item(it[i]);
////    }
//
//    //free(it);
//    delwin(win);
//    endwin();
//
//    logger->info("Done!");
//}

int main(void) {
    auto logger = spd::stdout_color_mt("main");

    int ch;

    initscr();
    atexit([] () {
        auto logger = spd::stdout_color_mt("quit");
        //int i;

        logger->info("Closing window...");
        std::cout << "Closing window..." << std::endl;

        unpost_menu(me);
        //free_menu(me);

//    for (i = 0; i <= 4; i++) {
//        free_item(it[i]);
//    }

        //free(it);
        //delwin(win);
        endwin();
        std::cout << "Done" << std::endl;

        logger->info("Done!");
    });

    clear();
    noecho();
    curs_set(0);
    cbreak();
    nl();
    keypad(stdscr, TRUE);

//    std::vector<std::shared_ptr<ITEM>> itemsX = {
//            std::shared_ptr<ITEM>(new_item("M1", "Menue-Eintrag 1"),free_item),
//            std::shared_ptr<ITEM>(new_item("M2", "Menue-Eintrag 2"),free_item),
//            std::shared_ptr<ITEM>(new_item("M3", "Menue-Eintrag 3"),free_item),
//            std::shared_ptr<ITEM>(new_item("Exit", "Exit"),free_item),
//            std::shared_ptr<ITEM>(NULL)
//
//    };
//
//    std::vector<std::unique_ptr<ITEM>> itemsY;
//    itemsY.push_back(std::unique_ptr<ITEM>(new_item("M1", "Menue-Eintrag 1")));
//    itemsY.push_back(std::unique_ptr<ITEM>(new_item("M2", "Menue-Eintrag 2")));
//    itemsY.push_back(std::unique_ptr<ITEM>(new_item("M3", "Menue-Eintrag 3")));
//    itemsY.push_back(std::unique_ptr<ITEM>(new_item("Exit", "Exit")));
//    itemsY.push_back(NULL);

    using MenuItem = std::unique_ptr<ITEM>; // ,decltype(&free_item)

    new_item("M4", "Menue-Eintrag 34");

    std::vector<MenuItem> items;
    items.push_back(MenuItem(new_item("M1", "Menue-Eintrag 1")));
    items.push_back(MenuItem(new_item("M2", "Menue-Eintrag 2")));
    items.push_back(MenuItem(new_item("M3", "Menue-Eintrag 3")));
    items.push_back(MenuItem(new_item("Exit", "Exit")));
    items.push_back(NULL);

//    it = (ITEM **) calloc(5, sizeof(ITEM *));
//    it[0] = new_item("M1", "Menueeintrag 1");
//    it[1] = new_item("M2", "Menueeintrag 2");
//    it[2] = new_item("M3", "Menueeintrag 3");
//    it[3] = new_item("Ende", "Programm beenden");
//    it[4] = 0;
    me = new_menu((ITEM **) &items[0]);

    //items.begin()
    auto win = std::unique_ptr<WINDOW,decltype(&delwin)>(newwin(8, 30, 5, 5),&delwin);
    set_menu_win(me, win.get());
    set_menu_sub(me, derwin(win.get(), 4, 28, 3, 2));
    box(win.get(), 0, 0);
    mvwaddstr(win.get(), 1, 2, "***** Testmenü *****");
    post_menu(me);

    mvaddstr(14, 3, "Programm mittels Menü oder F1-Funktionstaste beenden");

    refresh();
    wrefresh(win.get());

    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_DOWN:
                menu_driver(me, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(me, REQ_UP_ITEM);
                break;
            case 0xA: /* Return- bzw. Enter-Taste -> ASCII-Code */

                //logger->info("Current Item: {}", item_name(current_item(me)));
                mvaddstr(15, 3, (std::string("Current Item: ") + item_name(current_item(me))).c_str());
                if (item_index(current_item(me)) == 3) {
                    exit(0);
                }

            default:
                mvaddstr(16, 3, (std::string("KeyCode: ") + std::to_string(ch)).c_str());
        }

        wrefresh(win.get());
    }

    return (0);
}