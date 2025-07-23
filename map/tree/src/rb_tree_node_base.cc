#include "rb_tree_node_base.h"

namespace cxx {

  constexpr rb_tree_node_base*
  rb_tree_node_base::_next(rb_tree_node_base* _x) noexcept
  {
    if ( _x == nullptr ) {
      return nullptr;
    }
    
    if ( _x->m_right ) {
      return _minimum(_x->m_right);
    }
    
    _base_ptr _y = _x->m_parent;
    while ( _y && _x == _y->m_right ) {
      _x = _y;
      _y = _y->m_parent;
    }
    return _y;
  }

  constexpr rb_tree_node_base*
  rb_tree_node_base::_prev(rb_tree_node_base* _x) noexcept
  {
    if ( _x == nullptr ) {
      return nullptr;
    }
    
    if ( _x->m_left ) {
      return _maximum(_x->m_left);
    }
    
    _base_ptr _y = _x->m_parent;
    while ( _y && _x == _y->m_left ) {
      _x = _y;
      _y = _y->m_parent;
    }
    return _y;
  }

  constexpr rb_tree_node_base*
  rb_tree_node_base::_minimum(rb_tree_node_base* _x) noexcept
  {
    while ( _x && _x->m_left ) {
      _x = _x->m_left;
    }
    return _x;
  }

  constexpr rb_tree_node_base*
  rb_tree_node_base::_maximum(rb_tree_node_base* _x) noexcept
  {
    while ( _x && _x->m_right ) {
      _x = _x->m_right;
    }
    return _x;
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_minimum(const rb_tree_node_base* _x) noexcept
  {
    return _minimum(const_cast<rb_tree_node_base*>(_x));
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_maximum(const rb_tree_node_base* _x) noexcept
  {
    return _maximum(const_cast<rb_tree_node_base*>(_x));
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_next(const rb_tree_node_base* _x) noexcept
  {
    return _next(const_cast<rb_tree_node_base*>(_x));
  }

  constexpr const rb_tree_node_base*
  rb_tree_node_base::_prev(const rb_tree_node_base* _x) noexcept
  {
    return _prev(const_cast<rb_tree_node_base*>(_x));
  }

}