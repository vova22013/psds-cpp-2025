#include <stdexcept>
#include <vector>

using cit_t = std::vector<int>::const_iterator ;

std::pair<cit_t, cit_t> MinMax(const std::vector<int>& vec) {
    if (vec.size() == 0) return std::make_pair(vec.cend(), vec.cend());
    auto it_min = vec.cbegin();
    auto it_max = vec.cbegin();
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        if (*it_min > *it) it_min = it;
        if (*it_max <= *it) it_max = it;
    }
    return std::make_pair(it_min, it_max);
}
