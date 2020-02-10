#include "allocator.h"
#include "custom_forward_list.h"
#include <map>
#include <vector>

int main(int, char *[]) {

//     std::map<int, int, std::less<int>,
//         preventive_allocator<std::pair<const int, int>, 10>> map;

//     for (int i = 0; i < 8; ++i) {
//         map[i] = i;
//         std::cout << std::endl;
//     }


    custom_forward_list<int, preventive_allocator<int, 5>> cfl;
    for(int i = 0; i < 10; ++i)
        cfl.push_front(i);

    for(const int& value : cfl)
        std::cout << value << " " << cfl.size() << std::endl;

    while(!cfl.empty()) {
        cfl.pop_front();
        std::cout << cfl.size() << std::endl;
    }

    return 0;
}
