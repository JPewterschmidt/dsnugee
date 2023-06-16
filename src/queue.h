#ifndef NUGEE_QUEUE
#define NUGEE_QUEUE

#include <vector>
#include <utility>
#include <stdexcept>
#include <string>
#include <source_location>
#include "fmt/core.h"

class q_policy1
{
public:
    explicit q_policy1(size_t size) noexcept : m_capacity{ size } { }

    bool full()     const noexcept { return actual_size() == m_capacity; }
    bool empty()    const noexcept { return m_rear == m_front; }

    size_t next_rear()      const noexcept { return (m_rear  + 1)               % (m_capacity); }
    size_t next_front()     const noexcept { return (m_front + 1)               % (m_capacity); }
    size_t previous_rear()  const noexcept { return (m_rear  - 1 + m_capacity)  % (m_capacity); }
    size_t previous_front() const noexcept { return (m_front - 1 + m_capacity)  % (m_capacity); }

    size_t increase_rear()          noexcept { return ::std::exchange(m_rear , next_rear());    }
    size_t increase_front()         noexcept { return ::std::exchange(m_front, next_front());   }
    size_t decrease_rear()          noexcept { return m_rear  = previous_rear();    }
    size_t decrease_front()         noexcept { return m_front = previous_front();   }
    size_t actual_size()      const noexcept { return m_size; }
    size_t theoratical_size() const noexcept { return (m_rear - m_front + m_capacity) % m_capacity; }

    void increase_size() noexcept { ++m_size; }
    void decrease_size() noexcept { --m_size; }

    ::std::string describe(::std::source_location location = ::std::source_location::current()) const
    {
        return fmt::format("\ninitial m_rear == m_front == 0, "
                           "\nrear = {}, front = {}, size = {}, capacity = {}, "
                           "\nfunc = {}"
                           "\n",
                           m_rear, m_front, actual_size(), m_capacity, location.function_name());
    }

    size_t front()      const noexcept { return m_front; }
    size_t rear()       const noexcept { return m_rear; }
    size_t capacity()   const noexcept { return m_capacity; }

private:
    size_t m_front{ 0 };
    size_t m_rear { 0 };
    size_t m_size{};
    size_t m_capacity;
};

class q_policy2
{
public:
    explicit q_policy2(size_t size) noexcept 
        : m_capacity{ size }
        , m_front{ (static_cast<size_t>(-1) + m_capacity) % m_capacity }
    { 
    }

    bool full()  const noexcept { return actual_size() == m_capacity; }
    bool empty() const noexcept { return m_rear == m_front + 1; }

    size_t next_rear()      const noexcept { return (m_rear  + 1)  % (m_capacity); }
    size_t next_front()     const noexcept { return (m_front + 1)  % (m_capacity); }
    size_t previous_rear()  const noexcept { return (m_rear  - 1 + m_capacity) % (m_capacity); }
    size_t previous_front() const noexcept { return (m_front - 1 + m_capacity) % (m_capacity); }

    size_t increase_rear()          noexcept { return ::std::exchange(m_rear , next_rear()); }
    size_t increase_front()         noexcept { return m_front = next_front(); }
    size_t decrease_rear()          noexcept { return m_rear  = previous_rear();    }
    size_t decrease_front()         noexcept { return ::std::exchange(m_front, previous_front());   }
    size_t actual_size()      const noexcept { return m_size; }
    size_t theoratical_size() const noexcept { return (m_rear - m_front + m_capacity) % m_capacity; }

    void increase_size() noexcept { ++m_size; }
    void decrease_size() noexcept { --m_size; }

    ::std::string describe(::std::source_location location = ::std::source_location::current()) const
    {
        return fmt::format("\ninitial m_rear == m_front + 1 == 1, "
                           "\nrear = {}, front = {}, size = {}, capacity = {}, "
                           "\nfunc = {}"
                           "\n",
                           m_rear, m_front, actual_size(), m_capacity, location.function_name());
    }

    size_t front()      const noexcept { return m_front; }
    size_t rear()       const noexcept { return m_rear; }
    size_t capacity()   const noexcept { return m_capacity; }

private:
    size_t m_capacity;
    size_t m_front;
    size_t m_rear{ 0 };
    size_t m_size{};
};

template<typename QP>
concept queue_policy = requires(QP o)
{
    { o.full()  } -> ::std::same_as<bool>;
    { o.empty() } -> ::std::same_as<bool>;
    { o.actual_size() } -> ::std::same_as<size_t>;
    { o.theoratical_size() } -> ::std::same_as<size_t>;
    { o.increase_rear() };
    { o.increase_front() };
    { o.decrease_rear() };
    { o.decrease_front() };
    { o.describe() };
    { o.next_rear()      } -> ::std::same_as<size_t>; 
    { o.next_front()     } -> ::std::same_as<size_t>; 
    { o.previous_rear()  } -> ::std::same_as<size_t>; 
    { o.previous_front() } -> ::std::same_as<size_t>; 
};

template<queue_policy QP>
class double_queue
{
public:
    double_queue(size_t num_elements)
        : s_(num_elements, 0)
    {
    }

    size_t push_rear()    
    { 
        if (policy_.actual_size() + 1 == policy_.capacity())
            throw ::std::out_of_range{ policy_.describe() };

        const size_t i = policy_.increase_rear();   

        if (auto& entry = s_[i]; entry != 0)
            throw ::std::logic_error{ policy_.describe() };
        else entry = 1;

        policy_.increase_size();
        return i; 
    }

    size_t push_front()   
    { 
        if (policy_.actual_size() + 1 == policy_.capacity())
            throw ::std::out_of_range{ policy_.describe() };

        const size_t i = policy_.decrease_front(); 

        if (auto& entry = s_[i]; entry != 0)
            throw ::std::logic_error{ policy_.describe() };
        else entry = 1;

        policy_.increase_size();
        return i;
    }

    size_t pop_rear()     
    { 
        if (policy_.actual_size() - 1 < 0)
            throw ::std::out_of_range{ policy_.describe() };

        const size_t i = policy_.decrease_rear(); 

        if (auto& entry = s_[i]; entry != 1)
            throw ::std::logic_error{ policy_.describe() };
        else entry = 0;

        policy_.decrease_size();
        return i;
    }

    size_t pop_front()    
    { 
        if (policy_.actual_size() - 1 < 0)
            throw ::std::out_of_range{ policy_.describe() };

        const size_t i = policy_.increase_front(); 

        if (auto& entry = s_[i]; entry != 1)
            throw ::std::logic_error{ policy_.describe() };
        else entry = 0;

        policy_.decrease_size();
        return i;
    }

    bool full()     const noexcept { return policy_.full(); }
    bool empty()    const noexcept { return policy_.empty(); }
    size_t size()   const noexcept { return policy_.actual_size(); }

    void clear() noexcept
    {
        s_ = ::std::vector<int>(s_.size(), 0);
        policy_ = QP{ s_.size() };
    }

    const QP& get_policy() const noexcept { return policy_; }

    void example_routine()
    {
        for (int i = 0; i < 10; ++i)
        {
            push_rear();
            pop_front();
        }

        clear();

        for (int i = 0; i < 10; ++i)
        {
            push_front();
            pop_rear();
        }
    }

private:
    ::std::vector<int> s_;
    QP policy_{ s_.size() };
};

#endif
