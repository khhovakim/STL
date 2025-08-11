#include "rb_tree_node_base.h"

namespace cxx {
    constexpr rb_tree_node_base *
    rb_tree_node_base::_next(rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        if (_x->m_right != _nil) {
            return _minimum(_x->m_right, _nil);
        }

        _ptr_base _y = _x->m_parent;
        while (_x == _y->m_right) {
            _x = _y;
            _y = _y->m_parent;
        }
        return _y;
    }

    constexpr rb_tree_node_base *
    rb_tree_node_base::_prev(rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        if (_x == _nil) {
            _x = _nil->m_parent;
            return _maximum(_x, _nil);
        }

        if (_x->m_left != _nil) {
            return _maximum(_x->m_left, _nil);
        }

        _ptr_base _y = _x->m_parent;
        while (_x == _y->m_left) {
            _x = _y;
            _y = _y->m_parent;
        }
        return _y;
    }

    constexpr rb_tree_node_base *
    rb_tree_node_base::_minimum(rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        if (_x == _nil) {
            return _x;
        }

        while (_x->m_left != _nil) {
            _x = _x->m_left;
        }
        return _x;
    }

    constexpr rb_tree_node_base *
    rb_tree_node_base::_maximum(rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        if (_x == _nil) {
            return _x;
        }

        while (_x->m_right != _nil) {
            _x = _x->m_right;
        }
        return _x;
    }

    const rb_tree_node_base *
    rb_tree_node_base::_minimum(const rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        return _minimum(const_cast<rb_tree_node_base *>(_x), _nil);
    }

    const rb_tree_node_base *
    rb_tree_node_base::_maximum(const rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        return _maximum(const_cast<rb_tree_node_base *>(_x), _nil);
    }

    const rb_tree_node_base *
    rb_tree_node_base::_next(const rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        return _next(const_cast<rb_tree_node_base *>(_x), _nil);
    }

    const rb_tree_node_base *
    rb_tree_node_base::_prev(const rb_tree_node_base *_x, const rb_tree_node_base * const _nil) noexcept {
        return _prev(const_cast<rb_tree_node_base *>(_x), _nil);
    }

    void rb_tree_node_base::_resolve_red_uncle(_ptr_base _parent, _ptr_base _uncle) noexcept
    {
        _uncle->m_color  = _color::Black;
        _parent->m_color = _color::Black;
        _parent->m_parent->m_color = _color::Red;
    }

    void rb_tree_node_base::_resolve_red_parent(_ptr_base _parent) noexcept
    {
        _parent->m_color = _color::Black;
        _parent->m_parent->m_color = _color::Red;
    }
}
