#ifndef   RB_TREE_
# define  RB_TREE_

# include <bits/c++config.h>     // For std::size_t
# include <bits/stl_function.h>  // For std::less, std::_Select1st
# include <bits/stl_pair.h>      // For std::pair
#include "rb_tree_iterator.h"
#include "rb_tree_node.h"
#include "rb_tree_node_base.h"

namespace cxx {
    /// @brief Red-Black Tree implementation.
    /// This template class provides the structure and functionality for a Red-Black Tree,
    /// a self-balancing binary search tree. It ensures that the tree remains approximately
    /// balanced during insertions and deletions, providing efficient search, insertion,
    /// and deletion operations with O(log n) complexity.
    /// @tparam Key Key The type of keys used for ordering elements in the Red-Black Tree.
    /// @tparam Val The type of elements stored in the tree.
    ///             Typically, a value type like `std::pair<const Key, T>` for associative containers.
    /// @tparam Compare A binary predicate that defines the ordering of elements.
    ///                 It should return `true` if the first argument is considered to go before the second.
    ///                 Typically, `std::less<Key>`.

    template<
        typename Key,
        typename Val,
        typename Compare  = std::less<Key>
    >
    class rb_tree {
        using _node_type            = rb_tree_node<Val>;
        using _base_type            = rb_tree_node_base;
        using _color                = rb_tree_node_base::_color;
        using _ptr_node             = rb_tree_node<Val> *;
        using _ptr_const_node       = const rb_tree_node<Val> *;
        using _ptr_base             = rb_tree_node_base *;
        using _ptr_const_base       = const rb_tree_node_base *;
        using _const_ptr_const_base = const rb_tree_node_base * const;

    public:
        using value_type      = Val;
        using key_type        = Key;
        using key_compare     = Compare;
        using pointer         = value_type *;
        using reference       = value_type &;
        using const_pointer   = const value_type *;
        using const_reference = const value_type &;
        using size_type       = std::size_t;

        explicit rb_tree(const key_compare &comp = key_compare())
            : m_comp{comp}, m_size{0}, m_root{nullptr}, m_nil{nullptr} {
            m_nil = new _base_type;
            m_nil->m_color = _color::Black; // nil must be black
            m_nil->m_parent = m_root;
            m_root = m_nil;
        }

        rb_tree(const rb_tree &_x)
            : rb_tree{_x.m_comp} {
            _copy(_x.m_root, _x.m_nil);
            m_size = _x.m_size;
        }

        rb_tree &operator=(const rb_tree &_x);

        ~rb_tree() {
            _clear(m_root);
        }

        /// @brief Returns the number of elements in the tree.
        [[nodiscard]]
        constexpr size_type size() const {
            return m_size;
        }

        /// @brief Returns a pointer to the root node of the tree.
        constexpr _ptr_const_node getRoot() const {
            return m_root;
        }

        /// @brief Returns the height of the entire tree.
        /// @return Height of the tree.
        [[nodiscard]]
        constexpr size_type height() const {
            return _height(m_root);
        }

        /// @brief Returns a pointer to the nil (sentinel) node of the tree.
        [[nodiscard]]
        constexpr _ptr_const_base getNil() const {
            return m_nil;
        }

        /// @brief Checks if the tree is empty.
        /// @return true if the tree contains no elements, false otherwise.
        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return m_size == 0;
        }

        /// @brief Clears the entire Red-Black Tree.
        /// This function removes all elements from the tree.
        void clear() {
            _clear(m_root);
        }

        /// @brief Returns a pointer to the minimum (leftmost) node in the Red-Black Tree.
        /// @return Pointer to the node with the minimum key.
        constexpr _ptr_base min() const {
            return _base_type::_minimum(m_root, m_nil);
        }

        /// @brief Returns a pointer to the maximum (rightmost) node in the Red-Black Tree.
        /// @return Pointer to the node with the maximum key.
        constexpr _ptr_base max() const {
            return _base_type::_maximum(m_root, m_nil);
        }

        /// @brief Searches for a node with the given value in the Red-Black Tree.
        /// @param _val The value to search for (comparison is done using the key extracted from it).
        /// @return Pointer to the node containing the value, or `nullptr`/`_nil` if not found.
        constexpr _ptr_node search(const value_type &_val) const {
            return _search(m_root, m_nil, _val);
        }

        using iterator       = rb_tree_iterator<value_type>;
        using const_iterator = rb_tree_const_iterator<value_type>;

        /// @brief  Returns an iterator to the smallest element in the Red-Black Tree.
        /// @return Iterator to the beginning of the tree.
        [[nodiscard]]
        iterator begin() { return iterator{min(), m_nil}; }

        /// @brief  Returns an iterator to the end of the Red-Black Tree.
        /// @return Iterator to the past-the-end position of the tree.
        [[nodiscard]]
        iterator end()   { return iterator{m_nil, m_nil}; }

