#include "queue.h"
#include "gtest/gtest.h"

TEST(queue, double_queue_policy1_positive_direction)
{
    double_queue<q_policy1> q{ 5 };
    for (int i = 0; i < 10; ++i)
    {
        q.push_rear();
        q.pop_front();
    }
}

TEST(queue, double_queue_policy1_negative_direction)
{
    double_queue<q_policy1> q{ 5 };
    for (int i = 0; i < 10; ++i)
    {
        q.push_front();
        q.pop_rear();
    }
}
