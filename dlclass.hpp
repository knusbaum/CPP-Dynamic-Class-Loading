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

    bool open_module();
    void close_module();

    template <typename... Args>
    std::shared_ptr<T> make_obj(Args... args);
    
private:
    std::string module;
    void * dll_handle = NULL;
    
    typename T::create_t *create = NULL;
    typename T::destroy_t *destroy = NULL;

};

#include "dlclass.cpp"

#endif
