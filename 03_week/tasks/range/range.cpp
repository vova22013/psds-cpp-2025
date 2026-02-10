#include <stdexcept>
#include <vector>

std::vector<int> Range(int from, int to, int step = 1) {
    if ((to == from) || (step <= 0 ? to > from : from > to)) 
        return std::vector<int>();
    
    size_t num = std::abs(to - from);
    size_t div = std::abs(step);
    size_t size = num / div;
    if (num % div > 0) ++size;

    std::vector<int> res(size);
    for (size_t i = 0; i < size; ++i) {
        res[i] = from + step * i;
    }
    return res;
}