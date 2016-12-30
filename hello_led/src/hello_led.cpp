#include <iostream>
#include <thread>
#include <curses.h>
#include "GPIO.h"

using namespace mm;


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

    //std::thread kbThread(waitForKB,([](int ch) { std::cout << ch; } ));
    //kbThread.join();

    std::cout << "Hello, LED - Blink, Blink!" << std::endl;


    return 0;
}