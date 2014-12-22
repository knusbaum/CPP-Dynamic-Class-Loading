#ifndef DLCLASS_H
#define DLCLASS_H

#include <memory>
#include <string>
#include <dlfcn.h>
#include <iostream>

template <class T>
class DLClass {

public:
    DLClass(std::string module_name);
    ~DLClass();

    template <typename... Args>
    std::shared_ptr<T> make_obj(Args... args);
    
private:
    struct shared_obj {
        typename T::create_t *create = NULL;
        typename T::destroy_t *destroy = NULL;
        void * dll_handle = NULL;

        ~shared_obj();
        bool open_module(std::string module);
        void close_module();
    };

    std::string module;
    std::shared_ptr<shared_obj> shared;
};

#include "dlclass.cpp"

#endif
