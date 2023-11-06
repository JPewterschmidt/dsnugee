#include "kmp.h"

BEGIN_NAMESPACE_DSNUGEE

::std::vector<int> evaluate_next(::std::string_view pattern)
{
    size_t n = pattern.length();
    std::vector<int> next(n);
    int j = 0; // Length of the current prefix

    for (size_t i = 1; i < n; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        next[i] = j;
    }

    return next;
}

END_NAMESPACE_DSNUGEE
