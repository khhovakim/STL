#ifndef   RB_TREE_ITERATOR_
# define  RB_TREE_ITERATOR_

# include <bits/c++config.h>                // For std::ptrdiff_t
# include <bits/stl_iterator_base_types.h>  // For std::bidirectional_iterator_tag

# include "rb_tree_node_base.h"  // For rb_tree_node_base
# include "rb_tree_node.h"       // For rb_tree_node

namespace cxx {
    /// @brief Iterator for red-black trees.
    /// This class provides an iterator for traversing red-black trees.
    /// It supports both read and write access to the elements of the tree.
    template<typename T>
    struct rb_tree_iterator {
    private:
        using _self                 = rb_tree_iterator;
        using _base_ptr             = rb_tree_node_base *;
        using _node_ptr             = rb_tree_node<T> *;

    public:
        using value_type = T  ;
        using reference  = T &;
        using pointer    = T *;

        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        /// @brief Default constructor.
        /// Initializes the iterator with a null node pointer.
        constexpr
        rb_tree_iterator()
            : m_node{nullptr}, m_nil{nullptr} {
        }

        /// @brief Constructor with a base pointer.
        /// Initializes the iterator with the given base pointer.
        /// @param _x   Pointer to the base node.
        /// @param _nil Pointer to the nil  node.
        constexpr explicit
        rb_tree_iterator(_node_ptr _x, const _base_ptr const _nil)
            : m_node{_x}, m_nil{_nil} {
        }

        /// @brief Dereference operator.
        /// Returns a reference to the value stored in the node pointed to by the iterator.
        /// @return Reference to the value.
        constexpr reference
        operator*() const noexcept { return static_cast<_node_ptr>(m_node)->m_valueField; }

        /// @brief Arrow operator.
        /// Returns a pointer to the value stored in the node pointed to by the iterator.
        /// @return Pointer to the value.
        constexpr pointer
        operator->() const noexcept { return &static_cast<_node_ptr>(m_node)->m_valueField; }

        /// @brief Pre-increment operator.
        /// Moves the iterator to the next node in the tree.
        /// @return Reference to the updated iterator.
        constexpr _self &
        operator++() {
            m_node = rb_tree_node_base::_next(m_node, m_nil);
            return *this;
        }

        /// @brief Post-increment operator.
        /// Moves the iterator to the next node in the tree and returns a copy of the original iterator.
        /// @return Copy of the original iterator.
        constexpr _self
        operator++(int) {
            _self _tmp = *this; // Create a copy of the current iterator
            m_node = rb_tree_node_base::_next(m_node, m_nil); // Move to the next node
            return _tmp; // Return the copy
        }

        /// @brief Pre-decrement operator.
        /// Moves the iterator to the previous node in the tree.
        /// @return Reference to the updated iterator.
        constexpr _self &
        operator--() {
            m_node = rb_tree_node_base::_prev(m_node, m_nil);
            return *this;
        }

        /// @brief Post-decrement operator.
        /// Moves the iterator to the previous node in the tree and returns a copy of the original iterator.
        /// @return Copy of the original iterator.
        constexpr _self
        operator--(int) {
            _self _tmp = *this; // Create a copy of the current iterator
            m_node = rb_tree_node_base::_prev(m_node, m_nil); // Move to the previous node
            return _tmp; // Return the copy
        }

        /// @brief Equality operator.
        /// Compares two iterators for equality.
        /// @param _x The other iterator to compare with.
        /// @return True if both iterators point to the same node, false otherwise.
        constexpr bool
        operator==(const _self &_x) const { return m_node == _x.m_node; }

        /// @brief Inequality operator.
        /// Compares two iterators for inequality.
        /// @param _x The other iterator to compare with.
        /// @return True if the iterators point to different nodes, false otherwise.
        constexpr bool
        operator!=(const _self &_x) const { return m_node != _x.m_node; }

        _base_ptr m_node;            ///< Pointer to the current node in the tree.
        const _base_ptr const m_nil; ///< Pointer to the nil in the tree.
    };
} // namespace cxx

