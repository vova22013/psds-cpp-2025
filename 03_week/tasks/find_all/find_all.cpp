#include <stdexcept>
#include <vector>

std::vector<size_t> FindAll(const std::vector<int>& vec, bool (*func)(int)) {
    if (vec.size() == 0 || func == nullptr) return std::vector<size_t>(0);

    std::vector<size_t> res(vec.size() / 2);
    size_t res_ind = 0;
    
    for(size_t i = 0; i < vec.size(); ++i) {
        if (res.size() == res_ind) 
            res.resize(res_ind * 2);
        
        if (func(vec[i])) {
            if (res.empty()) res.push_back(i);
            else res[res_ind] = i;
            ++res_ind; 
        }
    }
    
    res.erase(res.begin() + res_ind, res.end());
    res.shrink_to_fit();
    
    return res;
}