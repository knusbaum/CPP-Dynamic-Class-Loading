C-Dynamic-Class-Loading
=======================

Playing with a class that dynamically loads classes at runtime from shared objects.

`DLClass` allows you to load shared objects at runtime and create instances of the classes inside them.

A loadable class must be subclasses of a 'base' class that is known to the loading executable, and that base class must define 
`create_t` and `destroy_t` function pointer types, which `DLClass` uses to instantiate the loaded class.
The shared object must contain implementations of the `create` and `destroy` functions, with the same type as `create_t` and `destroy_t` 
(DLClass assumes they have this type)

These functions are responsible for creating and destroying instances of the loaded class. `DLClass` returns a `std::shared_ptr<T>`
with destroy given to it as the destructor function, so it's safe to let the shared_ptr go out of scope (it'll correctly destroy the object)

Unfortunately, the instance of `DLClass` that created the object must remain alive until the objects it created are destroyed.
This is necessary, because the `DLClass` instance is responsible for maintaining the handle to the shared object file. When a `DLClass`
is destroyed, it closes the handle, and the `destroy` function pointers become invalid. If a loaded object instance tries to destroy
itself after the `DLClass` has been destroyed, it'll segfault when it tries to execute the `destroy` function.
