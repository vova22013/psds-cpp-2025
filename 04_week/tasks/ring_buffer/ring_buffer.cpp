#include <vector>
#include <algorithm>

class RingBuffer {
public:
    RingBuffer();
    RingBuffer(const int& capacity);
    RingBuffer(const int& capacity, const int& num);
    RingBuffer(const std::initializer_list<int>& init_list);
    RingBuffer(const RingBuffer& buf);

public:
    void Push(const int& num);
    bool TryPush(const int& num);

    void Pop();
    bool TryPop(int& num);

    int Size() const;
    int Capacity() const;

    int& Front();
    int& Back();
    int Front() const;
    int Back() const;

    bool Empty() const;
    bool Full() const;

    void Clear();
    void Resize(size_t new_capacity);

    std::vector<int> Vector() const;

    int& operator[](const size_t& ind);
    int operator[](const size_t& ind) const;

    RingBuffer& operator=(const RingBuffer& other);

private:
    size_t m_size = 0;
    std::vector<int> m_buffer;
    std::vector<int>::iterator m_first_ind = m_buffer.begin();
    std::vector<int>::iterator m_last_ind = m_buffer.begin();
};

RingBuffer::RingBuffer() = default;

RingBuffer::RingBuffer(const int& capacity) {
    if (capacity <= 0) m_buffer.reserve(1);
    else m_buffer.reserve(capacity);
    m_first_ind = m_buffer.begin();
    m_last_ind = m_buffer.begin();
}

RingBuffer::RingBuffer(const int& capacity, const int& num) {
    if (capacity <= 0) m_buffer.resize(1, num);
    else m_buffer.resize(capacity, num);
    m_size = m_buffer.size();
    m_first_ind = m_buffer.begin();
    m_last_ind = m_buffer.end() - 1;
}

RingBuffer::RingBuffer(const std::initializer_list<int>& init_list)
    : m_size(init_list.size()), m_buffer(init_list) {
    if (m_size == 0) {
        m_buffer.reserve(1);
        m_last_ind = m_buffer.begin();
    }
    else m_last_ind = m_buffer.end() - 1;
    m_first_ind = m_buffer.begin();
};

RingBuffer::RingBuffer(const RingBuffer& buf)
    : m_size(buf.m_size) {
    m_buffer.reserve(buf.m_buffer.capacity());
    m_buffer = buf.m_buffer;
    size_t d2last = static_cast<size_t>(buf.m_last_ind - buf.m_buffer.begin());
    size_t d2first = static_cast<size_t>(buf.m_first_ind - buf.m_buffer.begin());
    m_first_ind = m_buffer.begin() + d2first;
    m_last_ind = m_buffer.begin() + d2last;
};

int& RingBuffer::operator[](const size_t& ind) {
    if (m_size == 0 || ind >= m_size || ind >= m_buffer.size()) {
        int* n = nullptr;
        return *n;
    }

    if (m_first_ind < m_last_ind) return *(m_first_ind + ind);

    size_t dist = std::distance(m_first_ind, m_buffer.end());
    if (ind >= dist) return m_buffer[ind - dist];
    else return *(m_first_ind + ind);
}

int RingBuffer::operator[](const size_t& ind) const {
    if (m_size == 0 || ind >= m_size || ind >= m_buffer.size()) {
        int* n = nullptr;
        return *n;
    }

    size_t dist = 0;
    if (m_first_ind < m_last_ind) return *(m_first_ind + ind); 
    else dist = static_cast<size_t>(m_buffer.end() - m_first_ind);

    if (ind >= dist) return m_buffer[ind - dist];
    return *(m_first_ind + ind);
}

RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    if (&other == this) return *this;
    
    m_buffer = other.m_buffer;
    m_buffer.reserve(other.m_buffer.capacity());
    m_first_ind = other.m_first_ind;
    m_last_ind = other.m_last_ind;
    m_size = other.m_size;
    return *this;
}

void RingBuffer::Push(const int& num) {
    if (m_size == 0) {
        ++m_size;
        if (m_buffer.size() == 0) m_buffer.push_back(num);
        m_first_ind = m_buffer.begin();
        *m_last_ind = num;
    }
    else {
        if (m_size < m_buffer.capacity()) {
            if (m_last_ind + 1 == m_buffer.end()) {
                if (m_buffer.size() != m_buffer.capacity()) {
                    m_buffer.push_back(num);
                    ++m_last_ind;
                }
                else {
                    m_last_ind = m_buffer.begin();
                    *m_last_ind = num;
                }
            }
            else *(++m_last_ind) = num;
            ++m_size;
        }
        else {
            *m_first_ind = num;
            m_last_ind = m_first_ind;
            ++m_first_ind;
            if (m_first_ind == m_buffer.end()) m_first_ind = m_buffer.begin();
        }
    }
}

bool RingBuffer::TryPush(const int& num) {
    if (m_size == m_buffer.capacity()) return false;
    Push(num);
    return true;
}

void RingBuffer::Pop() {
    if (m_size != 0) {
        --m_size;
        ++m_first_ind;
        if (m_first_ind == m_buffer.end()) m_first_ind = m_buffer.begin();
    }
}

bool RingBuffer::TryPop(int& num) {
    if (m_size == 0) return false;
    num = Back();
    Pop();
    return true;
}

void RingBuffer::Resize(size_t new_capacity) {
    if (new_capacity == 0) new_capacity = 1;
    std::vector<int> new_buf;
    
    if (m_size <= new_capacity) {
        new_buf.reserve(m_size);
        for (size_t i = 0; i < m_size; ++i) {
            new_buf.push_back((*this)[i]);
        }
    }
    else {
        size_t off = m_size - new_capacity;
        new_buf.reserve(new_capacity);
        for (size_t i = 0; i < new_capacity; ++i) {
            new_buf.push_back((*this)[i + off]);
        }
        m_size = new_capacity;
    }

    m_buffer.clear();
    m_buffer.shrink_to_fit();
    m_buffer.reserve(new_capacity);
    m_buffer = new_buf;
    m_first_ind = m_buffer.begin();
    m_last_ind = m_first_ind + (m_size - 1);
}

void RingBuffer::Clear() {
    m_size = 0;
    m_first_ind = m_buffer.begin();
    m_last_ind = m_buffer.begin();
}

int& RingBuffer::Front() {
    if (m_size != 0) return *m_last_ind;
    int* n = nullptr;
    return *n;
}

int& RingBuffer::Back() {
    if (m_size != 0) return *m_first_ind;
    int* n = nullptr;
    return *n;
}

int RingBuffer::Front() const {
    if (m_size != 0) return *m_last_ind;
    int* n = nullptr;
    return *n;
}

int RingBuffer::Back() const {
    if (m_size != 0) return *m_first_ind;
    int* n = nullptr;
    return *n;
}

bool RingBuffer::Full() const {
    return m_size == m_buffer.capacity();
}

bool RingBuffer::Empty() const {
    return m_size == 0;
}

int RingBuffer::Size() const {
    return m_size;
}

int RingBuffer::Capacity() const{
    return m_buffer.capacity();
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> res;
    res.reserve(m_buffer.size());
    auto it = m_first_ind;
    size_t d2first = static_cast<size_t>(m_first_ind - m_buffer.begin());
    for (size_t i = 0, j = 0; j < m_size; ++i, ++j) {
        if ((it + i) == m_buffer.end()) {
            it -= d2first;
            i = 0;
        }
        res.push_back(*(it + i));
    }
    return res;
}

void func(double one, double two) {
    for(int i=0;i<2;i++){

    };
}