
template <class T>
DLClass<T>::DLClass(std::string module_name) :
    module(module_name){
    shared = std::make_shared<shared_obj>();
}

template <class T>
DLClass<T>::~DLClass() {
    //close_module();
}

template <class T>
void DLClass<T>::shared_obj::close_module() {
    if(dll_handle) {
        dlclose(dll_handle);
        dll_handle = NULL;
    }
    if(create) create = NULL;
    if(destroy) destroy = NULL;
}

template <class T>
bool DLClass<T>::shared_obj::open_module(std::string module) {
    
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
    if(!shared->create || !shared->destroy) {
        if(!shared->open_module(module)) {
            return std::shared_ptr<T>(NULL);
        }
    }

//    auto create_args = ((T* (*)(Args...))create);    
    std::shared_ptr<shared_obj> my_shared = shared;
    return std::shared_ptr<T>(shared->create(args...),
                              [my_shared](T* p){ my_shared->destroy(p); });
}


template <class T>
DLClass<T>::shared_obj::~shared_obj() {
    close_module();
}
