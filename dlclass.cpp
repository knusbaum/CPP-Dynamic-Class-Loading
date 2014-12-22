
template <class T>
DLClass<T>::DLClass(std::string module_name) :
    module(module_name){}

template <class T>
DLClass<T>::~DLClass() {
    close_module();
}

template <class T>
void DLClass<T>::close_module() {
    if(dll_handle) {
        dlclose(dll_handle);
        dll_handle = NULL;
    }
    if(create) create = NULL;
    if(destroy) destroy = NULL;
}

template <class T>
bool DLClass<T>::open_module() {

    dll_handle = dlopen(module.c_str(), RTLD_LAZY);

    if(!dll_handle) {
        std::cerr << "Failed to open library: " << dlerror() << std::endl;
        return false;
    }

    // Reset errors
    dlerror();

    create = (typename T::create_t*) dlsym(dll_handle, "create");
    const char * err = dlerror();
    if(err) {
        std::cerr << "Failed to load create symbol: " << err << std::endl;
        close_module();
        return false;
    }
    
    destroy = (typename T::destroy_t*) dlsym(dll_handle, "destroy");
    err = dlerror();
    if(err) {
        std::cerr << "Failed to load destroy symbol: " << err << std::endl;
        close_module();
        return false;
    }

    return true;
}

template <class T> template< typename... Args>
std::shared_ptr<T> DLClass<T>::make_obj(Args... args) {
    if(!create || !destroy) {
        if(!open_module()) {
            return std::shared_ptr<T>(NULL);
        }
    }

//    auto create_args = ((T* (*)(Args...))create);    
    return std::shared_ptr<T>(create(args...), destroy);
}
