#include <cstdio>
#include <utility>
#include <concepts>

namespace SimpleSTL
{

template <typename T>
struct DefaultDeleter {
    void operator() (T *p) const {
        delete p;
    }
};

template <typename T>
struct DefaultDeleter<T[]> {
    void operator() (T *p) const {
        delete[] p;
    }
};

template <>
struct DefaultDeleter<FILE> {
    void operator()(FILE *p) const {
        fclose(p);
    }
};

template <typename T, typename Deleter = DefaultDeleter<T>>
struct UniquePtr {

};

}