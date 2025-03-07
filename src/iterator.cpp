/**
 * @file iterator.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code on the usage and creation of iterators.
 * @brief 关于迭代器的使用和创建的教程代码。
 */

// C++ iterators are objects that point to an element inside a container.
// They can be used to iterate through the objects of that container.
// One example of an iterator that you know is a pointer. A pointer
// can be used to iterate through a C style array. Take the following
// C-style code snippet:
// int *array = malloc(sizeof(int) * 10);
// int *iter = array;
// int zero_elem = *iter;
// iter++;
// int first_elem = *iter;
// As we can see, the ++ operator can be used to iterate through the
// C style array, and the derefence operator returns the value at the
// iterator.
// C++迭代器是指向容器内部元素的对象。
// 它们可以用于遍历该容器的对象。
// 你所知道的迭代器的一个例子是指针。指针
// 可以用来遍历C风格的数组。看看下面的
// C风格代码片段:
// int *array = malloc(sizeof(int) * 10);
// int *iter = array;
// int zero_elem = *iter;
// iter++;
// int first_elem = *iter;
// 如我们所见，++运算符可以用来遍历
// C风格数组，解引用运算符返回迭代器所在位置的值。

// The main components of a C++ iterator are its main two operators. The
// dereference operator (*) on an iterator should return the value of the
// element at the current position of the iterator. The ++ (postfix increment)
// operator should increment the iterator's position by 1. As you can see, this
// is true with the pointer being used to iterate through a C style array.
// C++迭代器的主要组成部分是其两个主要运算符。
// 迭代器的解引用运算符(*)应返回迭代器当前位置的
// 元素的值。++(后缀递增)运算符应该将迭代器的位置增加1。
// 如你所见，这对于用来遍历C风格数组的指针是适用的。

// There are a few examples about how to use iterators to access elements
// in C++ STL containers in vectors.cpp, sets.cpp, unordered_maps.cpp,
// and auto.cpp. This is because using iterators in C++ to access and modify
// elements in C++ STL containers is considered good style, and worth
// mentioning in these files.
// 在vectors.cpp、sets.cpp、unordered_maps.cpp和
// auto.cpp中有一些关于如何使用迭代器访问C++ STL容器中元素的例子。
// 这是因为在C++中使用迭代器访问和修改C++ STL容器中的元素
// 被认为是良好的风格，值得在这些文件中提及。

// This file will mainly focus on the implementation of iterators. In this
// file, we demonstrate implementing C++ iterators by writing a basic doubly
// linked list (DLL) iterator.
// 本文件将主要关注迭代器的实现。在本文件中，
// 我们通过编写一个基本的双向链表(DLL)迭代器
// 来演示C++迭代器的实现。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout(打印)用于演示目的。
#include <iostream>

// This is the definition of the Node struct, used in our DLL.
// 这是我们DLL中使用的Node结构体的定义。
struct Node {
    Node(int val) : next_(nullptr), prev_(nullptr), value_(val) {}

    Node *next_;
    Node *prev_;
    int value_;
};

// This class implements a C++ style iterator for the doubly linked list class
// DLL. This class's constructor takes in a node that marks the start of the
// iterating. It also implements several operators that increment the iterator
// (i.e. accessing the next element in the DLL) and test for equality between
// two different iterators by comparing their curr_ pointers.
// 这个类为双向链表类DLL实现了一个C++风格的迭代器。
// 这个类的构造函数接收一个标记迭代起点的节点。
// 它还实现了几个运算符，用于递增迭代器
// (即访问DLL中的下一个元素)并通过比较它们的curr_指针
// 来测试两个不同迭代器之间的相等性。
class DLLIterator {
public:
    DLLIterator(Node *head) : curr_(head) {}

    // Implementing a prefix increment operator (++iter).
    // 实现前缀递增运算符(++iter)。
    DLLIterator &operator++() {
        curr_ = curr_->next_;
        return *this;
    }