        /// @brief  Returns a const iterator to the smallest element in the Red-Black Tree.
        /// @return Const iterator to the beginning of the tree.
        [[nodiscard]]
        const_iterator begin() const { return cbegin(); }

        /// @brief  Returns a const iterator to the end of the Red-Black Tree.
        /// @return Const iterator to the past-the-end position of the tree.
        [[nodiscard]]
        const_iterator end() const { return cend(); }

        /// @brief  Returns a const iterator to the smallest element in the Red-Black Tree.
        /// @return Const iterator to the beginning of the tree.
        [[nodiscard]]
        const_iterator cbegin() const { return const_iterator{min(), m_nil}; }

        /// @brief  Returns a const iterator to the end of the Red-Black Tree.
        /// @return Const iterator to the past-the-end position of the tree.
        [[nodiscard]]
        const_iterator cend()   const { return const_iterator{m_nil, m_nil}; }

        /// @brief Inserts a value into the Red-Black Tree.
        /// @param _val The value to insert into the tree.
        /// @return A pair consisting of:
        ///   - an iterator to the inserted element (or to the existing one if insertion failed),
        ///   - a boolean indicating whether the insertion took place (`true` if inserted, `false` if already present).
        std::pair<iterator, bool> insert(const value_type &_val) {
            _ptr_node _node = new _node_type{_val};
            return _insert(_node);
        }
    private:
        /// @brief Computes the height of the subtree rooted at the given node.
        /// This internal helper function calculates the height of a subtree, defined as
        /// the number of edges on the longest path from the given node to a leaf.
        /// @param _ptr Pointer to the root of the subtree.
        /// @return The height of the subtree rooted at `_ptr`. Returns 0 if `_ptr` is null.
        [[nodiscard]]
        constexpr size_type _height(_ptr_const_base _ptr) const;
        /// @brief Recursively clears all nodes in the Red-Black Tree.
        /// This function deallocates memory and destroys all nodes in the subtree
        /// rooted at the given node. It is typically used during tree destruction
        /// or when resetting the tree.
        /// @param _node Pointer to the root of the subtree to clear.
        void _clear(_ptr_node _node);
        /// @brief Recursively copies nodes from another Red-Black Tree.
        /// This internal helper function is used to deep-copy the structure and values
        /// of another Red-Black Tree into the current tree. It clones the subtree rooted
        /// at `_node`, skipping over the sentinel `_nil` node used in Red-Black Trees.
        /// @param _node Pointer to the current node in the source tree to copy.
        /// @param _nil Sentinel node pointer used to represent leaf (null) nodes in the source tree.
        void _copy(_ptr_const_node _node, _const_ptr_const_base _nil);

        /// @brief Compares two values based on their extracted keys.
        /// @param _x The first value to compare.
        /// @param _y The second value to compare.
        /// @return `true` if the key of `_x` is less than the key of `_y`, otherwise `false`.
        bool _compare(const value_type& _x, const value_type& _y) {
            const key_type keyX = std::_Select1st<value_type>()(_x);
            const key_type keyY = std::_Select1st<value_type>()(_y);
            return m_comp(keyX, keyY);
        }

        /// @brief Recursively searches for a node with the given value starting from a specific node.
        /// @param _ptr Pointer to the current node in the subtree being searched.
        /// @param _nil Sentinel node used to represent leaf/null nodes.
        /// @param _val The value to search for (comparison is based on the key extracted from it).
        /// @return Pointer to the node containing the value, or `_nil` if not found.
        constexpr _ptr_node
        _search(_ptr_const_node _ptr, _const_ptr_const_base _nil, const value_type &_val);

        /// @brief Internal helper to insert a node into the Red-Black Tree.
        /// @param _node Pointer to the node to insert.
        /// @return A pair consisting of:
        ///   - an iterator to the inserted node (or to the existing one if a duplicate key is found),
        ///   - a boolean indicating whether the insertion was successful (`true` if inserted, `false` if duplicate).
        std::pair<iterator, bool> _insert(_ptr_node _node);

        /// @brief Restores Red-Black Tree properties after insertion.
        /// This internal function is called after inserting a node to fix any violations
        /// of Red-Black Tree properties (such as two consecutive red nodes). It performs
        /// the necessary re-coloring and rotations to maintain the tree's balance.
        /// @param _node Pointer to the newly inserted node that may violate Red-Black rules.
        void _insert_fix_up(_ptr_node _node);



        static void _right_rotate(_ptr_node _node) noexcept;
        static void _left_rotate(_ptr_node _node) noexcept;

        key_compare m_comp;
        size_type m_size;
        _ptr_node m_root;
        _ptr_base m_nil;
    };


} // namespace cxx

// Red-Black Tree implementation
namespace cxx {
    template<typename Key, typename Val, typename Compare>
    rb_tree<Key, Val, Compare> &
    rb_tree<Key, Val, Compare>::operator=(const rb_tree &_x) {
        if (this == &_x) {
            return *this;
        }

        _clear(m_root);
        m_root = m_nil;
        m_comp = _x.m_comp;
        _copy(_x.m_root, _x.m_nil);
        m_size = _x.m_size;
        return *this;
    }

