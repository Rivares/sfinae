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



// ------------------------------------------------------------------------------------------------------------

// ----------------------------- TASK -------------------------------






// --------------------------- INTEGER ------------------------------

/// <summary>
/// Example of implementation function for print ip address
/// </summary>
/// /// <param name="value">INTEGER</param>
template <typename T>
std::enable_if_t<std::is_integral<T>::value> print_ip(T value)
{
    auto* begin = reinterpret_cast<uint8_t*>(&value) + sizeof(T) - 1;
    auto* end = begin - sizeof(T);

    for (auto* byte = begin; byte > end; --byte)//: std::ranges::subrange{begin, end} | std::views::reverse)
    {
        std::cout << static_cast<int>(*byte);

        if ((byte - 1) > end)
        {   std::cout << '.';  }
    };

    std::cout << '\n';
}




// --------------------------- STRING ------------------------------

/// <summary>
/// Definition for std::string
/// </summary>

template <typename T>
struct is_string
{
    static const bool value = false;
};

template <>
struct is_string<std::string>
{
    static const bool value = true;
};


/// <summary>
/// Example of implementation function for print ip address
/// </summary>
/// /// <param name="value">STRING</param>
template <typename T>
std::enable_if_t<is_string<T>::value> print_ip(T value)
{
    std::cout << value;

    std::cout << '\n';
}





// --------------------------- CONTAINER (SEQUENCE) ------------------------------

/// <summary>
/// Definition for std::string
/// </summary>
template <typename T>
struct is_container: std::false_type {};

// partial specializations for vector
template <typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>>: std::true_type {};

// partial specializations for list
template <typename T, typename Alloc>
struct is_container<std::list<T, Alloc>>: std::true_type {};


template <class Container, class T = std::enable_if_t<is_container<Container>::value>>
std::ostream& operator<<(std::ostream& os, const Container& container)
{
    if (!container.empty())
    {
        std::cout << *container.begin();
        std::for_each(std::next(container.begin()), container.end(), [] (auto& value) {
            std::cout << "." << value;
            });
    }

    return os;
}


/// <summary>
/// Example of implementation function for print ip address
/// </summary>
/// /// <param name="value">CONTAINER</param>
template <typename T>
std::enable_if_t<is_container<T>::value> print_ip(T value)
{
    std::cout << value;

    std::cout << '\n';
}






// --------------------------- TUPLE ------------------------------



/// <summary>
/// Definition for std::tuple
/// </summary>



// specializations for initializer_list
template <typename T>
struct is_initializer_list: std::false_type {};

// partial specializations for initializer_list
template <typename T>
struct is_initializer_list<std::initializer_list<T>>: std::true_type {};



/// <summary>
/// Example of implementation function for print ip address
/// </summary>
/// /// <param name="value">initializer_list</param>
template <typename T>
std::enable_if_t<is_initializer_list<T>::value> print_ip(T container)
{
    if (container.size() > 0)
    {
        std::cout << *container.begin();
        std::for_each(std::next(container.begin()), container.end(), [] (auto& value)
        {
            std::cout << "." << value;
        });
    }

    std::cout << '\n';
}



// specializations for tuple
template <typename T>
struct is_tuple: std::false_type {};

// partial specializations for tuple
template <typename T, typename Alloc>
struct is_tuple<std::tuple<T, Alloc>>: std::true_type {};


template <typename T, typename ... Rest>
inline constexpr bool one_type = (std::is_same_v<T, Rest> && ...);


/// <summary>
/// Example of implementation function for print ip address
/// </summary>
/// /// <param name="value">TUPLE</param>
template <typename TupleT, std::size_t... Is>
void printTuple(const TupleT& tp, std::index_sequence<Is...>)
{
    auto list = {std::get<Is>(tp)...};
    print_ip(list);
}

template <typename... Args>
std::enable_if_t<one_type<Args...>> print_ip(const std::tuple<Args...>& ip)
{
    printTuple(ip, std::make_index_sequence<std::tuple_size_v<std::tuple<Args...>>>{});
}


















