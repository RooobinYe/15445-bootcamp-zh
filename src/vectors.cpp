/**
 * @file vectors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) vectors.
 * @brief C++标准库(STL)向量的教程代码。
 */

// The C++ STL contains a container library, which is a generic collection of
// data structure and algorithm implementations that allow users to manipulate
// data structures like stacks, queues, and hash tables easily. Each container
// has its own header and usage. In the C++ standard (up to C++ 23), there are
// currently 20 containers, which is far too many to cover here well. In this
// file, we will introduce the container std::vector. The std::vector container
// is essentially a generic dynamic array (or unbounded array). We won't be
// able to cover every function in this container, but we will try to cover the
// basics of using this container.
// C++ STL包含一个容器库，它是数据结构和算法实现的通用集合，
// 允许用户轻松操作栈、队列和哈希表等数据结构。每个容器
// 都有自己的头文件和用法。在C++标准（截至C++ 23）中，
// 目前有20个容器，这里无法很好地全部涵盖。在这个
// 文件中，我们将介绍容器std::vector。std::vector容器
// 本质上是一个通用的动态数组（或无界数组）。我们不可能
// 涵盖这个容器的每个函数，但我们会尝试涵盖
// 使用这个容器的基础知识。

// There is documentation on all the other functions, and other containers on
// https://en.cppreference.com/w/cpp/container. You will definitely need this
// resource as you complete the assignments in this class, so you should check
// it out!
// 所有其他函数和其他容器的文档都可以在
// https://en.cppreference.com/w/cpp/container 找到。在完成本课程的
// 作业时，你肯定需要这个资源，所以你应该查看一下！

// Includes std::remove_if to remove elements from vectors.
// 包含std::remove_if用于从向量中移除元素。
#include <algorithm>
// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the vector container library header.
// 包含向量容器库头文件。
#include <vector>

// Basic point class. (Will use later)
// 基本的点类。（稍后使用）
class Point {
public:
    Point() : x_(0), y_(0) { std::cout << "Default constructor for the Point class is called.\n"; }

    Point(int x, int y) : x_(x), y_(y) { std::cout << "Custom constructor for the Point class is called.\n"; }

    inline int GetX() const { return x_; }
    inline int GetY() const { return y_; }
    inline void SetX(int x) { x_ = x; }
    inline void SetY(int y) { y_ = y; }
    void PrintPoint() const { std::cout << "Point value is (" << x_ << ", " << y_ << ")\n"; }

private:
    int x_;
    int y_;
};

