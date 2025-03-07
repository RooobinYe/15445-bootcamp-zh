/**
 * @file unique_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of a unique pointer.
 * @brief 唯一指针使用的教程代码。
 */

// A smart pointer is a type of data structure used for memory management (and
// sometimes other features) in languages that don't have memory management
// built in (e.g C++) An example of a language that has memory management built
// in is any language with garbage collection, like Java or Python. Two of the
// modern C++ standard library's smart pointers (and the ones that you will use
// in class) are std::unique_ptr and std::shared_ptr. Both std::unique_ptr and
// std::shared_ptr handle memory allocation and deallocation automatically, and
// contain raw pointers under the hood. In other words, they are wrapper classes
// over raw pointers. In this file, we'll talk about std::unique_ptr.
// std::unique_ptr is a type of smart pointer that retains sole ownership of an
// object This means that no two instances of std::unique_ptr can manage the
// same object.
// 智能指针是一种用于内存管理（有时还包括其他功能）的数据结构，
// 用于那些没有内置内存管理的语言（例如C++）。
// 拥有内置内存管理的语言的例子是任何带有垃圾收集功能的语言，如Java或Python。
// 现代C++标准库的两种智能指针（也是你将在课堂上使用的指针）是std::unique_ptr和
// std::shared_ptr。std::unique_ptr和std::shared_ptr都可以自动处理内存分配和
// 释放，并在底层包含原始指针。换句话说，它们是对原始指针的包装类。
// 在本文件中，我们将讨论std::unique_ptr。
// std::unique_ptr是一种保持对象唯一所有权的智能指针类型，
// 这意味着没有两个std::unique_ptr实例可以管理同一个对象。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes std::unique_ptr functionality.
// 包含std::unique_ptr功能。
#include <memory>
// String library for printing help for demo purposes.
// 字符串库，用于帮助演示目的的打印。
#include <string>
// Including the utility header for std::move.
// 包含用于std::move的实用工具头文件。
#include <utility>

// Basic point class. (Will use later)
// 基本的点类。（稍后使用）
class Point {
public:
    Point() : x_(0), y_(0) {}
    Point(int x, int y) : x_(x), y_(y) {}
    inline int GetX() { return x_; }
    inline int GetY() { return y_; }
    inline void SetX(int x) { x_ = x; }
    inline void SetY(int y) { y_ = y; }

private:
    int x_;
    int y_;
};

// Function that takes in a unique pointer reference and changes its x value to
// 445.
// 接受唯一指针引用并将其x值更改为445的函数。
void SetXTo445(std::unique_ptr<Point> &ptr) { ptr->SetX(445); }

int main() {
    // This is how to initialize an empty unique pointer of type
    // std::unique_ptr<Point>.
    // 这是如何初始化一个std::unique_ptr<Point>类型的空唯一指针。
    std::unique_ptr<Point> u1;
    // This is how to initialize a unique pointer with the default constructor.
    // 这是如何使用默认构造函数初始化唯一指针。
    std::unique_ptr<Point> u2 = std::make_unique<Point>();
    // This is how to initialize a unique pointer with a custom constructor.
    // 这是如何使用自定义构造函数初始化唯一指针。
    std::unique_ptr<Point> u3 = std::make_unique<Point>(2, 3);

    // Here, for std::unique_ptr instance u, we use the statement (u ? "not empty"
    // : "empty") to determine if the pointer u contains managed data. The main
    // gist of this is that the std::unique_ptr class has a conversion function on
    // its objects to a boolean type, and so this function is called whenever we
    // treat the std::unique_ptr as a boolean. For instance, this can be used in
    // the following example.
    // 在这里，对于std::unique_ptr实例u，我们使用语句(u ? "not empty" : "empty")
    // 来确定指针u是否包含托管数据。主要要点是std::unique_ptr类
    // 对其对象有一个转换为布尔类型的函数，因此每当我们将std::unique_ptr
    // 视为布尔值时，就会调用此函数。例如，这可以在以下示例中使用。
    if (u1) {
        // This won't print because u1 is empty.
        // 这不会打印，因为u1是空的。
        std::cout << "u1's value of x is " << u1->GetX() << std::endl;
    }

    if (u2) {
        // This will print because u2 is not empty, and contains a managed Point
        // instance.
        // 这将打印，因为u2不是空的，并且包含一个托管的Point实例。
        std::cout << "u2's value of x is " << u2->GetX() << std::endl;
    }

    // Note that u1 is empty and u2 and u3 are not empty, since they were
    // initialized with a Point instance.
    // 注意，u1是空的，而u2和u3不是空的，因为它们是用Point实例初始化的。
    std::cout << "Pointer u1 is " << (u1 ? "not empty" : "empty") << std::endl;
    std::cout << "Pointer u2 is " << (u2 ? "not empty" : "empty") << std::endl;
    std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;

    // Since instances of std::unique_ptr can have only one owner, it has no copy
    // constructor. Therefore, this code won't compile. Uncomment it to try!
    // 由于std::unique_ptr的实例只能有一个所有者，它没有复制构造函数。
    // 因此，这段代码不会编译。取消注释试试！
    // std::unique_ptr<Point> u4 = u3;

    // However, it's possible to transfer ownership of unique pointers via
    // std::move.
    // 然而，可以通过std::move传输唯一指针的所有权。
    std::unique_ptr<Point> u4 = std::move(u3);

    // Note that because u3 is an lvalue, it no longer contains any managed
    // object. It is an empty unique pointer. Let's retest for emptyness.
    // 注意，因为u3是一个左值，它不再包含任何托管对象。
    // 它是一个空的唯一指针。让我们重新测试是否为空。
    std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;
    std::cout << "Pointer u4 is " << (u4 ? "not empty" : "empty") << std::endl;

    // Lastly, let's talk about how to pass std::unique_ptr instances as arguments
    // to functions. Mainly, you should pass it as a reference so that the
    // ownership doesn't change. You can see this as an example in the function
    // SetXTo445 (line 44 in this file).
    // 最后，让我们谈谈如何将std::unique_ptr实例作为参数传递给函数。
    // 主要是，你应该将其作为引用传递，这样所有权就不会改变。
    // 你可以在函数SetXTo445中看到这个例子（本文件中的第44行）。
    SetXTo445(u4);

    // Now, let's print the x value of u4 to confirm that the change occured, but
    // the ownership of the Point instance has been retained to u4.
    // 现在，让我们打印u4的x值，以确认变化已经发生，
    // 但Point实例的所有权仍然保留给u4。
    std::cout << "Pointer u4's x value is " << u4->GetX() << std::endl;

    return 0;
}
