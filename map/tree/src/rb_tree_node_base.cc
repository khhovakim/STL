#include "rb_tree_node_base.h"

namespace cxx {

  constexpr rb_tree_node_base*
  rb_tree_node_base::_next(rb_tree_node_base* __x) noexcept
  {
    if ( __x == nullptr ) {
      return nullptr;
    }
    
    if ( __x->m_right ) {
      return _minimum(__x->m_right);
    }
    
    _base_ptr __y = __x->m_parent;
    while ( __y && __x == __y->m_right ) {
      __x = __y;
      __y = __y->m_parent;
    }
    return __y;
  }

  constexpr rb_tree_node_base*
  rb_tree_node_base::_prev(rb_tree_node_base* __x) noexcept
  {
    if ( __x == nullptr ) {
      return nullptr;
    }
    
    if ( __x->m_left ) {
      return _maximum(__x->m_left);
    }
    
    _base_ptr __y = __x->m_parent;
    while ( __y && __x == __y->m_left ) {
      __x = __y;
      __y = __y->m_parent;
    }
    return __y;
  }

  constexpr rb_tree_node_base*
  rb_tree_node_base::_minimum(rb_tree_node_base* __x) noexcept
  {
    while ( __x && __x->m_left ) {
      __x = __x->m_left;
    }
    return __x;
  }

  constexpr rb_tree_node_base*
  rb_tree_node_base::_maximum(rb_tree_node_base* __x) noexcept
  {
    while ( __x && __x->m_right ) {
      __x = __x->m_right;
    }
    return __x;
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_minimum(const rb_tree_node_base* __x) noexcept
  {
    return _minimum(const_cast<rb_tree_node_base*>(__x));
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_maximum(const rb_tree_node_base* __x) noexcept
  {
    return _maximum(const_cast<rb_tree_node_base*>(__x));
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_next(const rb_tree_node_base* __x) noexcept
  {
    return _next(const_cast<rb_tree_node_base*>(__x));
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_prev(const rb_tree_node_base* __x) noexcept
  {
    return _prev(const_cast<rb_tree_node_base*>(__x));
  }

}