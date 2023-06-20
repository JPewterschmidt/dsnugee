#ifndef DSNUGEE_GENERALIZED_TABLE
#define DSNUGEE_GENERALIZED_TABLE

#include "helpers.h"
#include <iostream>

BEGIN_NAMESPACE_DSNUGEE

template<size_t... I>
auto tail_impl(
    is_specialization_of<::std::tuple> auto&& tt, 
    ::std::integer_sequence<size_t, I...> is)
{
    return ::std::make_tuple(std::get<I + 1>(::std::forward<decltype(tt)>(tt))...);
}

auto tail(is_specialization_of<::std::tuple> auto&& tt)
{
    using tuple_type = ::std::decay_t<decltype(tt)>;
    if constexpr (::std::tuple_size<tuple_type>() == 0)
    {
        return ::std::make_tuple();
    }
    else return tail_impl( 
        ::std::forward<decltype(tt)>(tt), 
        ::std::make_integer_sequence< 
            size_t, 
            ::std::tuple_size_v<tuple_type> - 1
        >{}
    );
}

auto head(is_specialization_of<::std::tuple> auto&& tt)
{
    using tuple_type = ::std::decay_t<decltype(tt)>;
    if constexpr (::std::tuple_size<tuple_type>() != 0)
    {
        return get<1>(tt);
    }
    else return;
}

void print_tuple(is_specialization_of<::std::tuple> auto&& t)
{
    using tuple_type = ::std::decay_t<decltype(t)>;
    if constexpr (::std::tuple_size<tuple_type>() == 0)
    {
        ::std::cout << "()" << ::std::endl;
    }
    else
    {
        auto print_impl = [](auto&&... args) { 
            ((::std::cout << ", " << ::std::forward<decltype(args)>(args)), ...); 
        };

        ::std::cout << "(" << get<1>(t);
        ::std::apply(print_impl, tail(::std::forward<decltype(t)>(t)));
        ::std::cout << ")" << ::std::endl;
    }
}

END_NAMESPACE_DSNUGEE

#endif