namespace cxx {
    /// @brief Const iterator for red-black trees.
    /// This class provides a const iterator for traversing red-black trees.
    /// It supports read-only access to the elements of the tree.
    template<typename T>
    struct rb_tree_const_iterator {
    private:
        using _iterator       = rb_tree_iterator<T>;
        using _self           = rb_tree_const_iterator;
        using _base_ptr       = const rb_tree_node_base *;
        using _node_ptr       = const rb_tree_node<T> *;

    public:
        using value_type = T;
        using reference  = const T &;
        using pointer    = const T *;

        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        /// @brief Default constructor.
        /// Initializes the const iterator with a null node pointer.
        constexpr
        rb_tree_const_iterator()
            : m_node{nullptr}, m_nil{nullptr} {
        }

        /// @brief Constructor with a base pointer.
        /// Initializes the const iterator with the given base pointer.
        /// @param _x Pointer to the base node.
        /// @param _nil Pointer to the nil  node.
        constexpr explicit
        rb_tree_const_iterator(_node_ptr _x, _base_ptr const _nil)
            : m_node{_x}, m_nil {_nil} {
        }

        /// @brief Copy constructor from a non-const iterator.
        /// Initializes the const iterator with a non-const iterator.
        /// @param _x The non-const iterator to copy from.
        constexpr explicit
        rb_tree_const_iterator(const _iterator& _x)
            : m_node{_x.m_node}, m_nil{_x.m_nil} {
        }

        /// @brief Dereference operator.
        /// Returns a reference to the value stored in the node pointed to by the const iterator.
        /// @return Reference to the value.
        constexpr reference
        operator*() const noexcept { return static_cast<_node_ptr>(m_node)->m_valueField; }

        /// @brief Arrow operator.
        /// Returns a pointer to the value stored in the node pointed to by the const iterator.
        /// @return Pointer to the value.
        constexpr pointer
        operator->() const noexcept { return &static_cast<_node_ptr>(m_node)->m_valueField; }

        /// @brief Pre-increment operator.
        /// Moves the const iterator to the next node in the tree.
        /// @return Reference to the updated const iterator.
        constexpr _self &
        operator++() {
            m_node = rb_tree_node_base::_next(m_node, m_nil);
            return *this;
        }

        /// @brief Post-increment operator.
        /// Moves the const iterator to the next node in the tree and returns a copy of the original const iterator.
        /// @return Copy of the original const iterator.
        constexpr _self
        operator++(int) {
            _self _tmp = *this; // Create a copy of the current const iterator
            m_node = rb_tree_node_base::_next(m_node, m_nil); // Move to the next node
            return _tmp; // Return the copy
        }

        /// @brief Pre-decrement operator.
        /// Moves the const iterator to the previous node in the tree.
        /// @return Reference to the updated const iterator.
        constexpr _self &
        operator--() {
            m_node = rb_tree_node_base::_prev(m_node, m_nil);
            return *this;
        }

        /// @brief Post-decrement operator.
        /// Moves the const iterator to the previous node in the tree and returns a copy of the original const iterator.
        /// @return Copy of the original const iterator.
        constexpr _self
        operator--(int) {
            _self _tmp = *this; // Create a copy of the current const iterator
            m_node = rb_tree_node_base::_prev(m_node, m_nil); // Move to the previous node
            return _tmp; // Return the copy
        }

        /// @brief Equality operator.
        /// Compares two const iterators for equality.
        /// @param _x The other const iterator to compare with.
        /// @return True if both const iterators point to the same node, false otherwise.
        constexpr bool
        operator==(const _self &_x) const { return m_node == _x.m_node; }

        /// @brief Inequality operator.
        /// Compares two const iterators for inequality.
        /// @param _x The other const iterator to compare with.
        /// @return True if the const iterators point to different nodes, false otherwise.
        constexpr bool
        operator!=(const _self &_x) const { return m_node != _x.m_node; }

        _base_ptr m_node;      ///< Pointer to the current node in the tree.
        _base_ptr const m_nil; ///< Pointer to the nil node in the tree.
    };
} // namespace cxx

#endif // RB_TREE_ITERATOR_
