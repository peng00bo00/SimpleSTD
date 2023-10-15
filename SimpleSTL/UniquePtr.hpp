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

// exchange
template <typename T, typename U>
T exchange(T &dst, U &&val) {
    T tmp = std::move(dst);
    dst = std::forward<U>(val);

    return tmp;
}

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

    // copy constructor
    UniquePtr(UniquePtr const & that) = delete;

    // copy assignment
    UniquePtr &operator= (UniquePtr const &that) = delete;

    // move constructor
    UniquePtr(UniquePtr &&that) {
        m_p = exchange(that.m_p, nullptr);
    }

    // move assignment
    UniquePtr &operator=(UniquePtr &&that) {
        if (this != &that) [[likely]] {
            if (m_p)
                Deleter{}(m_p);
            m_p = exchange(that.m_p, nullptr);
        }
        return *this;
    }

    // get()
    T *get() const {
        return m_p;
    }

    // release()
    T *release() const {
        return exchange(m_p, nullptr);
    }

    // reset()
    void reset(T *p = nullptr) {
        if (m_p) Deleter{}(m_p);

        m_p = p;
    }

    // operators
    T &operator*() const {
        return *m_p;
    }

    T *operator->() const {
        return m_p;
    }
};

}