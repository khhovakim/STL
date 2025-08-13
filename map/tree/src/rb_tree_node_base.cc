#include "rb_tree_node_base.h"

namespace cxx {
    constexpr rb_tree_node_base *
    rb_tree_node_base::_next(_base_ptr _x, const _base_ptr const _nil) noexcept {
        if (_x->m_right != _nil) {
            return _minimum(_x->m_right, _nil);
        }

        _base_ptr _y = _x->m_parent;
        while (_x == _y->m_right) {
            _x = _y;
            _y = _y->m_parent;
        }
        return _y;
    }

    constexpr rb_tree_node_base *
    rb_tree_node_base::_prev(_base_ptr _x, const _base_ptr const _nil) noexcept {
        if (_x == _nil) {
            _x = _nil->m_parent;
            return _maximum(_x, _nil);
        }

        if (_x->m_left != _nil) {
            return _maximum(_x->m_left, _nil);
        }

        _base_ptr _y = _x->m_parent;
        while (_x == _y->m_left) {
            _x = _y;
            _y = _y->m_parent;
        }
        return _y;
    }

    constexpr rb_tree_node_base *
    rb_tree_node_base::_minimum(_base_ptr _x, const _base_ptr const _nil) noexcept {
        if (_x == _nil) {
            return _x;
        }

        while (_x->m_left != _nil) {
            _x = _x->m_left;
        }
        return _x;
    }

    constexpr rb_tree_node_base *
    rb_tree_node_base::_maximum(_base_ptr _x, const _base_ptr const _nil) noexcept {
        if (_x == _nil) {
            return _x;
        }

        while (_x->m_right != _nil) {
            _x = _x->m_right;
        }
        return _x;
    }

    const rb_tree_node_base *
    rb_tree_node_base::_minimum(const _base_ptr _x, const _base_ptr const _nil) noexcept {
        return _minimum(const_cast<_base_ptr>(_x), _nil);
    }

    const rb_tree_node_base *
    rb_tree_node_base::_maximum(const _base_ptr _x, const _base_ptr const _nil) noexcept {
        return _maximum(const_cast<_base_ptr>(_x), _nil);
    }

    const rb_tree_node_base *
    rb_tree_node_base::_next(const _base_ptr _x, const _base_ptr const _nil) noexcept {
        return _next(const_cast<_base_ptr>(_x), _nil);
    }

    const rb_tree_node_base *
    rb_tree_node_base::_prev(const _base_ptr _x, const _base_ptr const _nil) noexcept {
        return _prev(const_cast<_base_ptr>(_x), _nil);
    }

    void rb_tree_node_base::_resolve_red_uncle(_base_ptr _parent, _base_ptr _uncle) noexcept
    {
        _uncle->m_color  = _color::Black;
        _parent->m_color = _color::Black;
        _parent->m_parent->m_color = _color::Red;
    }

    void rb_tree_node_base::_resolve_red_parent(_base_ptr _parent) noexcept
    {
        _parent->m_color = _color::Black;
        _parent->m_parent->m_color = _color::Red;
    }
}
