#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>

template<typename T>
struct Node {
  T value;
  Node * next;
  Node * prev;

  explicit Node(T value)
    : value(value)
    , next(nullptr)
    , prev(nullptr)
  {}
};

template<typename T>
struct ListBase {
protected:
  size_t size;
  Node<T> * head;
  Node<T> * tail;
public:

  friend std::ostream & operator<<(std::ostream & os, const ListBase<T> & list) {
    Node<T> * current = list.head;
    os << "[ ";
    while (current != nullptr) {
      os << current->value << " ";
      current = current->next;
    }
    os << "]";
    return os;
  }

  Node<T> * for_each_node(std::function<bool(Node<T> *)> closure) {
    Node<T> * current = head;
    while (current != nullptr) {
      if (closure(current)) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  Node<T> * for_each(std::function<bool(T)> closure) {
    Node<T> * current = head;
    while (current != nullptr) {
      if (closure(current->value)) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  // Function that receives a lambda that specifies a value to use for comparison
  template <typename V>
  void push_ord(T value, std::function<V(T)> get_value_from_node) {
    Node<T> * node = new Node(value);
    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      Node<T> * current = head;
      while (current != nullptr) {
        if (get_value_from_node(current->value) > get_value_from_node(value)) {
          push_before(node, current);
          if (current == head) {
            head = node;
          }
          size++;
          return;
        }
        current = current->next;
      }
      push_after(node, tail);
      tail = node;
    }
    size++;
  }


  ListBase()
    : head(nullptr)
    , tail(nullptr)
    , size(0)
  {}

  // Construct list from initializer list
  ListBase(std::initializer_list<T> list)
    : head(nullptr)
    , tail(nullptr)
    , size(0)
  {
    for (auto & value : list) {
      push_bk(value);
    }
  }

  // Copy constructor
  ListBase(const ListBase<T> & other)
    : head(nullptr)
    , tail(nullptr)
    , size(0)
  {
    Node<T> * current = other.head;
      while (current != nullptr) {
        auto next_current = current->next;
        push_bk(current->value);
        current = next_current;
      }
  }

  // Move constructor
  ListBase(ListBase<T> && other) noexcept
    : head(other.head)
    , tail(other.tail)
    , size(other.size)
  {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
  }

  ~ListBase() {
    if (size > 0) {
      Node<T> * current = head;
      while (current != nullptr) {
        auto next_current = current->next;
        delete current;
        current = next_current;
      }
    }
  }

protected:
  void push_before(Node<T> * node, Node<T> * at) {
    if (at->prev != nullptr) {
      at->prev->next = node;
    }
    node->prev = at->prev;
    node->next = at;
    at->prev = node;
  }

  void push_after(Node<T> * node, Node<T> * at) {
    if (at->next != nullptr) {
      at->next->prev = node;
    }
    node->next = at->next;
    node->prev = at;
    at->next = node;
  }


  void push_ft(T value) {
    Node<T> * node = new Node(value);
    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      push_before(node, head);
      head = node;
    }
    size++;
  }

  void push_bk(T value) {
    Node<T> * node = new Node(value);
    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      push_after(node, tail);
      tail = node;
    }
    size++;
  }

};

template<typename T>
struct List: ListBase<T> {

  void push_front(T value) {
    ListBase<T>::push_ft(value);
  }

  void push_back(T value) {
    ListBase<T>::push_bk(value);
  }

  List() : ListBase<T>() {}

  // Construct list from initializer list
  List(std::initializer_list<T> list)
    : ListBase<T>(list)
  {}
};

template<typename T>
struct FreValue {
  T value;
  size_t fre;

  // << operator
  friend std::ostream & operator<<(std::ostream & os, const FreValue<T> & fre_value) {
    os << "{ " << fre_value.value << " : " << fre_value.fre << " }";
    return os;
  }
};

template<typename T>
struct ListFre : ListBase<FreValue<T>> {
protected:
  using ListBase<FreValue<T>>::ListBase;
  using ListBase<FreValue<T>>::push_ft;
  using ListBase<FreValue<T>>::push_bk;
  using ListBase<FreValue<T>>::head;
  using ListBase<FreValue<T>>::tail;
  using ListBase<FreValue<T>>::size;



public:
  void push_fre(T value) {
    if (head == nullptr) {
      push_ft({value, 1});
      return;
    }

    Node<FreValue<T>> * node = this->for_each([&value](FreValue<T> fre_value) {
      return fre_value.value == value;
    });

    if (node != nullptr) {
      node->value.fre++;
    } else {
      push_bk({value, 1});
    }
  };

  ListFre() : ListBase<FreValue<T>>() {}

  ListFre(std::initializer_list<FreValue<T>> list)
    : ListBase<FreValue<T>>()
  {
    for (auto & value : list) {
      push_bk(value);
    }
  }

  ListFre(std::initializer_list<T> list)
    : ListBase<FreValue<T>>()
  {
    for (auto & value : list) {
      push_fre(value);
    }
  }
};

#endif //LIBRARY_HPP
