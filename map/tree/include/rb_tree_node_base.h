#ifndef   RB_TREE_NODE_BASE_
# define  RB_TREE_NODE_BASE_

namespace cxx {
    /// @brief Enum class representing the color of a red-black tree node.
    /// @details This enum class defines two possible colors for nodes in a red-black tree:
    /// - `red`: Represents a red node in the tree.
    /// - `black`: Represents a black node in the tree.
    enum class rb_tree_node_color {
        Red = false, ///< Represents a red node in the tree.
        Black = true ///< Represents a black node in the tree.
    };

    /// @brief Base class for red-black tree nodes.
    /// @details This class defines the basic structure of a node in a red-black tree.
    /// It includes pointers to the parent, left child, right child, and the color of the node.
    /// This class is intended to be used as a base class for more specific node types.
    struct rb_tree_node_base {
        using _color                = rb_tree_node_color;
        using _ptr_base             = rb_tree_node_base *;
        using _ptr_const_base       = const rb_tree_node_base *;
        using _const_ptr_const_base = const rb_tree_node_base * const;

        _ptr_base m_parent{nullptr}; ///< Pointer to the parent node.
        _ptr_base m_left{nullptr}; ///< Pointer to the left child node.
        _ptr_base m_right{nullptr}; ///< Pointer to the right child node.
        _color m_color{_color::Black}; ///< Color of the node (red or black).

        /// @brief Minimum node in the subtree.
        /// @param _x Pointer to the node from which to find the minimum.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Pointer to the minimum node in the subtree rooted at `_x`.
        constexpr static _ptr_base _minimum(_ptr_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Maximum node in the subtree.
        /// @param _x Pointer to the node from which to find the maximum.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Pointer to the maximum node in the subtree rooted at `_x`.
        constexpr static _ptr_base _maximum(_ptr_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Minimum node in the subtree (const version).
        /// @param _x Const pointer to the node from which to find the minimum.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Const pointer to the minimum node in the subtree rooted at `_x`.
        static _ptr_const_base _minimum(_ptr_const_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Maximum node in the subtree (const version).
        /// @param _x Const pointer to the node from which to find the maximum.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Const pointer to the maximum node in the subtree rooted at `_x`.
        static _ptr_const_base _maximum(_ptr_const_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Get the next node in the in-order traversal.
        /// @param _x   Pointer to the current node.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Pointer to the next node in the in-order traversal.
        constexpr static _ptr_base _next(_ptr_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Get the previous node in the in-order traversal.
        /// @param _x Pointer to the current node.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Pointer to the previous node in the in-order traversal.
        constexpr static _ptr_base _prev(_ptr_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Get the next node in the in-order traversal (const version).
        /// @param _x Const pointer to the current node.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Const pointer to the next node in the in-order traversal.
        static _ptr_const_base _next(_ptr_const_base _x, _const_ptr_const_base _nil) noexcept;

        /// @brief Get the previous node in the in-order traversal (const version).
        /// @param _x Const pointer to the current node.
        /// @param _nil Sentinel node representing leaf/null in the Red-Black Tree.
        /// @return Const pointer to the previous node in the in-order traversal.
        static _ptr_const_base _prev(_ptr_const_base _x, _const_ptr_const_base _nil) noexcept;
    };
}

#endif // RB_TREE_NODE_BASE_
