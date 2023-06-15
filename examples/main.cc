#include "fmt/core.h"
#include "queue.h"
#include "disjoint.h"

int main()
{
    double_queue<q_policy1> q{ 5 };

    q.push_rear();
    q.push_rear();
    q.push_rear();
    q.push_rear();
    q.pop_front();

    q.get_policy().describe();
}
