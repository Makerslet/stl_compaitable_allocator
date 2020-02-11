#include "allocator.h"
#include "custom_forward_list.h"
#include <map>
#include <vector>

std::size_t factorial(std::size_t value)
{
    std::size_t result = 1;

    for(std::size_t i = 1; i <= value; ++i)
        result *= i;

    return  result;
}

int main(int, char *[]) {

    std::map<std::size_t, std::size_t> default_alloc_map;
    for(std::size_t i = 0; i < 10; ++i)
        default_alloc_map[i] = factorial(i);

    std::map<std::size_t, std::size_t, std::less<int>,
            preventive_allocator<std::pair<std::size_t, std::size_t>, 10>> custom_alloc_map;
    for(std::size_t i = 0; i < 10; ++i)
        custom_alloc_map[i] = factorial(i);

    for(auto it = custom_alloc_map.begin(); it != custom_alloc_map.end(); ++it)
        std::cout << it->first << " " << it->second << std::endl;

    custom_forward_list<int> default_alloc_cfl;
    for(int i = 0; i < 10; ++i)
        default_alloc_cfl.push_front(i);

    custom_forward_list<int, preventive_allocator<int, 10>> custom_alloc_cfl;
    for(int i = 0; i < 10; ++i)
        custom_alloc_cfl.push_front(i);

    for(const int& value : custom_alloc_cfl)
        std::cout << value << std::endl;

    return 0;
}
