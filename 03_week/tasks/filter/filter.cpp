#include <stdexcept>
#include <vector>

void Filter(std::vector<int>& vec, bool (*func)(int)) {
    if (vec.size() == 0 || func == nullptr) return;

    auto last_correct_it = vec.begin();
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        if (func(*it)) {
            std::swap(*it, *last_correct_it);
            ++last_correct_it;
        }
    }
    vec.erase(last_correct_it, vec.end());
}