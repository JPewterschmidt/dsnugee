#ifndef NUGEE_BINARY_TREE_TRAVERSER
#define NUGEE_BINARY_TREE_TRAVERSER

#include "helpers.h"
#include "binary_tree_node_concepts.h"
#include "binary_tree_traverser_policies.h"

#include <iterator>
#include <stack>
#include <cassert>
#include <cstddef>

BEGIN_NAMESPACE_DSNUGEE


template<
    typename Policy, 
    is_binary_tree_node Node>
class binary_tree_traverser
{
public:
    using node_type = Node;
    using const_node_ptr = const node_type*;
    using policy = Policy;

public:
    class sentinel_iterator
    {
        friend class iterator;
    public:
        sentinel_iterator(const binary_tree_traverser* t = nullptr, const_node_ptr root = nullptr)
            : m_traverser{ t }, m_root{ root }
        {
        }

        auto last() noexcept
        {
            return Policy{}.last_node_by_root(m_root);
        }

    private:
        const binary_tree_traverser* m_traverser;
        const_node_ptr m_root; 
        const_node_ptr m_last{};
    };

    class iterator
    {
    public:
        using value_type = typename Node::value_type;
        using difference_type = long;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = ::std::bidirectional_iterator_tag;

        using policy = binary_tree_traverser::policy;

    public:
        iterator(const binary_tree_traverser* t = nullptr, const_node_ptr node = nullptr) noexcept
            : m_traverser{ t }, m_cur{ node }
        {
        }
         
        iterator(sentinel_iterator si)
            : m_traverser{ si.m_traverser }, m_cur{ nullptr }
        {

        }

        iterator& operator = (sentinel_iterator si) noexcept
        {
            m_cur = nullptr;
            return *this;
        }

        iterator(iterator&& other) noexcept = default;
        iterator(const iterator&) noexcept = default;
        iterator& operator = (iterator&& other) noexcept = default;
        iterator& operator = (const iterator& other) noexcept = default;

        iterator& operator ++() noexcept
        {
            m_cur = m_policy.next(m_cur);
            return *this;
        }

        iterator operator ++(int) noexcept
        {
            iterator result{ *this };
            operator++();
            return result;
        }

        iterator& operator --() noexcept
        {
            if (m_cur == nullptr)
            {
                m_cur = m_traverser->sentinel().last();
                return *this;
            }

            m_cur = m_policy.prev(m_cur);
            return *this;
        }

        iterator operator --(int) noexcept
        {
            iterator result{ *this };
            operator --();
            return result;
        }

        friend bool operator == (
            const iterator& lhs, const iterator& rhs) noexcept
        {
            return lhs.m_cur == rhs.m_cur;
        }

        friend bool operator != (
            const iterator& lhs, const iterator& rhs) noexcept
        {
            return !operator == (lhs, rhs);
        }

        friend bool operator == (
            const sentinel_iterator& e, const iterator& rhs) noexcept
        {
            return rhs.m_cur == nullptr;
        }

        friend bool operator != (
            const sentinel_iterator& e, const iterator& rhs) noexcept
        {
            return !operator == (e, rhs);
        }

        friend bool operator == (
            const iterator& lhs, const sentinel_iterator&) noexcept
        {
            return lhs.m_cur == nullptr;
        }

        friend bool operator != (
            const iterator& lhs, const sentinel_iterator& e) noexcept
        {
            return !operator == (lhs, e);
        }

        reference operator*() const noexcept { return m_cur->ele(); }
        pointer operator ->() const noexcept { return &(m_cur->ele()); }

    private:
        const binary_tree_traverser* m_traverser;
        const_node_ptr m_cur{};
        policy m_policy;
    };

public:
    binary_tree_traverser(auto& tree)
        : m_root{ tree.root() }
    {
    }

    auto begin() const noexcept
    {
        return iterator{ this, Policy{}.first_node_by_root(m_root) };
    }

    auto end() const noexcept
    {
        return iterator{ this, nullptr };
    }

    auto sentinel() const noexcept
    {
        return sentinel_iterator{ this, m_root };
    }
    
private:
    const_node_ptr m_root;
};

template<typename T>
using root_first_traverser = 
binary_tree_traverser<
    root_first<typename binary_tree<T>::node_type>, 
    typename binary_tree<T>::node_type
>;

template<typename T>
using root_last_traverser = 
binary_tree_traverser<
    root_last<typename binary_tree<T>::node_type>, 
    typename binary_tree<T>::node_type
>;

END_NAMESPACE_DSNUGEE

#endif
