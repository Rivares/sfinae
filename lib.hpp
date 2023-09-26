#pragma once

#include <functional>
#include <charconv>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>


// Generator code
template <int v>
struct off
{
    static const int b = v < 0 ? -v : v; // accept only ternary operationd and lambda
    static const int value = [](){
        if (v < 0)
        {   return -v;  }

        return v;
    }();
};
//std::cout << off<4>::b << " " << std::boolalpha << (off<1>::b == off<2>::b);  // implementation if used. This features minimizationg volume of code!

//---------

template <int num>
struct fact
{
    static const int value = num * fact<num - 1>::value;
};

template <>
struct fact<0>
{
    static const int value = 1;
};

//fact<11>::value;


//---------

template <typename T>
struct remove_const
{
    using type = T;
};

template <typename U>
struct remove_const<const U>
{
    using type = U;
};

// remove_const<int>::type a1;
// remove_const<const int>::type a2;

//---------

template <typename T>
struct is_int
{
    static const bool value = false;
};

template<>
struct is_int<int>
{
    static const bool value = true;
};

// is_int<decltype(param)>::value;


//---------

//// ?
//template <bool cond, class T, class F>
//struct cond : type_is<T>{};

//template <class T, class F>
//struct cond <false, T, F> : type_is<F>{};

////---------

//// ? SFINAE
//template <bool cond, class T>
//struct enable_if: type_is<T> {};

//template <class T>
//struct enable_if<false, T> {};

//enable_if<false, int>::type;

//---------

//    1. Адрес может быть представлен в виде произвольного целочисленного типа. Выводить
//    побайтово в беззнаковом виде, начиная со старшего байта, с символом ` . ` (символ точки)
//    в качестве разделителя. Выводятся все байты числа.
//    2. Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от
//    содержимого.
//    3. Адрес может быть представлен в виде контейнеров ` std::list `, ` std::vector `.
//    Выводится полное содержимое контейнера поэлементно и разделяется `.` (символом
//    точка). Элементы выводятся как есть.
//    4. Опционально адрес может быть представлен в виде ` std::tuple ` при условии, что все
//    типы одинаковы. Выводится полное содержимое поэлементно и разделяется `.` (одним
//    символом точка). Элементы выводятся как есть. В случа

//template <typename T>
//struct print_ip
//{
//    static const
//};
