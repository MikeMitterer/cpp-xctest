#include <iostream>
#include "NewCppClass.h"

int main() {
    std::cout << "Hello, Lib!" << std::endl;

    NewCppClass newCppClass("Mike");

    newCppClass.showName();

    return 0;
}