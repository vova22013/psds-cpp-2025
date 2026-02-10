#include <stdexcept>

const char* FindLongestSubsequence(const char* begin, const char* end,
    size_t& count) {
    
    if (!begin || !end || std::distance(begin, end) <= 0) {
        count = 0;
        return nullptr;
    }
    
    auto res_ind = begin;
    size_t curr_count = 1;
    count = 1;
    
    for (auto it = begin; it != end - 1; ++it){
        if (*it == *(it + 1)) {
            ++curr_count;
            continue;
        }
        if (count < curr_count) {
            count = curr_count;
            res_ind = it - (curr_count - 1);
        }
        curr_count = 1;
    }

    if (count < curr_count) {
        count = curr_count;
        res_ind = end - curr_count;
    }

    return res_ind;
}
