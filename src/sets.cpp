/**
 * @file sets.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) sets.
 * @brief C++标准库(STL)集合的教程代码。
 */

// In this file, we will introduce the container std::set. We won't be able
// to cover every function in this container, but we will try to cover the
// basics of using this container. Look to the intro of vectors.cpp for
// a general overview of C++ STL containers.
// 在这个文件中，我们将介绍容器std::set。我们不可能
// 涵盖这个容器的每个函数，但我们会尝试涵盖
// 使用这个容器的基础知识。查看vectors.cpp的介绍部分，了解
// C++ STL容器的一般概述。

// The std::set container is a data structure that contains a sorted set of
// unique objects of a single type. It is usually implemented as a Red-Black
// tree, if that helps you conceptualize the std::set. The std::set container
// is used to maintain of a set of unique elements.
// std::set容器是一种数据结构，包含单一类型的
// 已排序的唯一对象集合。它通常实现为红黑树，
// 如果这有助于你理解std::set的话。std::set容器
// 用于维护一组唯一元素。

// There is documentation on all the other functions, and other containers
// on https://en.cppreference.com/w/cpp/container. You will definitely need this
// resource as you complete the assignments in this class, so you should check
// it out!
// 所有其他函数和其他容器的文档都可以在
// https://en.cppreference.com/w/cpp/container 找到。在完成本课程的
// 作业时，你肯定需要这个资源，所以你应该查看一下！

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the set container library header.
// 包含集合容器库头文件。
#include <set>

int main() {
    // We can declare a int set with the following syntax.
    // 我们可以用以下语法声明一个整数集合。
    std::set<int> int_set;

    // To insert elements, we use the insert function. Here we insert elements 1
    // through 10 in our set. There also exists an emplace function that allows
    // the user to construct objects in place for set insertion. We cover emplace
    // more in vectors.cpp (line 73).
    // 要插入元素，我们使用insert函数。这里我们在集合中插入1到10的元素。
    // 还存在一个emplace函数，它允许用户就地构造对象以进行集合插入。
    // 我们在vectors.cpp（第73行）中更多地介绍了emplace。
    for (int i = 1; i <= 5; ++i) {
        int_set.insert(i);
    }

    for (int i = 6; i <= 10; ++i) {
        int_set.emplace(i);
    }

    // To find an element, we can use the find function, which returns an
    // iterator that points to the element within the set with the key that is
    // equivalent to the key argument. We can then check to see whether this
    // returned iterator is equivalent to the end iterator. If the returned
    // iterator value is equivalent to the end iterator value, then this would
    // imply that the element does not exist.
    // 要查找元素，我们可以使用find函数，它返回一个
    // 指向集合中键与键参数等价的元素的迭代器。
    // 然后我们可以检查这个返回的迭代器是否等价于end迭代器。
    // 如果返回的迭代器值等价于end迭代器值，那么这将
    // 意味着该元素不存在。
    std::set<int>::iterator search = int_set.find(2);
    if (search != int_set.end()) {
        std::cout << "Element 2 is in int_set.\n";
    }

    // We can also use the count function, which returns the number of elements
    // with the specified key in the set.
    // 我们也可以使用count函数，它返回集合中具有指定键的元素数量。
    if (int_set.count(11) == 0) {
        std::cout << "Element 11 is not in the set.\n";
    }

    if (int_set.count(3) == 1) {
        std::cout << "Element 3 is in the set.\n";
    }

    // To erase an element, we can use the erase function. The erase function can
    // firstly, take a key to erase. For instance, if we want to erase 4 from the
    // set, we can call:
    // 要删除元素，我们可以使用erase函数。erase函数可以
    // 首先，接受要删除的键。例如，如果我们想从集合中删除4，
    // 我们可以调用：
    int_set.erase(4);

    // We confirm that 4 isn't in the set anymore.
    // 我们确认4不再在集合中。
    if (int_set.count(4) == 0) {
        std::cout << "Element 4 is not in the set.\n";
    }

    // Additionally, if we want to erase an element at a certain position, we can
    // pass in an iterator to the erase function. Let's say we want to erase the
    // first element from the set. We can pass in an iterator that points to the
    // first element from the set to the erase function.
    // 另外，如果我们想删除某个位置的元素，我们可以
    // 将迭代器传递给erase函数。假设我们要删除
    // 集合中的第一个元素。我们可以传入一个指向
    // 集合中第一个元素的迭代器给erase函数。
    int_set.erase(int_set.begin());

    // We confirm that 1 isn't in the set anymore.
    // 我们确认1不再在集合中。
    if (int_set.count(1) == 0) {
        std::cout << "Element 1 is not in the set.\n";
    }

    // Lastly, we can erase elements in the set by passing in an iterator range to
    // the erase function. For instance, if we want to erase elements that are
    // greater than or equal to 9 (so, 9 and 10), we call the following.
    // 最后，我们可以通过向erase函数传递迭代器范围来
    // 删除集合中的元素。例如，如果我们想删除大于或等于
    // 9的元素（即9和10），我们调用以下内容。
    int_set.erase(int_set.find(9), int_set.end());

    // We confirm that 9 and 10 aren't in the set anymore.
    // 我们确认9和10不再在集合中。
    if (int_set.count(9) == 0 && int_set.count(10) == 0) {
        std::cout << "Elements 9 and 10 are not in the set.\n";
    }

    // We can iterate through the set elements via the set iterator. You cannot
    // iterate through a set via indexes of any kind.
    // 我们可以通过集合迭代器遍历集合元素。你不能
    // 通过任何类型的索引遍历集合。
    std::cout << "Printing the elements of the iterator:\n";
    for (std::set<int>::iterator it = int_set.begin(); it != int_set.end(); ++it) {
        // We can access the element itself by dereferencing the iterator.
        // 我们可以通过解引用迭代器来访问元素本身。
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Just like std::vector, we can also iterate through the set via a for-each
    // loop.
    // 就像std::vector一样，我们也可以通过for-each循环
    // 遍历集合。
    std::cout << "Printing the elements of the iterator with a for-each loop:\n";
    for (const int &elem: int_set) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // We discuss more stylistic and readable ways of iterating through C++ STL
    // containers in auto.cpp! Check it out if you are interested.
    // 我们在auto.cpp中讨论了更多风格化和可读性更好的遍历C++ STL
    // 容器的方法！如果你感兴趣，可以查看一下。

    return 0;
}
