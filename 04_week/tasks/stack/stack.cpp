#include <vector>
#include<algorithm>

class Stack {
public:
    void Push(const int& num);
    bool Pop();
    int& Top();
    const int& Top() const;
    size_t Size() const;
    void Clear();
    bool Empty() const;
    void Swap(Stack& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

private:
    std::vector<int> stack;
};

void Stack::Push(const int& num) {
    stack.push_back(num);
}

bool Stack::Pop() {
    if (!stack.empty()) {
        stack.pop_back();
        return true;
    }
    return false;
}

int& Stack::Top() {
    return stack.back();
}

const int& Stack::Top() const {
    return stack.back();
}

void Stack::Clear() {
    stack.clear();
}

size_t Stack::Size() const {
    return stack.size();
}

void Stack::Swap(Stack& other) {
    if (this == &other) return;
    std::swap(stack, other.stack);
}

bool Stack::Empty() const {
    return stack.empty();
}

bool Stack::operator==(const Stack& other) const {
    if (this == &other) return true;
    
    if (Size() != other.Size()) return false;
    for (size_t i = 0; i < stack.size(); ++i) {
        if (stack[i] != other.stack[i]) return false;
    }
    return true;
}

bool Stack::operator!=(const Stack& other) const {
    return !(*this == other);
}



