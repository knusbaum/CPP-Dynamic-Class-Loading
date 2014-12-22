C++ Dynamic Class Loading
=======================

Playing with a class that dynamically loads classes at runtime from shared objects.

`DLClass` allows you to load shared objects at runtime and create instances of the classes inside them.

A loadable class must be subclasses of a 'base' class that is known to the loading executable, and that base class must define 
`create_t` and `destroy_t` function pointer types, which `DLClass` uses to instantiate the loaded class.
The shared object must contain implementations of the `create` and `destroy` functions, with the same type as `create_t` and `destroy_t` 
(DLClass assumes they have this type)

These functions are responsible for creating and destroying instances of the loaded class. `DLClass` returns a `std::shared_ptr<T>`
with destroy given to it as the destructor function, so it's safe to let the shared_ptr go out of scope (it'll correctly destroy the object)

The instance of `DLClass` that created the object need not remain alive until the objects it created are destroyed.
`DLClass` maintains a shared_ptr to a 'shared library' object responsible for closing the dynamic library. When a shared object handle is closed, the `destroy` function pointers become invalid. If a loaded object instance tries to destroy itself after the handle has been closed, it'll segfault when it tries to execute the `destroy` function.
Each created object also maintains a shared_ptr to the 'shared library' object implicitly through lambda capture, so only once all created objects and the `DLClass` instance have been destroyed does the 'shared library' object get destroyed. The destructor of the 'shared library' object closes the handle.

I read about loading C++ classes from shared objects [here](http://tldp.org/HOWTO/C++-dlopen/index.html)

Files
=======================

`DLClass` does the lifting. It uses the [POSIX dynamic linking API](http://pubs.opengroup.org/onlinepubs/009695399/basedefs/dlfcn.h.html) to load shared objects and get pointers to the necessary functions.

`Polygon` is the 'base class' that the executable knows about at compile-time.

`Triangle` and `Square` are classes that are made into the shared objects `triangle.so` and `square.so` and loaded by the main executable.

`main.cpp` is where you can see how to use `DLClass`. 

One cool thing about `DLClass` is that, although `make_obj` is variadic, the number and type of arguments is checked at compile-time thanks to the required typedefs in the template argument. Try passing any number of ints or other types to `DLClass<Polygon>.make_obj()`. It'll only compile with exactly one argument of type int.
