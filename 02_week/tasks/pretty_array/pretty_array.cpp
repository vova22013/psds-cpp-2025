#include <stdexcept>
#include <iostream>

void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    auto _start = begin;
    auto _end   = end;
    auto inc = 1;
    if (std::distance(begin, end) < 0) {
        inc = -1;
    }
    
    std::cout << "[";
    size_t count = 0;
    for (auto it = _start; it != _end; it += inc) {
        if (limit != 0 && count == limit) {
            std::cout << "...\n ";
            count = 1;
        }
        else ++count;
        
        std::cout << *it;
        if ((inc ==  1 && it != _end - 1) ||
            (inc == -1 && it != _end + 1)){
                std::cout << ", ";
        }
    }
    std::cout << "]\n";
}