    // Implementing a postfix increment operator (iter++). The difference
    // between a prefix and postfix increment operator is the return value
    // of the operator. The prefix operator returns the result of the
    // increment, while the postfix operator returns the iterator before
    // the increment.
    // 实现后缀递增运算符(iter++)。前缀和后缀递增运算符的区别
    // 在于运算符的返回值。前缀运算符返回递增的结果，
    // 而后缀运算符返回递增前的迭代器。
    DLLIterator operator++(int) {
        DLLIterator temp = *this;
        ++*this;
        return temp;
    }

    // This is the equality operator for the DLLIterator class. It
    // tests that the current pointers are the same.
    // 这是DLLIterator类的相等运算符。它
    // 测试当前指针是否相同。
    bool operator==(const DLLIterator &itr) const { return itr.curr_ == this->curr_; }

    // This is the inequality operator for the DLLIterator class. It
    // tests that the current pointers are not the same.
    // 这是DLLIterator类的不等运算符。它
    // 测试当前指针是否不同。
    bool operator!=(const DLLIterator &itr) const { return itr.curr_ != this->curr_; }

    // This is the dereference operator for the DLLIterator class. It
    // returns the value of the element at the current position of the
    // iterator. The current position of the iterator is marked by curr_,
    // and we can access the value of curr_ by accessing its value field.
    // 这是DLLIterator类的解引用运算符。它
    // 返回迭代器当前位置元素的值。
    // 迭代器的当前位置由curr_标记，
    // 我们可以通过访问其value字段来访问curr_的值。
    int operator*() { return curr_->value_; }

private:
    Node *curr_;
};


// This is a basic implementation of a doubly linked list. It also includes
// iterator functions Begin and End, which return DLLIterators that can be
// used to iterate through this DLL instance.
// 这是双向链表的基本实现。它还包括
// 迭代器函数Begin和End，它们返回可用于
// 遍历此DLL实例的DLLIterators。
class DLL {
public:
    // DLL class constructor.
    // DLL类构造函数。
    DLL() : head_(nullptr), size_(0) {}

    // Destructor should delete all the nodes by iterating through them.
    // 析构函数应通过遍历所有节点来删除它们。
    ~DLL() {
        Node *current = head_;
        while (current != nullptr) {
            Node *next = current->next_;
            delete current;
            current = next;
        }
        head_ = nullptr;
    }

    // Function for inserting val at the head of the DLL.
    // 在DLL头部插入val的函数。
    void InsertAtHead(int val) {
        Node *new_node = new Node(val);
        new_node->next_ = head_;

        if (head_ != nullptr) {
            head_->prev_ = new_node;
        }

        head_ = new_node;
        size_ += 1;
    }

    // The Begin() function returns an iterator to the head of the DLL,
    // which is the first element to access when iterating through.
    // Begin()函数返回指向DLL头部的迭代器，
    // 这是遍历时要访问的第一个元素。
    DLLIterator Begin() { return DLLIterator(head_); }


    // The End() function returns an iterator that marks the one-past-the-last
    // element of the iterator. In this case, this would be an iterator with
    // its current pointer set to nullptr.
    // End()函数返回一个标记迭代器最后一个元素之后位置的迭代器。
    // 在这种情况下，这将是一个当前指针设置为nullptr的迭代器。
    DLLIterator End() { return DLLIterator(nullptr); }

    Node *head_{nullptr};
    size_t size_;
};

// The main function shows the usage of the DLL iterator.
// main函数展示了DLL迭代器的使用。
int main() {
    // Creating a DLL and inserting elements into it.
    // 创建一个DLL并向其中插入元素。
    DLL dll;
    dll.InsertAtHead(6);
    dll.InsertAtHead(5);
    dll.InsertAtHead(4);
    dll.InsertAtHead(3);
    dll.InsertAtHead(2);
    dll.InsertAtHead(1);

    // We can iterate through our DLL via both our prefix and postfix operators.
    // 我们可以通过前缀和后缀运算符遍历我们的DLL。
    std::cout << "Printing elements of the DLL dll via prefix increment operator\n";
    for (DLLIterator iter = dll.Begin(); iter != dll.End(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << "Printing elements of the DLL dll via postfix increment operator\n";
    for (DLLIterator iter = dll.Begin(); iter != dll.End(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}
