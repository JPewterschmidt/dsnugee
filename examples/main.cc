#include "fmt/format.h"
#include "fmt/core.h"
#include "queue.h"
#include "disjoint.h"
#include "fmt/ranges.h"

int main()
{
    double_queue<q_policy2> q{ 5 };
    const auto& policy = q.get_policy();
    for (int i = 0; i < 10; ++i)
    {
    }
}
