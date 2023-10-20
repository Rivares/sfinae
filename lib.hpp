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
#include <tuple>
#include <deque>
#include <list>
#include <set>
#include <map>

/// <summary>
/// Generator code
/// </summary>
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

/// <summary>
/// Example of recurive templates
/// </summary>
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

/// <summary>
/// Example of remove const cvalificator
/// </summary>
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

/// <summary>
/// Example of defination types
/// </summary>
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



////---------

/// <summary>
/// Example of SFINAE
/// </summary>

// std::enable_if (как и std::is_same)

template<bool condition, typename Type>
struct EnableIf;

template<typename Type>
struct EnableIf<true, Type>
{
    using type = Type;
};

template<typename T, typename U>
struct IsSame
{
    static constexpr bool value = false;
};

template<typename T>
struct IsSame<T, T>
{
    static constexpr bool value = true;
};



template <typename T>
typename EnableIf<!IsSame<T, int>::value, void>::type
printContainer(T container)
{
    std::cout << "Values:{ ";
    for(auto value : container)
        std::cout << value << " ";
    std::cout << "}\n";
}

//---------




/// <summary>
/// Deefination for integer
/// </summary>
template <typename T>
struct is_integer
{
    static const bool result = false;
};

template <>
struct is_integer<int8_t>
{
    static const bool result = true;
};

template <>
struct is_integer<int16_t>
{
    static const bool result = true;
};

template <>
struct is_integer<int32_t>
{
    static const bool result = true;
};

template <>
struct is_integer<int64_t>
{
    static const bool result = true;
};




/// <summary>
/// Defination for std::string
/// </summary>

template <typename T>
struct is_string
{
    static const bool result = false;
};

template <>
struct is_string<std::string>
{
    static const bool result = true;
};



/// <summary>
/// Defination for std::string
/// </summary>

//template <typename T>
//struct is_vector
//{
//    static const bool result = false;
//};

//template <>
//struct is_vector<std::vector>
//{
//    static const bool result = true;
//};

template <typename T>
struct is_container: std::false_type {};

// partial specializations for vector
template <typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>>: std::true_type {};

// partial specializations for list
template <typename T, typename Alloc>
struct is_container<std::list<T, Alloc>>: std::true_type {};

//// partial specializations for tuple
//template <typename T, typename Alloc>
//struct is_container<std::tuple<T, Alloc>>: std::true_type {};

// partial specializations for tuple
template <>
struct is_container<std::tuple<int, int, int, int>>: std::true_type {};



/// <summary>
/// Example of implenetaion function for print from tuple
/// </summary>
/// /// <param name="value">Input value.</param>
template<class Container, typename... Args>
void printer(const Container& container, Args ... args)
{
    (std::cout << ... << std::get<args>(container)) << '\n';
}

template <class Container, class T = std::enable_if_t<is_container<Container>::value>>
std::ostream& operator<<(std::ostream& os, const Container& container)
{
    if constexpr (not std::is_same_v<Container, std::tuple<int, int, int, int>>)
    {
        if (!container.empty())
        {
            std::cout << *container.begin();
            std::for_each(std::next(container.begin()), container.end(), [] (auto& value) {
                std::cout << "." << value;
                });
        }
    }
    else
    {
        if (std::tuple_size_v<Container> > 0)
        {
            printer(container);
            std::cout << std::get<0>(container);
            std::cout << "." << std::get<1>(container);
            std::cout << "." << std::get<2>(container);
            std::cout << "." << std::get<3>(container);
        }
    }

    return os;
}




/// <summary>
/// Example of implenetaion function for print ip address
/// </summary>
/// /// <param name="value">Input value.</param>
template <typename T>
void print_ip(T value)
{
    if (is_integer<T>::result) // or std::is_integral<T>::value
    {
        auto* begin = reinterpret_cast<uint8_t*>(&value) + sizeof(T) - 1;
        auto* end = begin - sizeof(T);

        for (auto* byte = begin; byte > end; --byte)//: std::ranges::subrange{begin, end} | std::views::reverse)
        {
            std::cout << static_cast<int>(*byte);

            if ((byte - 1) > end)
            {   std::cout << '.';  }
        };
    }
    else if (is_string<T>::result)
    {   std::cout << value; }
    else if (is_container<T>::value)
    {
        std::cout << value;
    }


    std::cout << '\n';
}