// A utility function to print the elements of an int vector. The code for this
// should be understandable and similar to the code iterating through elements
// of a vector in the main function.
// 一个打印整数向量元素的实用函数。这段代码应该
// 容易理解，并且与主函数中遍历向量元素的代码类似。
void print_int_vector(const std::vector<int> &vec) {
    for (const int &elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    // We can declare a Point vector with the following syntax.
    // 我们可以用以下语法声明一个Point向量。
    std::vector<Point> point_vector;

    // It is also possible to initialize the vector via an initializer list.
    // 也可以通过初始化列表初始化向量。
    std::vector<int> int_vector = {0, 1, 2, 3, 4, 5, 6};

    // There are two functions for appending data to the back of the vector. They
    // are push_back and emplace_back. Generally, emplace_back is slightly faster,
    // since it forwards the constructor arguments to the object's constructor and
    // constructs the object in place, while push_back constructs the object, then
    // moves it to the memory in the vector. We can see this here where we add two
    // Point objects to our vector.
    // 有两个函数用于将数据追加到向量的末尾。它们是
    // push_back和emplace_back。通常，emplace_back稍微快一些，
    // 因为它将构造函数参数转发给对象的构造函数并
    // 就地构造对象，而push_back构造对象，然后
    // 将其移动到向量中的内存。我们可以在这里看到，我们添加了两个
    // Point对象到我们的向量中。
    std::cout << "Appending to the point_vector via push_back:\n";
    point_vector.push_back(Point(35, 36));
    std::cout << "Appending to the point_vector via emplace_back:\n";
    point_vector.emplace_back(37, 38);

    // Let's just add more items to the back of our point_vector.
    // 让我们再向point_vector的末尾添加更多项目。
    point_vector.emplace_back(39, 40);
    point_vector.emplace_back(41, 42);

    // There are many ways to iterate through a vector. For instance, we can
    // iterate through it's indices via the following for loop. Note that it is
    // good practice to use an unsigned int type for array or vector indexes.
    // 有很多方法可以遍历向量。例如，我们可以
    // 通过以下for循环遍历其索引。注意，对于数组或向量索引，
    // 使用无符号整数类型是一个好习惯。
    std::cout << "Printing the items in point_vector:\n";
    for (size_t i = 0; i < point_vector.size(); ++i) {
        point_vector[i].PrintPoint();
    }

    // We can also iterate through it via a for-each loop. Note that I use
    // references to iterate through it so that the items we iterate through are
    // the items in the original vector. If we iterate through references of the
    // vector elements, we can also modify the data in the vector.
    // 我们也可以通过for-each循环遍历它。注意，我使用
    // 引用来遍历它，这样我们遍历的项目就是
    // 原始向量中的项目。如果我们遍历向量元素的引用，
    // 我们也可以修改向量中的数据。
    for (Point &item: point_vector) {
        item.SetY(445);
    }

    // Let's see if our changes went through. Note that I use the const reference
    // syntax to ensure that the data I'm accessing is read only.
    // 让我们看看我们的更改是否生效。注意，我使用const引用
    // 语法来确保我访问的数据是只读的。
    for (const Point &item: point_vector) {
        item.PrintPoint();
    }

    // Now, we show how to erase elements from a vector. First, we can erase
    // elements by their position via the erase function. For instance, if we want
    // to delete int_vector[2], we can call the following function with the
    // following arguments. The argument passed into this erase function has
    // the type std::vector<int>::iterator. An iterator for a C++ STL container
    // is an object that points to an element within the container. For instance,
    // int_vector.begin() is an iterator object that points to the first element
    // in the vector. The vector iterator also has a plus operator that takes
    // a vector iterator and an integer. The plus operator will increase the
    // index of the element that the iterator is pointing to by the number passed
    // in. Therefore, int_vector.begin() + 2 is pointing to the third element in
    // the vector, or the element at int_vector[2].
    // If you are confused about iterators, it may be helpful to read the header of
    // iterator.cpp.
    // 现在，我们展示如何从向量中删除元素。首先，我们可以通过
    // erase函数按位置删除元素。例如，如果我们想
    // 删除int_vector[2]，我们可以使用以下参数调用以下函数。
    // 传递给这个erase函数的参数具有类型std::vector<int>::iterator。
    // C++ STL容器的迭代器是一个指向容器内元素的对象。
    // 例如，int_vector.begin()是一个指向向量中第一个元素的
    // 迭代器对象。向量迭代器还有一个加法运算符，它接受
    // 一个向量迭代器和一个整数。加法运算符将增加
    // 迭代器指向的元素的索引，增加的数量是传入的数字。
    // 因此，int_vector.begin() + 2指向向量中的第三个元素，
    // 或者说是int_vector[2]处的元素。
    // 如果你对迭代器感到困惑，阅读iterator.cpp的头部可能会有所帮助。
    int_vector.erase(int_vector.begin() + 2);
    std::cout << "Printing the elements of int_vector after erasing "
                 "int_vector[2] (which is 2)\n";
    print_int_vector(int_vector);

    // We can also erase elements in a range via the erase function. If we want to
    // delete elements starting from index 1 to the end of the array, then we can
    // do so the following. Note that int_vector.end() is an iterator pointing to
    // the end of the vector. It does not point to the last valid index of the
    // vector. It points to the end of a vector and cannot be accessed for data.
    // 我们也可以通过erase函数删除一个范围内的元素。如果我们想
    // 删除从索引1到数组末尾的元素，那么我们可以
    // 这样做。注意，int_vector.end()是一个指向
    // 向量末尾的迭代器。它不指向向量的最后一个有效索引。
    // 它指向向量的末尾，不能用于访问数据。
    int_vector.erase(int_vector.begin() + 1, int_vector.end());
    std::cout << "Printing the elements of int_vector after erasing all elements "
                 "from index 1 through the end\n";
    print_int_vector(int_vector);

    // We can also erase values via filtering, i.e. erasing values if they meet a
    // conditional. We can do so by importing another library, the algorithm
    // library, which gives us the std::remove_if function, which removes all
    // elements meeting a conditional from an iterator range. This does seem
    // awfully complicated, but the code can be summarized as follows.
    // std::remove_if takes in 3 arguments. Two of those arguments indicate the
    // range of elements that we should filter. These are given by
    // point_vector.begin() and point_vector.end(), which are iterators that point
    // to the beginning and the end of a vector respectively. Therefore, when we
    // pass these in, we are implying that we want the whole vector filtered.
    // The third argument is a conditional lambda type (see the std::function
    // library in C++, or at
    // https://en.cppreference.com/w/cpp/utility/functional/function), that takes
    // in one argument, which is supposed to represent each element in the vector
    // that we are filtering. This function should return a boolean that is true
    // if the element is to be filtered out and false otherwise. std::remove_if
    // returns an iterator pointing to the first element in the container that
    // should be eliminated. Keep in mind that it swaps elements as needed,
    // partitioning the elements that need to be deleted after the iterator value
    // it returns. When erase is called, it deletes only the elements that
    // remove_if has partitioned away to be deleted, up to the end of the vector.
    // This outer erase takes a range argument, as we saw in the previous example.
    // 我们也可以通过过滤来删除值，即如果值满足条件就删除它们。
    // 我们可以通过导入另一个库，算法库，来做到这一点，
    // 它给我们提供了std::remove_if函数，该函数从迭代器范围中
    // 删除所有满足条件的元素。这看起来非常复杂，
    // 但代码可以总结如下。
    // std::remove_if接受3个参数。其中两个参数表示
    // 我们应该过滤的元素范围。这些由
    // point_vector.begin()和point_vector.end()给出，它们是分别指向
    // 向量开始和结束的迭代器。因此，当我们
    // 传入这些时，我们暗示我们想要过滤整个向量。
    // 第三个参数是一个条件lambda类型（参见C++中的std::function
    // 库，或者
    // https://en.cppreference.com/w/cpp/utility/functional/function），它接受
    // 一个参数，该参数应该表示我们正在过滤的向量中的每个元素。
    // 如果元素要被过滤掉，这个函数应该返回true，否则返回false。
    // std::remove_if返回一个指向容器中应该被删除的第一个元素的迭代器。
    // 请记住，它会根据需要交换元素，
    // 将需要删除的元素划分到它返回的迭代器值之后。
    // 当调用erase时，它只删除remove_if已经划分出来要删除的元素，
    // 直到向量的末尾。
    // 这个外部erase接受一个范围参数，就像我们在前面的例子中看到的那样。
    point_vector.erase(std::remove_if(point_vector.begin(), point_vector.end(),
                                      [](const Point &point) { return point.GetX() == 37; }),
                       point_vector.end());

    // After calling remove here, we should see that three elements remain in our
    // point vector. Only the one with value (37, 445) is deleted.
    // 在这里调用remove后，我们应该看到我们的point向量中
    // 剩下三个元素。只有值为(37, 445)的那个被删除了。
    std::cout << "Printing the point_vector after (37, 445) is erased:\n";
    for (const Point &item: point_vector) {
        item.PrintPoint();
    }

    // We discuss more stylistic and readable ways of iterating through C++ STL
    // containers in auto.cpp! Check it out if you are interested.
    // 我们在auto.cpp中讨论了更多风格化和可读性更好的遍历C++ STL
    // 容器的方法！如果你感兴趣，可以查看一下。

    return 0;
}
