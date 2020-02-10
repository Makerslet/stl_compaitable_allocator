#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>
#include <memory>
#include <vector>
#include <bitset>

#define WITH_DEBUG_OUTPUT


template<typename T, std::size_t Elem>
struct preventive_allocator {

    // standard aliases
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    // user's aliases
    using chunk = pointer;

    template<typename U>
    struct rebind {
        using other = preventive_allocator<U, Elem>;
    };

    preventive_allocator() : _current(0) {
        _chunks.push_back(allocate_chunk());
    }

    ~preventive_allocator() {
        for(chunk ch : _chunks)
            deallocate_chunk(ch);
    }

    // not implemented yet
    template<typename U, std::size_t E>
    preventive_allocator(const preventive_allocator<U, E>&) {}

    T *allocate(std::size_t n) {

#ifdef WITH_DEBUG_OUTPUT
        std::cout << "allocate: [n = " << n << "]" << std::endl;
        std::cout << "chunks vector size: " << _chunks.size() << " current: " << _current << std::endl;
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        // если в чанке нет места, то выделим новый
        if(_current >= Elem) {
            _chunks.push_back(allocate_chunk());
            _current = 0;
        }

        chunk last_chunk = _chunks.back();
        std::size_t old_index = _current++;
        return last_chunk + old_index;
    }

    void deallocate(T *p, std::size_t n) {
        (void)p; (void)n;
#ifdef WITH_DEBUG_OUTPUT
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifdef WITH_DEBUG_OUTPUT
        std::cout << "construct" << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U *p) {
#ifdef WITH_DEBUG_OUTPUT
        std::cout << "destroy" << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~U();
    }

private:
    chunk allocate_chunk() {
        chunk result = reinterpret_cast<T*>(std::malloc(sizeof(T) * Elem));
        if(!result)
            throw std::bad_alloc();

        return result;
    }

    void deallocate_chunk(chunk ch) {
        std::free(ch);
    }

private:
    std::vector<chunk> _chunks;

    // индекс свободного элемента в текущем чанке
    std::size_t _current = 0;
};

#endif // ALLOCATOR_H
