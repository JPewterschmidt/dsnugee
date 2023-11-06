#ifndef NUGEE_BINARY_TREE
#define NUGEE_BINARY_TREE

#include "helpers.h"
#include <concepts>
#include <memory>
#include <utility>
#include <compare>
#include <stdexcept>
#include "binary_tree_policy.h"

BEGIN_NAMESPACE_DSNUGEE

template<
    ::std::totally_ordered ElementType, 
    typename Policy = plain_bt_policy, 
    typename Alloc = ::std::allocator<int>>
class binary_tree
{
public:
    using allocator_type    = Alloc;
    using value_type        = ElementType;
    using size_type         = ::std::size_t;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using pointer           = typename ::std::allocator_traits<Alloc>::pointer;
    using policy            = Policy;

private:
    class bt_node
    {
    public:
        using value_type = ElementType;

    public:
        template<typename... Args>
        bt_node(binary_tree& tree, Args&&... args)
            : m_tree{ tree }, 
              m_ele{ tree.make_element(::std::forward<Args>(args)...) }
        {
        }

        bt_node(binary_tree& tree) noexcept
            : m_tree{ tree }
        {
        }

        ~bt_node() noexcept
        {
            if (m_ele) 
                m_tree.drop_element(m_ele);
        }

        const ElementType& ele() const 
        { 
            if (!m_ele) 
                throw ::std::logic_error{"no element"};
            return *m_ele; 
        }

        binary_tree& m_tree;
        ElementType* m_ele{};
        bt_node* m_parent{};
        bt_node* m_left{};
        bt_node* m_right{};
        bool m_left_is_thread{};
        bool m_right_is_thread{};

        bool is_left_child() const noexcept
        {
            if (!m_parent) return false;
            return parent()->left() == this;
        }

        bool is_right_child() const noexcept
        {
            if (!m_parent) return false;
            return parent()->right() == this;
        }

        const bt_node* right_most_leaf() const noexcept
        {
            const bt_node* cur{ this }, *result{};
            while (cur) result = ::std::exchange(cur, cur->right());
            return result;
        }

        const bt_node* left_most_leaf() const noexcept
        {
            const bt_node* cur{ this }, *result{};
            while (cur) result = ::std::exchange(cur, cur->left());
            return result;
        }

        bool has_child() const noexcept { return left() || right(); }
        bool is_leaf() const noexcept { return !has_child(); }
        const bt_node* left()   const noexcept { return m_left; }
        const bt_node* right()  const noexcept { return m_right; }
        const bt_node* parent() const noexcept { return m_parent; }
        void set_left(bt_node* n)   noexcept { m_left = n; m_left_is_thread = false; }
        void set_right(bt_node* n)  noexcept { m_right = n; m_right_is_thread = false; }
        void set_parent(bt_node* n) noexcept { m_parent = n; }
    };

    friend ::std::partial_ordering operator<=>(
        const binary_tree::bt_node& lhs, const binary_tree::bt_node& rhs)
    {
        if (!lhs.m_ele || !rhs.m_ele)
            return ::std::partial_ordering::unordered;

        return *lhs.m_ele <=> *rhs.m_ele;
    }

    template<typename, is_binary_tree_node> 
    friend class binary_tree_traverser;

public:
    using node_type = bt_node;

    template<typename... Args>
    const_reference emplace(Args&&... args)
    {
        return insert(make_node(::std::forward<Args>(args)...));
    }

    const_reference insert(value_type val)
    {
        return insert(make_node(::std::move(val)));
    }

    ~binary_tree() noexcept
    {
        drop_sub_tree(m_root);
    }

    friend bool operator==(const binary_tree& lhs, const binary_tree& rhs) noexcept
    {
        return &lhs == &rhs;
    }

private:
    const_reference insert(bt_node* node) noexcept
    {
        auto* parent_pointer = m_policy.find_parent(m_root, node);
        if (parent_pointer == nullptr) 
        {
            m_root = node;
        }
        else
        {
            auto* parent = const_cast<bt_node*>(parent_pointer);
            m_policy.insert_as_child(parent, node);
        }
        return node->ele();
    }

    template<typename... Args>
    ElementType* make_element(Args... args)
    {
        auto* tmp = allocator_type{}.allocate(1);
        new (tmp) ElementType(::std::forward<Args>(args)...);
        return tmp;
    }

    void drop_element(ElementType* ele)
    {
        ele->~ElementType();
        allocator_type{}.deallocate(ele, 1);
    }
    
    template<typename... EleArgs>
    bt_node* make_node(EleArgs&&... args)
    {
        return new bt_node(*this, ::std::forward<ElementType>(args)...);
    }

    void drop_node(bt_node* node) noexcept
    {
        delete node;
    }

    auto& root() noexcept { return m_root; }

    void drop_sub_tree(bt_node* sub_root) noexcept
    {
        bt_node* left = sub_root->m_left;
        bt_node* right = sub_root->m_right;
        
        if (left) drop_sub_tree(left);
        if (right) drop_sub_tree(right);
        
        drop_node(sub_root);
    }

private:
    bt_node* m_root{};
    policy m_policy{};
};

END_NAMESPACE_DSNUGEE

#endif
