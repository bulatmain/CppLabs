#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <initializer_list>
#include <exception>
#include <memory>

// ------------- linked_list -------------

namespace lab5 {

    template <typename T>
    struct node;

    template <typename T, typename Allocator>
    class linked_list {    
    public:
        class iterator;
        class const_iterator;

        linked_list();
        linked_list(const std::initializer_list<T>& list);
        linked_list(const linked_list& other);
        linked_list(linked_list&& other) noexcept;

        linked_list& operator= (const linked_list& other);
        linked_list& operator= (linked_list&& other) noexcept;
    
        ~linked_list() noexcept;

        T& at(const const_iterator& it);
        T at(const const_iterator& it) const;

        void insert(const T& data, const const_iterator& iter);

        void erase(const const_iterator& iter) noexcept;

        T pop(const const_iterator& iter) noexcept;

        iterator begin() noexcept;
        iterator end() noexcept;

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;

        const_iterator cbegin() noexcept;
        const_iterator cend() noexcept;

        std::size_t length() const noexcept;
        bool empty() const noexcept;

    protected:
        void copy(const linked_list& other);
        void move(linked_list&& other) noexcept;

        node<T>* make_new_node(const T& data);

        Allocator allocator;
        node<T>* first;
        node<T>* last;
        std::size_t size;
    };


    template <typename T, typename Allocator>
    linked_list<T, Allocator>::linked_list() : first(nullptr), last(nullptr), size(0) {}

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::linked_list(const std::initializer_list<T>& list) {
        using traits = std::allocator_traits<Allocator>;
        first = traits::allocate(allocator, sizeof(node<T>));
        struct node<T>* i = first;
        auto it = list.begin();
        while (true) {
            node<T> new_node{ std::move(*it), nullptr }; 
            traits::construct(allocator, i, std::move(new_node));
            if (++it == list.end()) {
                last = i;
                break;
            } else {
                i->next = traits::allocate(allocator, sizeof(node<T>));
                i = i->next;
            }
        }
        size = list.size();
    }

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::linked_list(const linked_list& other) {
        copy(other);
    }

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::linked_list(linked_list&& other) noexcept {
        move(std::move(other));
    }

    template <typename T, typename Allocator>
    linked_list<T, Allocator>& linked_list<T, Allocator>::operator= (const linked_list& other) {
        copy(other);
        return *this;
    }

    template <typename T, typename Allocator>
    linked_list<T, Allocator>& linked_list<T, Allocator>::operator= (linked_list&& other) noexcept {
        move(std::move(other));
        return *this;
    }

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::~linked_list() noexcept {
        using traits = std::allocator_traits<Allocator>;
        struct node<T> *l, *r = first;
        while (r != nullptr) {
            l = r; r = r->next;
            traits::destroy(allocator, l);
            traits::deallocate(allocator, l, sizeof(node<T>));
        }

        first = nullptr;
        size = 0;
    }

    template <typename T, typename Allocator>
    void linked_list<T, Allocator>::copy(const linked_list& other) {
        using traits = std::allocator_traits<Allocator>;
        first = traits::allocate(allocator, sizeof(node<T>));
        struct node<T>* i = first;
        auto& it = other.begin();
        while (true) {
            traits::construct(allocator, i, std::move(*it.p));
            if (++it == other.end()) {
                last = i;
                break;
            } else {
                i->next = traits::allocate(allocator, sizeof(node<T>));
                i = i->next;
            }
        }
        size = other.size;
    }

    template <typename T, typename Allocator>
    void linked_list<T, Allocator>::move(linked_list&& other) noexcept {
        allocator = std::move(other.allocator);
        first = other.first;
        last = other.last;
        size = other.size;

        other.first = other.last = nullptr;
        other.size = 0;
    }

    template <typename T, typename Allocator>
    T& linked_list<T, Allocator>::at(const const_iterator& it) {
        if (it == end()) {
            throw std::invalid_argument("Error: passing end iterator to at.\n");
        }
        return const_cast<node<T>*>(it.p)->data;
    }

    template <typename T, typename Allocator>
    T linked_list<T, Allocator>::at(const const_iterator& it) const {
        return at(it);
    }

    template <typename T, typename Allocator>
    node<T>* linked_list<T, Allocator>::make_new_node(const T& data) {
        using traits = std::allocator_traits<Allocator>;
        node<T>* p_new = traits::allocate(allocator, sizeof(node<T>));
        node<T> structure(data, nullptr);
        traits::construct(allocator, p_new, std::move(structure));
        return p_new;
    }

    template <typename T, typename Allocator>
    void linked_list<T, Allocator>::insert(const T& data, const const_iterator& it) {
        node<T>* p_new = make_new_node(data);

        if (empty()) {
            first = last = p_new;
            return;
        }

        if (it == end()) {
            last->next = p_new;
            last = p_new;
        } else {
            node<T>* p_curr = const_cast<node<T>*>(it.p);

            std::swap(p_curr->data, p_new->data);
            p_new->next = p_curr->next;
            p_curr->next = p_new;
        }
        ++size;
    }

    template <typename T, typename Allocator>
    void linked_list<T, Allocator>::erase(const const_iterator& iter) noexcept {
        pop(iter);
    }

