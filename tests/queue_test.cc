#include "queue.h"
#include "gtest/gtest.h"

using namespace dsnugee;

TEST(queue, double_queue_policy1_positive_direction)
{
    double_queue<q_policy1> q{ 5 };
    const auto& policy = q.get_policy();

    // Corner situations covered!
    for (int i = 0; i < 10; ++i)
    {
        const size_t old_front  = policy.front();
        const size_t old_rear   = policy.rear();

        ASSERT_EQ(old_rear, q.push_rear());
        ASSERT_EQ(old_front, q.pop_front());
    }
}

TEST(queue, double_queue_policy1_negative_direction)
{
    double_queue<q_policy1> q{ 5 };
    const auto& policy = q.get_policy();
    const size_t capa = policy.capacity();

    // Corner situations covered!
    for (int i = 0; i < 10; ++i)
    {
        const size_t old_front  = policy.front();
        const size_t old_rear   = policy.rear();

        ASSERT_EQ((old_front - 1 + capa) % capa, q.push_front());
        ASSERT_EQ((old_rear - 1 + capa) % capa, q.pop_rear());
    }
}

TEST(queue, double_queue_policy2_positive_direction)
{
    double_queue<q_policy2> q{ 5 };
    const auto& policy = q.get_policy();
    const size_t capa = policy.capacity();
    for (int i = 0; i < 10; ++i)
    {
        const size_t new_rear = q.push_rear();
        const size_t new_front = q.pop_front();
        ASSERT_EQ((new_rear + 1) % capa, policy.rear());
        ASSERT_EQ((new_front), policy.front());
    }
}

TEST(queue, double_queue_policy2_negative_direction)
{
    double_queue<q_policy2> q{ 5 };
    const auto& policy = q.get_policy();
    const size_t capa = policy.capacity();
    for (int i = 0; i < 10; ++i)
    {
        const size_t new_front = q.push_front();
        const size_t new_rear = q.pop_rear();
        ASSERT_EQ((new_front - 1 + capa) % capa, policy.front());
        ASSERT_EQ((new_rear), policy.rear());
    }
}

TEST(queue, example_of_policy1)
{
    double_queue<q_policy1> q{ 5 };
    q.example_routine();
}

TEST(queue, example_of_policy2)
{
    double_queue<q_policy2> q{ 5 };
    q.example_routine();
}
