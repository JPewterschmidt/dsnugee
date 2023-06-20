#ifndef DSNUGEE_GENERALIZED_TABLE
#define DSNUGEE_GENERALIZED_TABLE

#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

template<size_t... I>
auto tail_impl(
    is_specialization_of<::std::tuple> auto const& tt, 
    ::std::integer_sequence<size_t, I...> is)
{
    return ::std::make_tuple(std::get<I + 1>(tt)...);
}

template<typename... Args>
auto tail(const ::std::tuple<Args...>& tt)
{
    return tail_impl( 
        tt, 
        ::std::make_integer_sequence< 
            size_t, 
            ::std::tuple_size_v<::std::tuple<Args...>> - 1
        >{}
    );
}

auto head(is_specialization_of<::std::tuple> auto const& tt)
{
    return get<1>(tt);
}

END_NAMESPACE_DSNUGEE

#endif
