#ifndef   __RB_TREE_NODE__
# define  __RB_TREE_NODE__

# include "rb_tree_node_base.h"

namespace cxx {

  /// @brief class representing a node in a red-black tree.
  /// @details This class inherits from `rb_tree_node_base` and adds a value field.
  /// It provides methods to access the value and manage the node's memory.
  /// The class is designed to be used as a base class for red-black tree nodes,
  /// allowing for efficient insertion, deletion, and traversal operations.
  template<typename ValueType>
  struct rb_tree_node : public rb_tree_node_base
  {
    using _node_ptr = rb_tree_node<ValueType>*; ///< Pointer type for the node.

    ValueType m_valueField { }; ///< The value stored in the node.
    
    explicit rb_tree_node(const ValueType& _val)
      : rb_tree_node_base { }, m_valueField{ _val }
    { }
  };

} // namespace cxx

#endif // __RB_TREE_NODE__