#include <vector>
#include <stack>
#include <algorithm>

class Queue {
public:
    Queue();
    Queue(const std::vector<int>& input_vec);
    Queue(const std::initializer_list<int>& input_list);
    Queue(std::stack<int> input_stack);
    Queue(const size_t sizeQueue);

public:
    void Push(const int& num);
    bool Pop();

    int& Front();
    int& Back();
    const int& Front() const;
    int Back() const;

    int Size() const;
    void Clear();
    bool Empty() const;

    void Swap(Queue& other);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

private:
    void UpdateOutVecQueue();
    
    std::vector<int> m_in_vec = {};
    std::vector<int> m_out_vec = {};
};

Queue::Queue() = default;

Queue::Queue(const std::vector<int>& input_vec) : m_in_vec(input_vec) {};

Queue::Queue(const std::initializer_list<int>& input_list)
    : m_in_vec(std::vector<int>(input_list)) {
};

Queue::Queue(std::stack<int> input_stack) {
    m_in_vec.resize(input_stack.size());
    for (size_t i = m_in_vec.size(); i >= 1; --i) {
        m_in_vec[i - 1] = input_stack.top();
        input_stack.pop();
    }
};

Queue::Queue(const size_t sizeQueue) {
    m_in_vec.reserve(sizeQueue);
}

void Queue::UpdateOutVecQueue() {
    while(!m_in_vec.empty()) {
        m_out_vec.push_back(m_in_vec.back());
        m_in_vec.pop_back();
    }
    m_in_vec.shrink_to_fit();
}

void Queue::Push(const int& num) {
    m_in_vec.push_back(num);
}

bool Queue::Pop() {
    if (!m_out_vec.empty()) {
        m_out_vec.pop_back();
        return true;
    }

    UpdateOutVecQueue();
    if (m_out_vec.empty()) return false;
    m_out_vec.pop_back();
    return true;    
}

int& Queue::Front() {
    if (!m_out_vec.empty()) return m_out_vec.back();
    return m_in_vec.front();
}

const int& Queue::Front() const {
    if (!m_out_vec.empty()) return m_out_vec.back();
    return m_in_vec.front();
}

int& Queue::Back() {
    if (!m_in_vec.empty()) return m_in_vec.back();
    return m_out_vec.front();
}

int Queue::Back() const {
    if (!m_in_vec.empty()) return m_in_vec.back();
    return m_out_vec.front();
}

int Queue::Size() const {
    return m_in_vec.size() + m_out_vec.size();
}

void Queue::Swap(Queue& other) {
    if (this == &other) return;

    std::swap(m_in_vec, other.m_in_vec);
    std::swap(m_out_vec, other.m_out_vec);
}

void Queue::Clear() {
    m_in_vec.resize(0);
    m_out_vec.resize(0);
}

bool Queue::Empty() const {
    return (m_in_vec.empty() && m_out_vec.empty());
}

bool Queue::operator==(const Queue& other) const {
    if (this == &other) return true;

   if (Size() != other.Size()) return false;
    std::vector<int> queue_this(Size());
    std::vector<int> queue_other(Size());

    for (size_t i = 0; i < queue_this.size(); ++i) {
        if (i < m_out_vec.size())
            queue_this[i] = m_out_vec[m_out_vec.size() - 1 - i];
        if (i < m_in_vec.size())
            queue_this[i + m_out_vec.size()] = m_in_vec[i];
        if (i < other.m_out_vec.size())
            queue_other[i] = other.m_out_vec[other.m_out_vec.size() - 1 - i];
        if (i < other.m_in_vec.size())
            queue_other[i + other.m_out_vec.size()] = other.m_in_vec[i];
        if (queue_this[i] != queue_other[i]) return false;
    }
    return true;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}