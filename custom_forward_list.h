#ifndef CUSTOM_FORWARD_LIST_H
#define CUSTOM_FORWARD_LIST_H

#include <cstddef>
#include <iterator>

template<typename T>
class custom_forward_list {

    struct list_node {
        T object;
        list_node* next = nullptr;
    };

    using node_ptr = list_node*;

public:

    class iterator : public std::iterator<
            std::forward_iterator_tag, T> {

        using value_type = T;
        using pointer_type = T*;
        using reference_type = T&;

        iterator(node_ptr node) : _current_node(node){
        }
        iterator operator++() {
            iterator tmp = *this;
            _current_node = _current_node->next;
            return tmp;
        }
        iterator operator++(int) {
            _current_node = _current_node->next;
            return *this;
        }
        T& operator*() {
            return _current_node->object;
        }
        T* operator->() {
            return &_current_node->object;
        }
        bool operator==(const iterator& rhs) {
            return _current_node == rhs._current_node;
        }
        bool operator!=(const iterator& rhs) {
            return  _current_node != rhs._current_node;
        }
    private:
        node_ptr _current_node;
    };

    custom_forward_list() :_size(0)  {
        list_node tmp = new list_node();
        _begin = tmp;
        _end = tmp;
    }

    void push_front(const T& value) {

    }

    bool empty() const {

    }

private:
    node_ptr _begin;
    node_ptr _end;
    std::size_t _size;
};

#endif // CUSTOM_FORWARD_LIST_H
