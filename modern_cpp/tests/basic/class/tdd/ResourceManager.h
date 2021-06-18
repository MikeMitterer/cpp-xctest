#include <utility>

#pragma once

template<class T> struct Defaulted {
    T t;
    Defaulted() = default; // DO NOT default the default CTOR
};

template<class T>
T copy_assign_value_defaulted() {
    T t;
    T const ct;
    t = ct;
    return t;
}

class ResourceCopyNotMove{
    // useful when potential race conditions need to be avoided, e.g. OS mutex replication
public:
    ResourceCopyNotMove() = default;
    ResourceCopyNotMove(std::string  _name) : name{ std::move(_name)}{};

    // enable copy
    ResourceCopyNotMove(const ResourceCopyNotMove& src) = default;
    ResourceCopyNotMove& operator=(const ResourceCopyNotMove& rhs) = default;

    // disable move
    ResourceCopyNotMove(ResourceCopyNotMove&& src) = delete;
    ResourceCopyNotMove& operator=(ResourceCopyNotMove&& rhs) = delete;

    ~ResourceCopyNotMove() = default;

    std::string name;
};

class ResourceMoveNotCopy{
    // useful when handling large data files as resource
public:
    ResourceMoveNotCopy() = default;
    ResourceMoveNotCopy(std::string  _name) : name{ std::move(_name)}{};

    // disable copy
    ResourceMoveNotCopy(const ResourceMoveNotCopy& src) = delete;
    ResourceMoveNotCopy& operator=(const ResourceMoveNotCopy& rhs) = delete;

    // enable move
    ResourceMoveNotCopy(ResourceMoveNotCopy&& src) = default;
    ResourceMoveNotCopy& operator=(ResourceMoveNotCopy&& rhs) = default;

    ~ResourceMoveNotCopy() = default;

    std::string name;
};

class ResourceDeletedAssignmentOperators{
    // useful when handling large data files as resource
public:
    ResourceDeletedAssignmentOperators() = default;
    ResourceDeletedAssignmentOperators(std::string  _name) : name{ std::move(_name)}{};

    // enable copy ctor but disable copy assignment operator
    ResourceDeletedAssignmentOperators(const ResourceDeletedAssignmentOperators& src) = default;
    ResourceDeletedAssignmentOperators& operator=(const ResourceDeletedAssignmentOperators& rhs) = delete;

    // enable move ctor but disable move assignment operator
    ResourceDeletedAssignmentOperators(ResourceDeletedAssignmentOperators&& src) = default;
    ResourceDeletedAssignmentOperators& operator=(ResourceDeletedAssignmentOperators&& rhs) = delete;

    ~ResourceDeletedAssignmentOperators() = default;

    std::string name;
};

class ParentResource{
public:
    inline static uint8_t destructorCallsCounter = 0;

    virtual std::string getMyName() {return "Mike";};

    ParentResource() = default;
    ParentResource(const ParentResource&) = default;
    ParentResource(ParentResource&&) = default;
    ParentResource& operator=(const ParentResource&) = default;
    ParentResource& operator=(ParentResource&&) = default;
    
    // make destructor virtual in the base class and generally ALWAYS
    virtual ~ParentResource() {
        std::cout << "Parent destroyed." << std::endl;
        destructorCallsCounter++;
    };

    double processDoubleOnly(double param){return param + 2.0;};
    template <typename T>
    void processDoubleOnly(T param) = delete;
};

class ChildResource : public ParentResource{
public:
    std::string getMyName() override {return "Sarah";};
    ~ChildResource(){ // make destructor virtual in the base class
        std::cout << "Child destroyed." << std::endl;
        destructorCallsCounter++;
    };
};



