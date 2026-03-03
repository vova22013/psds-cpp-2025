#include <vector>
#include <algorithm>

class RingBuffer {
public:
    RingBuffer();
    RingBuffer(size_t capacity);
    RingBuffer(size_t capacity, int num);
    RingBuffer(const std::initializer_list<int>& init_list);
    RingBuffer(const RingBuffer& buf);

    void Push(int num);
    bool TryPush(int num);
    void Pop();
    bool TryPop(int& num);
    size_t Size() const;
    size_t Capacity() const;
    int& Front();
    int& Back();
    const int& Front() const;
    const int& Back() const;
    bool Empty() const;
    bool Full() const;
    void Clear();
    void Resize(size_t new_cap);
    std::vector<int> Vector() const;

    int& operator[](size_t ind);
    const int& operator[](size_t ind) const;
    RingBuffer& operator=(const RingBuffer& other);

private:
    size_t size_ = 0;
    std::vector<int> buf_;
    std::vector<int>::iterator fptr_ = buf_.begin();
    std::vector<int>::iterator lptr_ = buf_.begin();
};

RingBuffer::RingBuffer() = default;

RingBuffer::RingBuffer(size_t capacity) {
    capacity == 0 ? buf_.resize(1) : buf_.resize(capacity);
    fptr_ = buf_.begin();
    lptr_ = buf_.begin();
}

RingBuffer::RingBuffer(size_t capacity, int num) {
    capacity == 0 ? buf_.resize(1, num) : buf_.resize(capacity, num);
    size_ = buf_.size();
    fptr_ = buf_.begin();
    Empty() ? lptr_ = buf_.begin() : lptr_ = buf_.begin() + size_ - 1;
}

RingBuffer::RingBuffer(const std::initializer_list<int>& init_list) : 
    size_(init_list.size()), 
    buf_(init_list) {
    if (size_ == 0) buf_.resize(1);
    fptr_ = buf_.begin();
    Empty() ? lptr_ = buf_.begin() : lptr_ = buf_.begin() + size_ - 1;
};

RingBuffer::RingBuffer(const RingBuffer& other) :
    size_(other.size_),
    buf_(other.buf_),
    fptr_(buf_.begin()) {
    Empty() ? lptr_ = buf_.begin() : lptr_ = buf_.begin() + size_ - 1;
}

const int& RingBuffer::operator[](size_t pos) const {
    size_t dist = (buf_.begin() + size_) - fptr_;
    return (pos < dist) ? *(fptr_ + pos) : *(buf_.begin() + (pos - dist));  
}

int& RingBuffer::operator[](size_t pos) {
    size_t dist = (buf_.begin() + size_) - fptr_;
    return (pos < dist) ? *(fptr_ + pos) : *(buf_.begin() + (pos - dist));
}

RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    if (&other != this) {
        buf_ = other.buf_;
        fptr_ = other.fptr_;
        lptr_ = other.lptr_;
        size_ = other.size_;
    }
    return *this;
}

void RingBuffer::Push(int num) {
    if (size_ < buf_.capacity()) {
        if (++lptr_ == buf_.end()) lptr_ = buf_.begin();
        size_++ == 0 ? *(--lptr_) = num : *lptr_ = num;
        return;
    }
    *fptr_ = num;
    lptr_ = fptr_;
    if (++fptr_ == buf_.begin()+ size_) fptr_ = buf_.begin(); 
}

bool RingBuffer::TryPush(int num) {
    return !Full() ? (Push(num), true) : false;
}

void RingBuffer::Pop() {
    if (!Empty()) {
        --size_;
        if (++fptr_ == buf_.end()) fptr_ = buf_.begin();
    }
}

bool RingBuffer::TryPop(int& num) {
    return !Empty() ? (num = Back(), Pop(), true) : false;
}

void RingBuffer::Resize(size_t new_cap) {
    if (new_cap == 0) new_cap = 1;
    
    auto temp = Vector();
    buf_.clear();
    buf_.shrink_to_fit();
    buf_.resize(new_cap);

    size_t offset = 0;
    if (size_ > new_cap) {
        offset = size_ - new_cap;
        size_ = new_cap;
    }
    for (size_t i = 0; i < size_; ++i) {
        buf_[i] = temp[i + offset];
    }

    fptr_ = buf_.begin();
    lptr_ = buf_.begin() + size_ - 1;
}

void RingBuffer::Clear() {
    size_ = 0;
    fptr_ = buf_.begin();
    lptr_ = buf_.begin();
}

int& RingBuffer::Front() {
    return (*this)[size_ - 1];
}

int& RingBuffer::Back() {
    return (*this)[0];
}

const int& RingBuffer::Front() const {
    return (*this)[size_ - 1];
}

const int& RingBuffer::Back() const {
    return (*this)[0];
}

bool RingBuffer::Full() const {
    return size_ == buf_.capacity();
}

bool RingBuffer::Empty() const {
    return size_ == 0;
}

size_t RingBuffer::Size() const {
    return size_;
}

size_t RingBuffer::Capacity() const{
    return buf_.capacity();
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> res(size_);
    for (size_t i = 0; i < size_; ++i) {
        res[i] = (*this)[i];
    }
    return res;
}