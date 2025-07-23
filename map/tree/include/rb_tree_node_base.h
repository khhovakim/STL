#ifndef   __RB_TREE_NODE_BASE__
# define  __RB_TREE_NODE_BASE__

namespace cxx {
  /// @brief Enum class representing the color of a red-black tree node.
  /// @details This enum class defines two possible colors for nodes in a red-black tree:
  /// - `red`: Represents a red node in the tree.
  /// - `black`: Represents a black node in the tree.
  enum class rb_tree_node_color {
    Red   = false, ///< Represents a red node in the tree.
    Black = true   ///< Represents a black node in the tree.
  };
  /// @brief Base class for red-black tree nodes.
  /// @details This class defines the basic structure of a node in a red-black tree.
  /// It includes pointers to the parent, left child, right child, and the color of the node.
  /// This class is intended to be used as a base class for more specific node types.
  struct rb_tree_node_base {
    using _color          =       rb_tree_node_color; ///< Type alias for the color of the node.
    using _base_ptr       =       rb_tree_node_base*; ///< Pointer to base node type.
    using _const_base_ptr = const rb_tree_node_base*; ///< Const pointer to base node type.
    
    _base_ptr     m_parent {    nullptr    }; ///< Pointer to the parent node.
    _base_ptr     m_left   {    nullptr    }; ///< Pointer to the left child node.
    _base_ptr     m_right  {    nullptr    }; ///< Pointer to the right child node.
    _color        m_color  { _color::Black }; ///< Color of the node (red or black).

    /// @brief Minimum node in the subtree.
    /// @param _x Pointer to the node from which to find the minimum.
    /// @return Pointer to the minimum node in the subtree rooted at `__x`.
    constexpr static _base_ptr
    _minimum(_base_ptr _x) noexcept;

    /// @brief Maximum node in the subtree.
    /// @param _x Pointer to the node from which to find the maximum.
    /// @return Pointer to the maximum node in the subtree rooted at `__x`.
    constexpr static _base_ptr
    _maximum(_base_ptr _x) noexcept;

    /// @brief Minimum node in the subtree (const version).
    /// @param _x Pointer to the node from which to find the minimum.
    /// @return Const pointer to the minimum node in the subtree rooted at `__x`.
    constexpr static _const_base_ptr
    _minimum(_const_base_ptr _x) noexcept;

    /// @brief Maximum node in the subtree (const version).
    /// @param _x Pointer to the node from which to find the maximum.
    /// @return Const pointer to the maximum node in the subtree rooted at `__x`.
    constexpr static _const_base_ptr
    _maximum(_const_base_ptr _x) noexcept;

    /// @brief Get the next node in the in-order traversal.
    /// @param _x Pointer to the current node.
    /// @return Pointer to the next node in the in-order traversal.
    constexpr static _base_ptr
    _next(_base_ptr _x) noexcept;

    /// @brief Get the previous node in the in-order traversal.
    /// @param _x Pointer to the current node.
    /// @return Pointer to the previous node in the in-order traversal.
    constexpr static _base_ptr
    _prev(_base_ptr _x) noexcept;

    /// @brief Get the next node in the in-order traversal (const version).
    /// @param _x Pointer to the current node.
    /// @return Const pointer to the next node in the in-order traversal.
    constexpr static _const_base_ptr
    _next(_const_base_ptr _x) noexcept;

    /// @brief Get the previous node in the in-order traversal (const version).
    /// @param _x Pointer to the current node.
    /// @return Const pointer to the previous node in the in-order traversal.
    constexpr static _const_base_ptr
    _prev(_const_base_ptr _x) noexcept;

  };

}

#endif // __RB_TREE_NODE_BASE__