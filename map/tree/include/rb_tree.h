#ifndef   RB_TREE_
# define  RB_TREE_

# include <functional>        // For std::less
# include <bits/c++config.h>  // For std::size_t

// # include "rb_tree_iterator.h"   // For rb_tree_iterator, rb_tree_const_iterator
# include "rb_tree_node.h"       // For rb_tree_node
# include "rb_tree_node_base.h"  // For rb_tree_node_base, rb_tree_node_color

namespace cxx {

  /// @brief Red-Black Tree implementation.
  /// This template class provides the structure and functionality for a Red-Black Tree,
  /// a self-balancing binary search tree. It ensures that the tree remains approximately
  /// balanced during insertions and deletions, providing efficient search, insertion,
  /// and deletion operations with O(log n) complexity.
  /// @tparam Val The type of elements stored in the tree. Typically, a value type like `std::pair<const Key, T>` for associative containers.
  /// @tparam Compare A binary predicate that defines the ordering of elements. It should return `true` if the first argument is considered to go before the second. Typically, `std::less<Key>`.

  template<typename Val, typename Compare = std::less<Val>>
  class rb_tree {
    public:
      using value_type      =       Val        ;
      using key_compare     =       Compare    ;
      using pointer         =       value_type*;
      using reference       =       value_type&;
      using const_pointer   = const value_type*;
      using const_reference = const value_type&;
      using size_type       =       std::size_t;

    private:
      using _node_type      =       rb_tree_node<Val>        ;
      using _base_type      =       rb_tree_node_base        ;
      using _color          =       rb_tree_node_base::_color;
      using _node_ptr       =       rb_tree_node<Val>*       ;
      using _const_node_ptr = const rb_tree_node<Val>*       ;
      using _base_ptr       =       rb_tree_node_base *      ;
      using _const_base_ptr = const rb_tree_node_base *      ;


    public:
      constexpr explicit rb_tree(const key_compare& comp = key_compare())
        : m_comp{ comp }, m_size{ 0 }, m_root{ nullptr }, m_nil{ nullptr }
      {
        m_nil  = new _base_type;
        m_root = m_nil;
        m_nil->m_color  = _color::Black; // nil must be black
        m_nil->m_parent = m_root;
      }

      constexpr rb_tree(const rb_tree& _x)
        : rb_tree{ _x.m_comp }
      {
        // _copy(__x.m_root, __x.m_nil);
        m_size = _x.m_size;
      }

      constexpr rb_tree& operator=(const rb_tree& _x);

      // constexpr ~rb_tree() { _clear(m_root); }
      
    public:
      /// @brief Returns the number of elements in the tree.
      [[nodiscard]]
      constexpr size_type size() const { return m_size; }

      /// @brief Returns a pointer to the root node of the tree.
      constexpr _const_node_ptr getRoot() const { return m_root; }

      /// @brief Returns the height of the subtree rooted at the given node.
      /// @param _ptr Pointer to the root of the subtree.
      /// @return Height of the subtree.
    [[nodiscard]]
    constexpr size_type height(_const_base_ptr _ptr) const;

      /// @brief Returns the height of the entire tree.
      /// @return Height of the tree.
      [[nodiscard]]
      constexpr size_type height() const { return height(m_root); }

      /// @brief Returns a pointer to the nil (sentinel) node of the tree.
      [[nodiscard]]
      constexpr _const_base_ptr getNil() const { return m_nil; }

      /// @brief Checks if the tree is empty.
      /// @return true if the tree contains no elements, false otherwise.
      [[nodiscard]]
      constexpr bool empty() const noexcept { return m_size == 0; }

      /// @brief Creates a new node with the given value.
      /// @param value The value to store in the new node.
      /// @return Pointer to the newly created node.
      [[nodiscard]]
      constexpr _node_ptr createNode(const value_type& value) const;

      /// To Do impl _copy  helper function.
      /// To Do impl _clear helper function.
    private:
      key_compare m_comp;
      size_type   m_size;
      _node_ptr   m_root;
      _base_ptr   m_nil;

  };

} // namespace cxx

#endif // RB_TREE_
