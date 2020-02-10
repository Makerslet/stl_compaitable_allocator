#ifndef CUSTOM_FORWARD_LIST_H
#define CUSTOM_FORWARD_LIST_H

#include <cstddef>
#include <iterator>

template<typename T, typename Alloc = std::allocator<T>>
class custom_forward_list {

    struct list_node {
        T object;
        list_node* next = nullptr;

        list_node() {}
        list_node(const T& value) : object(value) {}
    };

    using node_ptr = list_node*;
    using node_alloc = typename std::allocator_traits<Alloc>::template rebind_alloc<list_node>;

public:

    // TODO: solve const/non const versions
    class iterator : public std::iterator<
            std::forward_iterator_tag, T> {

        using value_type = T;
        using pointer_type = T*;
        using reference_type = T&;
    public:

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

    class const_iterator : public std::iterator<
            std::forward_iterator_tag, T> {

        using value_type = const T;
        using pointer_type = const T*;
        using reference_type = const T&;
    public:

        const_iterator(node_ptr node) : _current_node(node){
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
        node_ptr tmp = create_node();
        _begin = tmp;
        _end = tmp;
    }

    T& front() {
        return static_cast<T&>(
                    const_cast<custom_forward_list<T>*>(this)->front());
    }

    const T& front() const {
        if(empty())
            throw std::range_error("custom_forward_list is epmty");

        return _begin->object;
    }

    // TODO: implement move push front
    // TODO implement emplace_push_front
    void push_front(const T& value) {
        node_ptr new_front = create_node(value);
        new_front->next = _begin;
        _begin = new_front;
        ++_size;
    }

    void pop_front() {
        if(empty())
            return;

        node_ptr tmp = _begin;
        _begin = tmp->next;

        delete_node(tmp);
        --_size;
    }

    bool empty() const {
        return _begin == _end;
    }

    std::size_t size() const {
        return _size;
    }

    iterator begin() {
        return iterator(_begin);
    }

    iterator end() {
        return  iterator(_end);
    }

    iterator cbegin() const {
        return const_iterator(_begin);
    }

    iterator cend() const {
        return  const_iterator(_end);
    }

private:
    template<typename ...Args>
    node_ptr create_node(Args&& ...args) {
        node_ptr result = _allocator.allocate(1);
        _allocator.construct(result, args...);
        return result;
    }

    void delete_node(node_ptr node) {
        _allocator.destroy(node);
        _allocator.deallocate(node, 1);
    }

private:
    node_alloc _allocator;

    node_ptr _begin;
    node_ptr _end;
    std::size_t _size;
};

#endif // CUSTOM_FORWARD_LIST_H
