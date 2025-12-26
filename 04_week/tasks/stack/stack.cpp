#include <vector>
#include<algorithm>

class Stack {
public:
    void Push(const int& num);
    bool Pop();
    
    int& Top();
    int Top() const;
    
    int Size() const;
    void Clear();
    bool Empty() const;

    void Swap(Stack& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

private:
    friend void SwapVecs(std::vector<int>& v1, std::vector<int>& v2, size_t min_size);
    
    std::vector<int> stack;
};

void Stack::Push(const int& num) {
    stack.push_back(num);
}

bool Stack::Pop() {
    if (stack.size() != 0) {
        stack.pop_back();
        return true;
    }
    return false;
}

int& Stack::Top() {
    if (stack.size() != 0) return stack[stack.size() - 1];
    else {
        int trash = std::rand();
        int& ref_trash = trash;
        return ref_trash;
    }
}

int Stack::Top() const {
    if (stack.size() != 0) return stack[stack.size() - 1];
    else {
        int trash = std::rand();
        int& ref_trash = trash;
        return ref_trash;
    }
}

void Stack::Clear() {
    stack.resize(0);
    stack.shrink_to_fit();
}

int Stack::Size() const {
    return stack.size();
}

void SwapVecs(std::vector<int>& v1, std::vector<int>& v2, size_t min_size) {
    v2.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        std::swap(v1[i], v2[i]);
    }
    v1.resize(min_size);
    v1.shrink_to_fit();
}

void Stack::Swap(Stack& other) {
    if (this == &other) return;
    
    size_t min_size = stack.size();
    
    if (min_size >= other.stack.size()) {
        min_size = other.stack.size();
        SwapVecs(stack, other.stack, min_size);
    }
    else {
        SwapVecs(other.stack, stack, min_size);
    }
}

bool Stack::Empty() const {
    return stack.size() == 0;
}

bool Stack::operator==(const Stack& other) const {
    if (this == &other) return true;
    
    if (stack.size() != other.stack.size()) return false;
    for (size_t i = 0; i < stack.size(); ++i) {
        if (stack[i] != other.stack[i]) return false;
    }
    return true;
}

bool Stack::operator!=(const Stack& other) const {
    if (this == &other) return false;
    
    if (stack.size() != other.stack.size()) return true;
    for (size_t i = 0; i < stack.size(); ++i) {
        if (stack[i] != other.stack[i]) return true;
    }
    return false;
}



