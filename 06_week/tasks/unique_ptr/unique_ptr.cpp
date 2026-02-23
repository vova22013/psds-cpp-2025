#include <string>


class UniquePtr {
public:
    UniquePtr();
    UniquePtr(const std::string& str);
    UniquePtr(std::string&& str);
    UniquePtr(std::string* str_ptr);
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr(const UniquePtr& other) = delete;
    ~UniquePtr();
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    std::string& operator*() const;
    std::string* operator->() const;
    
    std::string* Get() const noexcept;
    std::string* Release() noexcept;
    void Reset(std::string* str_ptr) noexcept;
    void Swap(UniquePtr& other) noexcept;
    operator bool() const noexcept;

private:
    std::string* data_ = nullptr;
};

UniquePtr::UniquePtr() {}

UniquePtr::UniquePtr(std::string&& str) :
    data_(new std::string(std::move(str))) {}

UniquePtr::UniquePtr(std::string* str_ptr) :
    data_(str_ptr) {}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept :
    data_(other.data_) {
    other.data_ = nullptr;
}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete data_;
        data_ = std::move(other.data_);
        other.data_ = nullptr;
    }
    return *this;
}

UniquePtr::~UniquePtr() {
    if (data_) delete data_;
}

std::string& UniquePtr::operator*() const {
    return *data_;
}

std::string* UniquePtr::operator->() const {
    return data_;
}

std::string* UniquePtr::Get() const noexcept {
    return data_;
}

std::string* UniquePtr::Release() noexcept {
    std::string* new_ptr = data_;
    data_ = nullptr;
    return new_ptr;
}

void UniquePtr::Reset(std::string* str_ptr = nullptr) noexcept {
    delete data_;
    data_ = str_ptr;
}

void UniquePtr::Swap(UniquePtr& other) noexcept {
    std::swap(data_, other.data_);
}

UniquePtr::operator bool() const noexcept {
    return static_cast<bool>(data_);
}

UniquePtr MakeUnique(std::string* str_ptr) noexcept {
    return UniquePtr(str_ptr);
}

UniquePtr MakeUnique(const std::string& str) noexcept {
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& temp) noexcept {
    return UniquePtr(std::move(temp));
}

UniquePtr MakeUnique(UniquePtr other) noexcept {
    return UniquePtr(other.Get());
}

UniquePtr MakeUnique(UniquePtr&& other) noexcept {
    return UniquePtr(std::move(other));
}
   
void Swap(UniquePtr& lft, UniquePtr& rht) noexcept {
    std::swap(lft, rht);
}


