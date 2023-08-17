#include "helpers.h"

BEGIN_NAMESPACE_DSNUGEE

std::vector<int> generate_n_prime_number(int n) 
{
    std::vector<bool> sieve(n + 1, true);
    sieve[0] = sieve[1] = false;

    for (int i = 2; i * i <= n; ++i) 
    {
        if (sieve[i]) 
        {
            for (int j = i * i; j <= n; j += i) 
            {
                sieve[j] = false;
            }
        }
    }

    std::vector<int> result;
    for (int i = 2; i <= n; ++i)
    {
        if (sieve[i]) 
        {
            result.push_back(i);
        }
    }

    return result;
}

END_NAMESPACE_DSNUGEE
