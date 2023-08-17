#ifndef DSNUGEE_HELPERS
#define DSNUGEE_HELPERS

#define BEGIN_NAMESPACE_DSNUGEE namespace dsnugee {
#define END_NAMESPACE_DSNUGEE }

#include <vector>

BEGIN_NAMESPACE_DSNUGEE

template<typename T, template<typename...> typename Primary>
struct is_specialization_of_helper : ::std::false_type
{
};

template<template<typename...> typename Primary, typename... Args>
struct is_specialization_of_helper<Primary<Args...>, Primary> : ::std::true_type
{
};

template<typename T, template<typename...> typename Primary>
concept is_specialization_of = !!is_specialization_of_helper<::std::decay_t<T>, Primary>{};

std::vector<int> generate_n_prime_number(int n);

END_NAMESPACE_DSNUGEE

#endif
