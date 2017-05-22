
#ifndef HELLOLIB_NEWCPPCLASS_H
#define HELLOLIB_NEWCPPCLASS_H


#include <iosfwd>
#include <string>

class NewCppClass {
private:
    const std::string name;

public:
    NewCppClass(const std::string &name) : name{name} { }

    void showName();
};


#endif //HELLOLIB_NEWCPPCLASS_H
