#include <stdexcept>

int* FindLastElement(const int* begin, const int* end, bool(*predicate)(int)) {
    
    if (predicate == nullptr ||
        begin     == nullptr ||
        end       == nullptr || 
        std::distance(begin, end) < 0)
        return const_cast<int*>(end);
    
    for(int* it = const_cast<int*>(end - 1); it != begin - 1; --it){
        if (predicate(*it)) return it;
    }
    
    return const_cast<int*>(end);
}