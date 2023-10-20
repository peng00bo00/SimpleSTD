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
struct Array{
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
};

template <typename _Tp>
struct Array<_Tp, 0> {

};

}