#include <string>

struct Node {
    Node();
    Node(const std::string& str);
    Node(std::string&& str);
    Node(const Node& other);
    Node(Node&& other) noexcept;
    Node& operator=(const Node& other);
    Node& operator=(Node&& other) noexcept;
    ~Node();
    
    Node* prev_ = this;
    Node* next_ = this;
    std::string data_ = "";
};

Node::Node() = default;

Node::Node(const std::string& str) :
    data_(str) {}
    
Node::Node(std::string&& str) :
    data_(std::move(str)) {}

Node::Node(const Node& other) :
    prev_(other.prev_), next_(other.next_), data_(other.data_) {}

Node::Node(Node&& other) noexcept : 
    prev_(other.prev_),
    next_(other.next_),
    data_(std::move(other.data_)) {
    other.prev_ = nullptr;
    other.next_ = nullptr;    
}

Node& Node::operator=(const Node& other) {
    if (this != &other) {
        prev_ = other.prev_;
        next_ = other.next_;
        data_ = other.data_;
    }
    return *this;
}

Node& Node::operator=(Node&& other) noexcept {
    if (this != &other) {
        prev_ = other.prev_;
        next_ = other.next_;
        data_ = std::move(other.data_);
        other.prev_ = nullptr;
        other.next_ = nullptr;
    }
    return *this;
}

Node::~Node() = default;


class SimpleList {
public:
    SimpleList();
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other) noexcept;
    ~SimpleList();
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other) noexcept;

    void Swap(SimpleList& other) noexcept;
    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void PushBack(const std::string& str) noexcept;
    void PushBack(std::string&& str) noexcept;
    void PopBack() noexcept;
    void PushFront(const std::string& str) noexcept;
    void PushFront(std::string&& str) noexcept;
    void PopFront() noexcept;
    std::string& Back();
    const std::string& Back() const;
    std::string& Front();
    const std::string& Front() const;
    
    void Clear() noexcept;

private:
    void Unlink(Node* elem) noexcept;
    void Link(Node* new_node, Node* elem_prev) noexcept;

    size_t size_ = 0;
    Node* node_ = nullptr;
};

SimpleList::SimpleList() :
    size_(0), node_(new Node()) {
}

SimpleList::SimpleList(const SimpleList& other) :
    node_(new Node(other.node_->data_)) {
    Node* temp = other.node_->next_;
    while (temp != other.node_) {
        PushBack(temp->data_);
        temp = temp->next_;
    }
}

SimpleList::SimpleList(SimpleList&& other) noexcept :
    size_(other.size_),
    node_(std::move(other.node_)) {
    other.node_ = nullptr;
    other.size_ = 0;
}

SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this != &other) {
        if (node_) {
            while (!Empty()) PopBack();
            delete node_;
        }
        node_ = new Node(other.node_->data_);
        Node* temp = other.node_->next_;
        while (temp != other.node_) {
            PushBack(temp->data_);
            temp = temp->next_;
        }
    }
    return *this;
}

SimpleList& SimpleList::operator=(SimpleList&& other) noexcept {
    if (this != &other) {
        if (node_) {
            while (!Empty()) PopBack();
            delete node_;
        }
        size_ = other.size_;
        node_ = std::move(other.node_);
        other.node_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

SimpleList::~SimpleList() {
    if (node_ && (node_->prev_ != node_ || node_->next_ != node_)) {
        while (!Empty()) PopBack();
    }
    delete node_;
};

void SimpleList::Link(Node* new_node, Node* node_prev) noexcept {
    Node* next = node_prev->next_;
    node_prev->next_ = new_node;
    new_node->prev_ = node_prev;
    new_node->next_ = next;
    next->prev_ = new_node;
}

void SimpleList::Unlink(Node* out_node) noexcept {
    out_node->prev_->next_ = out_node->next_;
    out_node->next_->prev_ = out_node->prev_;
}

void SimpleList::Swap(SimpleList& other) noexcept {
    std::swap(node_, other.node_);
    std::swap(size_, other.size_);
}

size_t SimpleList::Size() const noexcept {
    return size_;
}

bool SimpleList::Empty() const noexcept {
    return size_ == 0;
}

void SimpleList::PushBack(const std::string& str) noexcept {
    Node* new_node = new Node(str);
    if (!node_) node_ = new Node();
    Link(new_node, node_->prev_);
    ++size_;
}

void SimpleList::PushBack(std::string&& str) noexcept {
    Node* new_node = new Node(std::move(str));
    if (!node_) node_ = new Node();
    Link(new_node, node_->prev_);
    ++size_;
}

void SimpleList::PushFront(const std::string& str) noexcept {
    Node* new_node = new Node(str);
    if (!node_) node_ = new Node();
    Link(new_node, node_);
    ++size_;
}

void SimpleList::PushFront(std::string&& str) noexcept {
    Node* new_node = new Node(std::move(str));
    if (!node_) node_ = new Node();
    Link(new_node, node_);
    ++size_;
}

void SimpleList::PopBack() noexcept {
    if (!Empty()) {
        Node* out_node = node_->prev_;
        Unlink(out_node);
        delete out_node;
        --size_;
    }
}

void SimpleList::PopFront() noexcept {
    if (!Empty()) {
        Node* out_node = node_->next_;
        Unlink(out_node);
        delete out_node;
        --size_;
    }
}

const std::string& SimpleList::Back() const {
    return node_->prev_->data_;
}

const std::string& SimpleList::Front() const {
    return node_->next_->data_;
}

std::string& SimpleList::Back() {
    return node_->prev_->data_;
}

std::string& SimpleList::Front() {
    return node_->next_->data_;
}

void SimpleList::Clear() noexcept {
    while (!Empty()) PopBack();
}

void Swap(SimpleList& lft, SimpleList& rht) noexcept {
    std::swap(lft, rht);
}