    template <typename T, typename Allocator>
    T linked_list<T, Allocator>::pop(const const_iterator& iter) noexcept {
        if (empty()) {
            throw std::logic_error("Error: trying to erase element from empty list.\n");
        } else if (iter == end()) {
            throw std::invalid_argument("Error: passing end iterator to erase.\n");
        }

        using traits = std::allocator_traits<Allocator>;
        struct node<T>* to_delete;

        if (first == last) {
            to_delete = first;
            first = last = nullptr;
        } else if (iter == begin()) {
            to_delete = first;
            first = first->next;
        } else {
            struct node<T>* it = first;
            while (it->next != iter.p) { ++it; }
            if (iter.p == last) {
                last = it;
            }
            it->next = iter.p->next;
            to_delete = iter.p;
        }
 
        T to_return = std::move(to_delete->data);
        traits::destroy(allocator, to_delete);
        traits::deallocate(allocator, to_delete, sizeof(node<T>));

        --size;

        return to_return;
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::iterator linked_list<T, Allocator>::begin() noexcept {
        return iterator(first);
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::iterator linked_list<T, Allocator>::end() noexcept {
        return iterator(nullptr);
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator linked_list<T, Allocator>::begin() const noexcept {
        return const_iterator(first);
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator linked_list<T, Allocator>::end() const noexcept {
        return const_iterator(nullptr);
    }

        template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator linked_list<T, Allocator>::cbegin() noexcept {
        return const_iterator(first);
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator linked_list<T, Allocator>::cend() noexcept {
        return const_iterator(nullptr);
    }

    template <typename T, typename Allocator>
    std::size_t linked_list<T, Allocator>::length() const noexcept {
        return size;
    }

    template <typename T, typename Allocator>
    bool linked_list<T, Allocator>::empty() const noexcept {
        return begin() == end();
    }

// ------------- linked_list -------------


// ------------- node -------------

    template <typename T>
    struct node {
        node(const T& data, node* next) : data{data}, next{next} {}
        node(T&& data, node* next) : data{std::move(data)}, next{next} {}
        T data;
        node* next;
    };


// ------------- node -------------

// ------------- iterator -------------

    template <typename T, typename Allocator>
    class linked_list<T, Allocator>::iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer_type      = T*;
        using reference_type    = T&;

        friend class linked_list<T, Allocator>;
        friend class const_iterator;

        iterator(node<T>* ptr = nullptr);

        T& operator* ();
        T operator* () const;

        node<T>& operator->();
        const node<T>& operator->() const;

        iterator& operator++();
        iterator operator++(int);

        difference_type operator- (const iterator& other);

        bool operator== (const const_iterator& other) const noexcept;
        bool operator!= (const const_iterator& other) const noexcept;

    private:
        node<T>* p;
    };

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::iterator::iterator(node<T>* ptr) : p{ptr} {}

    template <typename T, typename Allocator>
    T& linked_list<T, Allocator>::iterator::operator*() {
        return p->data;
    }

    template <typename T, typename Allocator>
    T linked_list<T, Allocator>::iterator::operator*() const {
        return p->data;
    }

    template <typename T, typename Allocator>
    node<T>& linked_list<T, Allocator>::iterator::operator->() {
        return *p;
    }

    template <typename T, typename Allocator>
    const node<T>& linked_list<T, Allocator>::iterator::operator->() const {
        return *p;
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::iterator& linked_list<T, Allocator>::iterator::operator++() {
        p = p->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::iterator linked_list<T, Allocator>::iterator::operator++(int) {
        auto _it = *this;
        p = p->next;
        return _it;
    }

    template <typename T, typename Allocator>
    bool linked_list<T, Allocator>::iterator::operator==(const const_iterator& other) const noexcept {
        return p == other.p;
    }

    template <typename T, typename Allocator>
    bool linked_list<T, Allocator>::iterator::operator!=(const const_iterator& other) const noexcept {
        return p != other.p;
    }

// ------------- const_iterator -------------

    template <typename T, typename Allocator>
    class linked_list<T, Allocator>::const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer_type      = const T* const;
        using reference_type    = const T&;

        friend class linked_list<T, Allocator>;

        const_iterator(node<T>* ptr = nullptr);
        const_iterator(const iterator& other);

        const_iterator& operator= (const iterator& other);

        T operator* () const;

        const node<T>& operator->() const;

        const_iterator& operator++();
        const_iterator operator++(int);

        bool operator== (const const_iterator& other) const noexcept;
        bool operator!= (const const_iterator& other) const noexcept;

        friend bool iterator::operator==(const const_iterator&) const noexcept;
        friend bool iterator::operator!=(const const_iterator&) const noexcept;


    private:
        node<T>* p;
    };

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::const_iterator::const_iterator(node<T>* ptr) : p{ptr} {}

    template <typename T, typename Allocator>
    linked_list<T, Allocator>::const_iterator::const_iterator(const iterator& other) : p{other.p} {}

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator& linked_list<T, Allocator>::const_iterator::operator=(const iterator& other) {
        this->p = other.p;
        return *this;
    }

    template <typename T, typename Allocator>
    T linked_list<T, Allocator>::const_iterator::operator*() const {
        return p->data;
    }

    template <typename T, typename Allocator>
    const node<T>& linked_list<T, Allocator>::const_iterator::operator->() const {
        return *p;
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator& linked_list<T, Allocator>::const_iterator::operator++() {
        p = p->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename linked_list<T, Allocator>::const_iterator linked_list<T, Allocator>::const_iterator::operator++(int) {
        auto _it = *this;
        p = p->next;
        return _it;
    }

    template <typename T, typename Allocator>
    bool linked_list<T, Allocator>::const_iterator::operator==(const const_iterator& other) const noexcept {
        return p == other.p;
    }

    template <typename T, typename Allocator>
    bool linked_list<T, Allocator>::const_iterator::operator!=(const const_iterator& other) const noexcept {
        return p != other.p;
    }

};


#endif