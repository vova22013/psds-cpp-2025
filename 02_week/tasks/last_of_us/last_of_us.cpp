#include <stdexcept>

const int* FindLastElement(const int* begin, const int* end,
     bool(*predicate)(int)) {
    
    if (!predicate || !begin || !end || std::distance(begin, end) < 0)
        return end;
    
    for(const int* it = end - 1; it != begin - 1; --it) {
        if (predicate(*it)) return it;
    }

    return end;
}