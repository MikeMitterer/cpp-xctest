#include <iostream>
#include <thread>
#include <curses.h>
#include "GPIO.h"

using namespace mm;

int r, c, // current row and column (upper-left is (0,0))
        nrows, // number of rows in window
        ncols; // number of columns in window


void draw(char dc) {
    move(r, c); // curses call to move cursor to row r, column c
    delch();
    insch(dc); // curses calls to replace character under cursor by dc
    refresh(); // curses call to update screen
    c++; // go to next row
    // check for need to shift right or wrap around
    if (c == ncols) {
        c = 0;
        r++;
        if (r == nrows) r = 0;
    }
}

// http://heather.cs.ucdavis.edu/~matloff/UnixAndC/CLanguage/Curses.pdf
// CPP-Version: https://github.com/Praetonus/Ncursescpp
// https://sourceforge.net/projects/ansigl/
void waitForKB(std::function<void (int ch)> onKeyPressed) {
    /*WINDOW* wnd = */initscr();
    cbreak();
    noecho();
    //nodelay(w, TRUE);
    noecho();

    nrows = 5;
    ncols = 5;

    //getmaxyx(wnd,nrows,ncols); // curses call to find size of window
    clear(); // curses call to clear screen, send cursor to position (0,0)
    refresh(); // curses call to implement all changes since last r

    int counter = 0;
    while (counter < 20) {
        int ch = getch();
        if (ch != ERR) {
            //std::cout << "K: " << c << std::endl;
            draw(ch);
            onKeyPressed(ch);
            counter++;
        }
    }

    endwin();
}

int main() {
    gpio::Board board;


    if (!board.init()) {
        printf("GPIO initialization failed!\n");
    }
    printf("RASPI is up and running\n");

    // Pin 18 / GPIO 24 muss exportiert sein (gpio export 24 in)
    gpio::Pin pinButton(24);

    // Pin 13 / GPIO 27 muss exportiert sein (gpio export 27 out)
    // Lambda-Funktion wird im Destruktor aufgerufen!
    gpio::Pin pinLed(27, [](gpio::Pin &pin) {
        pin.write(gpio::Pin::OutputState::OFF);
        printf("Turned off LED with Lambda-Function!\n");
    });

    pinLed.write(gpio::Pin::OutputState::ON);
    mm::gpio::delay(100);
    mm::gpio::delay(100);
    pinLed.write(gpio::Pin::OutputState::OFF);

    std::thread kbThread(waitForKB,([](int ch) { std::cout << ch; } ));
    kbThread.join();

    std::cout << "Hello, LED - Blink, Blink!" << std::endl;


    return 0;
}