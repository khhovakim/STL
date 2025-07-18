#include "rb_tree.h"

#include <bits/c++config.h>  // For std::size_t

#include "rb_tree_node_base.h"  // For rb_tree_node_base
#include "rb_tree_node.h"       // For rb_tree_node

namespace cxx {

  template <typename Val, typename Com>
  constexpr rb_tree<Val, Com>&
  rb_tree<Val, Com>::operator=(const rb_tree<Val, Com>& __x)
  {
    if ( this == &__x ) {
      return *this;
    }

    // _clear(m_root);
    m_comp = __x.m_comp;
    m_root = m_nil;
    // _copy(__x.m_root, __x.m_nil);
    m_size = __x.m_size;
    return *this;
  }

  template <typename Val, typename Com>
  constexpr std::size_t
  rb_tree<Val, Com>::height(const rb_tree_node_base* __ptr) const
  {
    if (__ptr == m_nil) {
      return 0;
    }

    size_type __l = height(__ptr->m_left);
    size_type __r = height(__ptr->m_right);
    return 1 + (__l > __r ? __l : __r);
  }

  template <typename Val, typename Com>
  constexpr rb_tree_node<Val>*
  rb_tree<Val, Com>::createNode(const Val& __val) const
  {
    _node_ptr __node = new _node_type{ __val };
    return __node;
  }

}
