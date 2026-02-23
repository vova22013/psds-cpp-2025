#include <string>

class SharedPtr;
class WeakPtr;

struct Control {
    size_t count_owners_ = 1;
    size_t count_observers_ = 0;

    Control();
    Control(size_t count_owners);
    Control(size_t count_owners, size_t count_observers);
};

class SharedPtr {
public:
    SharedPtr();
    SharedPtr(std::string* str_ptr);
    SharedPtr(const WeakPtr& weak_ptr);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    ~SharedPtr();
    
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    std::string& operator*() const;
    std::string* operator->() const;
    operator bool() const noexcept;
    
    std::string* Get() const noexcept;
    Control* GetBlock() const noexcept;
    void Reset(std::string* str_ptr) noexcept;
    void Swap(SharedPtr& other) noexcept;
    size_t UseCount() const noexcept;
    
private:
    std::string* data_ = nullptr;
    Control* block_ = nullptr;
};

class WeakPtr {
public:
    WeakPtr();
    WeakPtr(const SharedPtr& shared_ptr);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;
    ~WeakPtr();
    
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    const std::string& operator*() const;
    const std::string* operator->() const;
    
    void Reset() noexcept;
    void Swap(WeakPtr& other) noexcept;
    size_t UseCount() const noexcept;
    bool Expired() const noexcept;
    SharedPtr Lock() noexcept;

    friend SharedPtr::SharedPtr(const WeakPtr& weak_ptr);
    
private:
    const std::string* data_ = nullptr;
    Control* block_ = nullptr;
};

// Control's ctors

Control::Control() = default;

Control::Control(size_t count_owners, size_t count_observers) :
    count_owners_(count_owners), count_observers_(count_observers) {}

Control::Control(size_t count_owners) : Control(count_owners, 0) {}

// SharePtr's ctors and methods

SharedPtr::SharedPtr() : 
    block_(new Control()){};

SharedPtr::SharedPtr(std::string* str_ptr) :
    data_(str_ptr),
    block_(new Control()){};

SharedPtr::SharedPtr(const WeakPtr& weak_ptr) :
    data_(const_cast<std::string*>(weak_ptr.data_)),
    block_(weak_ptr.block_) {
    ++block_->count_owners_;
}

SharedPtr::SharedPtr(const SharedPtr& other) :
    data_(other.data_),
    block_(other.block_) {
    ++block_->count_owners_;
}

SharedPtr::SharedPtr(SharedPtr && other) noexcept :
    data_(other.data_),
    block_(other.block_) {
    other.data_ = nullptr;
    other.block_ = nullptr;
}

SharedPtr::~SharedPtr() {
    if (data_ && --block_->count_owners_ == 0) {
        delete data_;
        data_ = nullptr;
        delete block_;
        block_ = nullptr;
    }
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        if (data_ && --block_->count_owners_ == 0) {
            delete data_;
            delete block_;
        }
        data_ = other.data_;
        block_ = other.block_;
        ++block_->count_owners_;
    }
    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        if (data_ && --block_->count_owners_ == 0) {
            delete data_;
            delete block_;
        }
        data_ = other.data_;
        block_ = other.block_;
        other.data_ = nullptr;
        other.block_ = nullptr;   
    }
    return *this;
}

std::string& SharedPtr::operator*() const {
    return *data_;
}

std::string* SharedPtr::operator->() const {
    return data_;
}

std::string* SharedPtr::Get() const noexcept {
    return data_;
}

Control* SharedPtr::GetBlock() const noexcept {
    return block_;
}

void SharedPtr::Reset(std::string* str_ptr = nullptr) noexcept {
    if (block_ && --block_->count_owners_ == 0) {
        delete data_;
        ++block_->count_owners_;
    } 
    else block_ = new Control();
    data_ = str_ptr;
} 

void SharedPtr::Swap(SharedPtr& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(block_, other.block_);
}

size_t SharedPtr::UseCount() const noexcept {
    return data_ ? block_->count_owners_ : 0;
}

SharedPtr::operator bool() const noexcept {
    return static_cast<bool>(data_);
}

SharedPtr MakeShared(const std::string& str) noexcept {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(const SharedPtr& other) noexcept {
    return SharedPtr(other);
}

SharedPtr MakeShared(SharedPtr&& other) noexcept {
    return SharedPtr(std::move(other));
}

void Swap(SharedPtr& lft, SharedPtr& rht) noexcept {
    std::swap(lft, rht);
}

// WeakPtr's ctors and methods

WeakPtr::WeakPtr() = default;

WeakPtr::WeakPtr(const SharedPtr& shared_ptr) :
    data_(shared_ptr.Get()),
    block_(shared_ptr.GetBlock()) {
    ++block_->count_observers_;
}

WeakPtr::WeakPtr(const WeakPtr& other) :
    data_(other.data_),
    block_(other.block_) {
    ++block_->count_observers_;
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept :
    data_(other.data_),
    block_(other.block_) {
    other.data_ = nullptr;
    other.block_ = nullptr;
}

WeakPtr::~WeakPtr() = default;

WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if (this != &other) {
        data_ = other.data_;
        --block_->count_observers_;
        block_ = other.block_;
        ++block_->count_observers_;
    }
    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        data_ = other.data_;
        if (block_) --block_->count_observers_;
        block_ = other.block_;
        other.data_ = nullptr;
        other.block_ = nullptr;
    }
    return *this;
}

const std::string& WeakPtr::operator*() const {
    return *data_;
}

const std::string* WeakPtr::operator->() const {
    return data_;
}

void WeakPtr::Reset() noexcept {
    data_ = nullptr;
    if (block_) --block_->count_observers_;
    block_ = nullptr;
}

void WeakPtr::Swap(WeakPtr& other) noexcept {
    std::swap(data_, other.data_);
}

size_t WeakPtr::UseCount() const noexcept {
    return block_ ? block_->count_owners_ : 0;
}

bool WeakPtr::Expired() const noexcept {
    return UseCount() == 0;
}

SharedPtr WeakPtr::Lock() noexcept {
    return UseCount() != 0 ? SharedPtr(*this) : SharedPtr();
}

void Swap(WeakPtr& lft, WeakPtr& rht) noexcept {
    std::swap(lft, rht);
}













