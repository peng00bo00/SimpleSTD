#include <cstdio>
#include <utility>
#include <concepts>

namespace SimpleSTL
{

// DefaultDeleter
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

// UniquePtr
template <typename T, typename Deleter = DefaultDeleter<T>>
struct UniquePtr {
private:
    T *m_p;

    template <typename U, typename UDeleter>
    friend struct UniquePtr;

public:
    UniquePtr(std::nullptr_t dummy = nullptr) {
        m_p = nullptr;
    }

    explicit UniquePtr(T *p) {
        m_p = p;
    }

    ~UniquePtr() {
        if (m_p) Deleter{}(m_p);
    }
};

}