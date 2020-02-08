#include "allocator.h"
#include <map>

int main(int, char *[]) {

     std::map<int, int, std::less<int>,
         logging_allocator<std::pair<const int, int>, 10>> map;

     for (int i = 0; i < 8; ++i) {
         map[i] = i;
         std::cout << std::endl;
     }

    return 0;
}
