#pragma once

#include <cstddef>
#include <stdexcept>
#include <iterator>

namespace SimpleSTL
{

template <typename _Tp, size_t _N>
struct Array{

};

template <typename _Tp>
struct Array<_Tp, 0> {

};

}