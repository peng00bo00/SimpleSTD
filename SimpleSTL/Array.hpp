#pragma once

#include <cstddef>
#include <stdexcept>
#include <iterator>

#define _LIBPENGCXX_THROW_OUT_OF_RANGE(__i, __n) throw std::runtime_error("out of range at index " + std::to_string(__i) + ", size " + std::to_string(__n))

#if defined(_MSC_VER)
#define _LIBPENGCXX_UNREACHABLE() __assume(0)
#elif defined(__clang__)
#define _LIBPENGCXX_UNREACHABLE() __builtin_unreachable()
#elif defined(__GNUC__)
#define _LIBPENGCXX_UNREACHABLE() __builtin_unreachable()
#else
#define _LIBPENGCXX_UNREACHABLE() do {} while (1)
#endif

namespace SimpleSTL
{

template <typename _Tp, size_t _N>
struct Array {
    using value_type             = _Tp;
    using pointer                = _Tp *;
    using const_pointer          = _Tp const *;
    using reference              = _Tp &;
    using const_reference        = _Tp const &;
    using iterator               = _Tp *;
    using const_iterator         = _Tp *;
    using reverse_iterator       = std::reverse_iterator<_Tp *>;
    using const_reverse_iterator = std::reverse_iterator<_Tp const *>;

    _Tp _M_elements[_N];

    _Tp &operator[] (size_t __i) noexcept {
        return _M_elements[__i];
    }

    _Tp const &operator[] (size_t __i) const noexcept {
        return _M_elements[__i];
    }

    _Tp &at(size_t __i) {
        if (__i >= _N) [[__unlikely__]]
            _LIBPENGCXX_THROW_OUT_OF_RANGE(__i, _N);
        
        return _M_elements[__i];
    }

    _Tp const &at(size_t __i) const {
        if (__i >= _N) [[__unlikely__]]
            _LIBPENGCXX_THROW_OUT_OF_RANGE(__i, _N);
        return _M_elements[__i];
    }

    void fill(_Tp const &__val) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        for (size_t __i = 0; __i < N; __i++) {
            _M_elements[__i] = val;
        }
    }

    void swap(Array &__that) noexcept(std::is_nothrow_swappable_v<_Tp>) {
        for (size_t __i = 0; __i < N; __i++) {
            std::swap(_M_elements[__i], __that._M_elements[__i]);
        }
    }

    _Tp &front() noexcept {
        return _M_elements[0];
    }

    _Tp const &front() const noexcept {
        return _M_elements[0];
    }

    _Tp &back() noexcept {
        return _M_elements[_N - 1];
    }

    _Tp const &back() const noexcept {
        return _M_elements[_N - 1];
    }

    static constexpr bool empty() noexcept {
        return false;
    }

    static constexpr size_t size() noexcept {
        return _N;
    }

    static constexpr size_t max_size() noexcept {
        return _N;
    }

    _Tp const *cdata() const noexcept {
        return _M_elements;
    }

    _Tp const *data() const noexcept {
        return _M_elements;
    }

    _Tp *data() noexcept {
        return _M_elements;
    }

    _Tp const *cbegin() const noexcept {
        return _M_elements;
    }

    _Tp const *cend() const noexcept {
        return _M_elements + _N;
    }

    _Tp const *begin() const noexcept {
        return _M_elements;
    }

    _Tp const *end() const noexcept {
        return _M_elements + _N;
    }

    _Tp *begin() noexcept {
        return _M_elements;
    }

    _Tp *end() noexcept {
        return _M_elements + _N;
    }

    std::reverse_iterator<_Tp const *> crbegin() const noexcept {
        return std::make_reverse_iterator(_M_elements + _N);
    }

    std::reverse_iterator<_Tp const *> crend() const noexcept {
        return std::make_reverse_iterator(_M_elements);
    }

    std::reverse_iterator<_Tp const *> rbegin() const noexcept {
        return std::make_reverse_iterator(_M_elements + _N);
    }

    std::reverse_iterator<_Tp const *> rend() const noexcept {
        return std::make_reverse_iterator(_M_elements);
    }

    std::reverse_iterator<_Tp *> rbegin() noexcept {
        return std::make_reverse_iterator(_M_elements + _N);
    }

    std::reverse_iterator<_Tp *> rend() noexcept {
        return std::make_reverse_iterator(_M_elements);
    }
};

template <typename _Tp>
struct Array<_Tp, 0> {
    using value_type             = _Tp;
    using pointer                = _Tp *;
    using const_pointer          = _Tp const *;
    using reference              = _Tp &;
    using const_reference        = _Tp const &;
    using iterator               = _Tp *;
    using const_iterator         = _Tp const *;
    using reverse_iterator       = _Tp *;
    using const_reverse_iterator = _Tp const *;

    _Tp &operator[](size_t __i) noexcept {
        _LIBPENGCXX_UNREACHABLE();
    }

    _Tp const &operator[](size_t __i) const noexcept {
        _LIBPENGCXX_UNREACHABLE();
    }

    _Tp &at(size_t __i) {
        _LIBPENGCXX_THROW_OUT_OF_RANGE(__i, 0);
    }

    _Tp const &at(size_t __i) const {
        _LIBPENGCXX_THROW_OUT_OF_RANGE(__i, 0);
    }

    void fill(_Tp const &) noexcept {
    }

    void swap(Array &) noexcept {
    }

    _Tp &front() noexcept {
        _LIBPENGCXX_UNREACHABLE();
    }

    _Tp const &front() const noexcept {
        _LIBPENGCXX_UNREACHABLE();
    }

    _Tp &back() noexcept {
        _LIBPENGCXX_UNREACHABLE();
    }

    _Tp const &back() const noexcept {
        _LIBPENGCXX_UNREACHABLE();
    }

    static constexpr bool empty() noexcept {
        return true;
    }

    static constexpr size_t size() noexcept {
        return 0;
    }

    static constexpr size_t max_size() noexcept {
        return 0;
    }

    _Tp const *cdata() const noexcept {
        return nullptr;
    }

    _Tp const *data() const noexcept {
        return nullptr;
    }

    _Tp *data() noexcept {
        return nullptr;
    }

    _Tp const *cbegin() const noexcept {
        return nullptr;
    }

    _Tp const *cend() const noexcept {
        return nullptr;
    }

    _Tp const *begin() const noexcept {
        return nullptr;
    }

    _Tp const *end() const noexcept {
        return nullptr;
    }

    _Tp *begin() noexcept {
        return nullptr;
    }

    _Tp *end() noexcept {
        return nullptr;
    }

    _Tp const *crbegin() const noexcept {
        return nullptr;
    }

    _Tp const *crend() const noexcept {
        return nullptr;
    }

    _Tp const *rbegin() const noexcept {
        return nullptr;
    }

    _Tp const *rend() const noexcept {
        return nullptr;
    }

    _Tp *rbegin() noexcept {
        return nullptr;
    }

    _Tp *rend() noexcept {
        return nullptr;
    }
};

template <class _Tp, class ..._Ts>
Array(_Tp, _Ts...) -> Array<_Tp, 1 + sizeof...(_Ts)>;

}