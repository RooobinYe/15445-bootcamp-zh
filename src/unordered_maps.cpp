/**
 * @file unordered_maps.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) unordered_map.
 * @brief C++标准库(STL) unordered_map的教程代码。
 */

// In this file, we will introduce the container std::unordered_map. We won't
// be able to cover every function in this container, but we will try to cover
// the bare bones of using this container. Look to the intro of vectors.cpp for
// a general overview of C++ STL containers.
// 在这个文件中，我们将介绍容器std::unordered_map。我们不可能
// 涵盖这个容器的每个函数，但我们会尝试涵盖
// 使用这个容器的基础知识。查看vectors.cpp的介绍部分，了解
// C++ STL容器的一般概述。

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
// Includes the unordered_map container library header.
// 包含unordered_map容器库头文件。
#include <unordered_map>
// Includes the C++ string library.
// 包含C++字符串库。
#include <string>
// Includes std::make_pair.
// 包含std::make_pair。
#include <utility>

int main() {
    // The std::unordered_map is a data structure that contains key-value pairs
    // with unique keys. Essentially, this means you can use it as a hash table
    // in your code.
    // std::unordered_map是一种包含键值对的数据结构，
    // 其中键是唯一的。本质上，这意味着你可以在代码中
    // 将其用作哈希表。

    // You can declare a unordered_map with string keys and int values with
    // the following syntax.
    // 你可以用以下语法声明一个带有字符串键和整数值的unordered_map。
    std::unordered_map<std::string, int> map;

    // The insert function is used to insert items into an unordered map.
    // insert函数用于将项目插入到无序映射中。
    map.insert({"foo", 2});

    // The insert function also takes in a std::pair as the argument. An
    // std::pair is a generic pair type, and you can create one by calling
    // std::make_pair with 2 arguments. std::make_pair is defined in the header
    // <utility>, and constructs an instance of the generic pair type.
    // insert函数也接受std::pair作为参数。std::pair
    // 是一种通用的对类型，你可以通过调用带有2个参数的
    // std::make_pair来创建一个。std::make_pair定义在头文件
    // <utility>中，它构造一个通用对类型的实例。
    map.insert(std::make_pair("jignesh", 445));

    // You can also insert multiple elements at a time by passing in an
    // initializer list of pairs.
    // 你也可以通过传入一个对的初始化列表来一次插入多个元素。
    map.insert({{"spam", 1}, {"eggs", 2}, {"garlic rice", 3}});

    // It is also possible to insert an element via array-style syntax,
    // even if the element did not exist previously.
    // 也可以通过数组样式的语法插入元素，
    // 即使该元素之前不存在。
    map["bacon"] = 5;

    // You can also update an element in the unordered map with the same syntax.
    // 你也可以用相同的语法更新无序映射中的元素。
    map["spam"] = 15;

    // The find function is used to find elements in an unordered map. It returns
    // an iterator pointing to the found element if the element exists, and
    // returns an iterator pointing to the end of the unordered map container
    // otherwise.
    // find函数用于在无序映射中查找元素。如果元素存在，
    // 它返回一个指向找到的元素的迭代器，否则返回一个
    // 指向无序映射容器末尾的迭代器。
    std::unordered_map<std::string, int>::iterator result = map.find("jignesh");
    if (result != map.end()) {
        // This is one way of accessing the key/value pair from the iterator.
        // 这是从迭代器访问键/值对的一种方式。
        std::cout << "Found key " << result->first << " with value " << result->second << std::endl;

        // Dereferencing the iterator is another method of accessing the key/value
        // pair from the iterator.
        // 解引用迭代器是从迭代器访问键/值对的另一种方法。
        std::pair<std::string, int> pair = *result;
        std::cout << "DEREF: Found key " << pair.first << " with value " << pair.second << std::endl;
    }

    // The count function returns the number of elements in an unordered map with
    // the specified key in the unordered map.
    // count函数返回无序映射中具有指定键的元素数量。
    size_t count = map.count("spam");
    if (count == 1) {
        std::cout << "A key-value pair with key spam exists in the unordered map.\n";
    }

    // The erase function deletes values from the unordered map. It can take a
    // key as an argument.
    // erase函数从无序映射中删除值。它可以接受一个键作为参数。
    map.erase("eggs");

    // We confirm that the eggs/2 key-value pair isn't in the map anymore.
    // 我们确认键值对eggs/2不再在映射中。
    if (map.count("eggs") == 0) {
        std::cout << "Key-value pair with key eggs does not exist in the unordered "
                     "map.\n";
    }

    // Additionally, if we want to erase an element at a certain position, we can
    // pass in an iterator to the erase function. The following code will erase
    // the key-value pair with the key "garlic rice". Note that std::next is an
    // iterator function that returns the successor of the iterator passed in as
    // its argument.
    // 此外，如果我们想删除某个位置的元素，我们可以
    // 将迭代器传递给erase函数。以下代码将删除
    // 键为"garlic rice"的键值对。注意，std::next是一个
    // 迭代器函数，返回作为其参数传入的迭代器的后继。
    map.erase(map.find("garlic rice"));

    // We confirm that garlic rice/3 key-value pair isn't in the map anymore.
    // 我们确认键值对garlic rice/3不再在映射中。
    if (map.count("garlic rice") == 0) {
        std::cout << "Key-value pair with key garlic rice does not exist in the "
                     "unordered map.\n";
    }

    // We can iterate through the unordered map elements via the unordered map
    // iterator. You cannot iterate through a unordered map via indexes of any
    // kind.
    // 我们可以通过无序映射迭代器遍历无序映射元素。
    // 你不能通过任何类型的索引遍历无序映射。
    std::cout << "Printing the elements of the iterator:\n";
    for (std::unordered_map<std::string, int>::iterator it = map.begin(); it != map.end(); ++it) {
        // We can access the element itself by dereferencing the iterator.
        // 我们可以通过解引用迭代器来访问元素本身。
        std::cout << "(" << it->first << ", " << it->second << "), ";
    }
    std::cout << "\n";

    // Just like std::vector, we can also iterate through the unordered map
    // via a for-each loop.
    // 就像std::vector一样，我们也可以通过for-each循环
    // 遍历无序映射。
    std::cout << "Printing the elements of the iterator with a for-each loop:\n";
    for (const std::pair<const std::string, int> &elem: map) {
        std::cout << "(" << elem.first << ", " << elem.second << "), ";
    }
    std::cout << "\n";

    // We discuss more stylistic and readable ways of iterating through C++ STL
    // containers in auto.cpp! Check it out if you are interested.
    // 我们在auto.cpp中讨论了更多风格化和可读性更好的遍历C++ STL
    // 容器的方法！如果你感兴趣，可以查看一下。

    return 0;
}
