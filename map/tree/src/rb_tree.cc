#include "rb_tree.h"

#include <bits/c++config.h>  // For std::size_t

#include "rb_tree_node_base.h"  // For rb_tree_node_base
#include "rb_tree_node.h"       // For rb_tree_node

namespace cxx {
    template<typename Val, typename Com>
    constexpr rb_tree<Val, Com> &
    rb_tree<Val, Com>::operator=(const rb_tree<Val, Com> &_x) {
        if (this == &_x) {
            return *this;
        }

        // _clear(m_root);
        m_comp = _x.m_comp;
        m_root = m_nil;
        // _copy(__x.m_root, __x.m_nil);
        m_size = _x.m_size;
        return *this;
    }

    template<typename Val, typename Com>
    constexpr std::size_t
    rb_tree<Val, Com>::height(const rb_tree_node_base *_ptr) const {
        if (_ptr == m_nil) {
            return 0;
        }

        const size_type _l = height(_ptr->m_left);
        const size_type _r = height(_ptr->m_right);
        return 1 + (_l > _r ? _l : _r);
    }

    template<typename Val, typename Com>
    constexpr rb_tree_node<Val> *
    rb_tree<Val, Com>::createNode(const Val &_val) const {
        auto _node = new _node_type{_val};
        return _node;
    }
}
