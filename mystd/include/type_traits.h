#pragma once

#ifndef MYSTD_TYPE_TRAITS_H
#define MYSTD_TYPE_TRAITS_H

// This header using for get info. 

// Use standard header for type_traits
#include<type_traits>

namespace mystd
{

template<class T, T v>
struct m_integral_constant
{
    static constexpr T value = v;
};

template <bool b>
using m_bool_constant = m_integral_constant<bool, b>;

typedef m_bool_constant<true> m_true_type;
typedef m_bool_constant<false> m_false_type;

/* is pair */

// forward declaration begin
template<class T1, class T2>
struct pair;

template <class T>
struct is_pair :mystd::m_false_type {};

template<class T1, class T2>
struct is_pair<mystd::pair<T1, T2>> :mystd::m_true_type {};


} // namespace mystd
#endif