    template<typename Key, typename Val, typename Compare>
    constexpr std::size_t
    rb_tree<Key, Val, Compare>::_height(const rb_tree_node_base *_ptr) const {
        if (_ptr == m_nil) {
            return 0;
        }

        const size_type _l = height(_ptr->m_left);
        const size_type _r = height(_ptr->m_right);
        return 1 + (_l > _r ? _l : _r);
    }

    template<typename Key, typename Val, typename Compare>
    void rb_tree<Key, Val, Compare>::_clear(_ptr_node _node) {
        if (_node == m_nil) {
            return ;
        }

        _clear(_node->m_left);
        _clear(_node->m_right);
        delete _node;
        --m_size;
    }

    template<typename Key, typename Val, typename Compare>
    void rb_tree<Key, Val, Compare>::
    _copy(_ptr_const_node _node, _const_ptr_const_base _nil) {
        if (_node == _nil) {
            return ;
        }

        insert(_node->m_valueField);
        _copy(_node->m_left, _nil);
        _copy(_node->m_right, _nil);
    }

    template<typename Key, typename Val, typename Compare>
    constexpr rb_tree_node<Val> *rb_tree<Key, Val, Compare>::
    _search(_ptr_const_node _ptr, _const_ptr_const_base _nil, const value_type &_val) {
        if ( _ptr == _nil ) {
            return _ptr;
        }

        if ( _compare(_ptr->m_valueField, _val) ) {
            return _search(_ptr->m_right, _nil, _val);
        }

        if ( _compare(_val, _ptr->m_valueField) ) {
            return _search(_ptr->m_left, _nil, _val);
        }

        return _ptr;
    }

    template<typename Key, typename Val, typename Compare>
    std::pair<typename rb_tree<Key, Val, Compare>::iterator, bool>
    rb_tree<Key, Val, Compare>::_insert(_ptr_node _node) {
        _ptr_node _current { m_root };
        _ptr_node _parent  { m_nil  };

        while ( _current != m_nil ) {
            _parent = _current;
            if ( !_compare(_node->m_valueField, _current->m_valueField) &&
                !_compare(_current->m_valueField, _node->m_valueField) ) {
                return std::make_pair(iterator{_current, m_nil}, false);
            }

            if ( _compare(_node->m_valueField, _current->m_valueField) ) {
                _current = _current->m_left;
            } else {
                _current = _current->m_right;
            }
        }

        _node->m_parent = _parent;
        if ( _parent == m_nil ) {
            m_root = _node;
        } else if ( _compare(_node->m_valueField, _parent->m_valueField) ) {
            _parent->m_left = _node;
        } else {
            _parent->m_right = _node;
        }

        ++m_size;
        _insert_fix_up(_node);
        return std::make_pair(iterator{_node, m_nil}, true);
    }

    template<typename Key, typename Val, typename Compare>
    void rb_tree<Key, Val, Compare>::_insert_fix_up(_ptr_node _node) {
        while ( _node->m_parent->m_color == _color::Red ) {
            if ( _node->m_parent == _node->m_parent->m_parent->m_left ) {
                _ptr_base _uncle = _node->m_parent->m_parent->m_right;
                if ( _uncle->m_color == _color::Red ) {
                    // Case 1: Uncle is red
                    _base_type::_resolve_red_uncle(_node->m_parent, _uncle);
                    _node = _node->m_parent->m_parent;
                } else {
                    if ( _node == _node->m_parent->m_right ) {
                        // Case 2: Uncle is BLACK and _node is a right child
                        _node = _node->m_parent;
                        _left_rotate(_node);
                    }
                    // Case 3: Uncle is BLACK and _node is a left child
                    _base_type::_resolve_red_parent(_node->m_parent);
                    _right_rotate(_node->m_parent->m_parent);
                }
            } else {
                _ptr_base _uncle = _node->m_parent->m_parent->m_left;
                if ( _uncle->m_color == _color::Red ) {
                    // Case 1: Uncle is red
                    _base_type::_resolve_red_uncle(_node->m_parent, _uncle);
                    _node = _node->m_parent->m_parent;
                } else {
                    if ( _node == _node->m_parent->m_left ) {
                        // Case 2: Uncle is BLACK and _node is a right child
                        _node = _node->m_parent;
                        _right_rotate(_node);
                    }
                    // Case 3: Uncle is BLACK and _node is a left child
                    _base_type::_resolve_red_parent(_node->m_parent);
                    _left_rotate(_node->m_parent->m_parent);
                }
            }
        }
        m_root->m_color = _color::Black;
    }

    template <typename Key, typename Val, typename Compare>
    void rb_tree<Key, Val, Compare>::_right_rotate(_ptr_node _node) noexcept
    {
    }

    template <typename Key, typename Val, typename Compare>
    void rb_tree<Key, Val, Compare>::_left_rotate(_ptr_node _node) noexcept
    {
    }
}

#endif // RB_TREE_
