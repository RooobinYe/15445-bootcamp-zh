/**
 * @file shared_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of a shared pointer.
 * @brief 共享指针使用的教程代码。
 */

// In this file, we'll talk about std::shared_ptr, which is a C++ smart pointer.
// See the intro of unique_ptr.cpp for an introduction on smart pointers.
// std::shared_ptr is a type of smart pointer that retains shared ownership of
// an object through a pointer. This means that multiple shared pointers can
// own the same object, and shared pointers can be copied.
// 在这个文件中，我们将讨论std::shared_ptr，它是一种C++智能指针。
// 关于智能指针的介绍，请参见unique_ptr.cpp的介绍部分。
// std::shared_ptr是一种通过指针保持对象共享所有权的智能指针类型。
// 这意味着多个共享指针可以拥有同一个对象，并且可以复制共享指针。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes std::shared_ptr functionality.
// 包含std::shared_ptr功能。
#include <memory>
// Includes the utility header for std::move.
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

// Function that modifies a Point object inside a shared pointer
// by passing the shared pointer argument as a reference.
// 通过将共享指针参数作为引用传递来修改共享指针内的Point对象的函数。
void modify_ptr_via_ref(std::shared_ptr<Point> &point) { point->SetX(15); }

// Function that modifies a Point object inside a shared pointer
// by passing the shared pointer argument as a rvalue reference.
// 通过将共享指针参数作为右值引用传递来修改共享指针内的Point对象的函数。
void modify_ptr_via_rvalue_ref(std::shared_ptr<Point> &&point) { point->SetY(645); }

void copy_shared_ptr_in_function(std::shared_ptr<Point> point) {
    std::cout << "Use count of shared pointer is " << point.use_count() << std::endl;
}

int main() {
    // This is how to initialize an empty shared pointer of type
    // std::shared_ptr<Point>.
    // 这是如何初始化一个std::shared_ptr<Point>类型的空共享指针。
    std::shared_ptr<Point> s1;
    // This is how to initialize a shared pointer with the default constructor.
    // 这是如何使用默认构造函数初始化共享指针。
    std::shared_ptr<Point> s2 = std::make_shared<Point>();
    // This is how to initialize a shared pointer with a custom constructor.
    // 这是如何使用自定义构造函数初始化共享指针。
    std::shared_ptr<Point> s3 = std::make_shared<Point>(2, 3);

    // The specific syntax for checking whether a smart pointer is empty is
    // covered in unique_ptr.cpp (line 56). Note that s1 is empty, while s2 and
    // s3 are not empty.
    // 检查智能指针是否为空的具体语法在unique_ptr.cpp（第56行）中有介绍。
    // 注意，s1是空的，而s2和s3不是空的。
    std::cout << "Pointer s1 is " << (s1 ? "not empty" : "empty") << std::endl;
    std::cout << "Pointer s2 is " << (s2 ? "not empty" : "empty") << std::endl;
    std::cout << "Pointer s3 is " << (s3 ? "not empty" : "empty") << std::endl;

    // It is possible to copy shared pointers via their copy assignment and copy
    // constructor operators. Using these copy operators will increase the
    // reference count of the overall object. Also, std::shared_ptr comes with
    // a method called use_count which keeps track of the number of objects
    // currently interacting with the same internal data as the current shared
    // pointer instance.
    // 可以通过它们的复制赋值和复制构造运算符复制共享指针。
    // 使用这些复制运算符将增加整体对象的引用计数。
    // 此外，std::shared_ptr带有一个名为use_count的方法，
    // 它跟踪当前与当前共享指针实例具有相同内部数据的对象数量。

    // First, the number of references to pointer s3 is obtained. This should be
    // 1 because s3 is the only object instance using the data in s3.
    // 首先，获取指针s3的引用数量。这应该是1，
    // 因为s3是唯一使用s3中数据的对象实例。
    std::cout << "Number of shared pointer object instances using the data in s3: " << s3.use_count() << std::endl;

    // Then, s4 is copy-constructed from s3.
    // This is copy-construction because it is the first time s4 appears.
    // 然后，s4从s3复制构造。
    // 这是复制构造，因为这是s4第一次出现。
    std::shared_ptr<Point> s4 = s3;

    // Now, the number of references to pointer s3's data should be 2, since both
    // s4 and s3 have access to s3's data.
    // 现在，指针s3数据的引用数应该是2，因为s4和s3都可以访问s3的数据。
    std::cout << "Number of shared pointer object instances using the data in s3 "
                 "after one copy: "
              << s3.use_count() << std::endl;

    // Then, s5 is copy-constructed from s4.
    // 然后，s5从s4复制构造。
    std::shared_ptr<Point> s5(s4);

    // Now, the number of references to pointer s3's data should be 3, since s5,
    // s4, and s3 have access to s3's data.
    // 现在，指针s3数据的引用数应该是3，因为s5、s4和s3都可以访问s3的数据。
    std::cout << "Number of shared pointer object instances using the data in s3 "
                 "after two copies: "
              << s3.use_count() << std::endl;

    // Modifying s3's data should also change the data in s4 and s5, since they
    // refer to the same object instance.
    // 修改s3的数据也应该改变s4和s5中的数据，因为它们引用相同的对象实例。
    s3->SetX(445);

    std::cout << "Printing x in s3: " << s3->GetX() << std::endl;
    std::cout << "Printing x in s4: " << s4->GetX() << std::endl;
    std::cout << "Printing x in s5: " << s5->GetX() << std::endl;

    // It is also possible to transfer ownership of a std::shared_ptr by moving
    // it. Note that the pointer is empty after the move has occurred.
    // 也可以通过移动来转移std::shared_ptr的所有权。
    // 注意，移动发生后，指针是空的。
    std::shared_ptr<Point> s6 = std::move(s5);

    // Note that s5 is now empty, s6 refers to the same data as s3 and s4, and
    // there are still 3 shared pointer instances with access to the same Point
    // instance data, not 4.
    // 注意，s5现在是空的，s6引用与s3和s4相同的数据，
    // 并且仍然有3个共享指针实例可以访问相同的Point实例数据，而不是4个。
    std::cout << "Pointer s5 is " << (s5 ? "not empty" : "empty") << std::endl;
    std::cout << "Number of shared pointer object instances using the data in s3 "
                 "after two copies and a move: "
              << s3.use_count() << std::endl;

    // Similar to unique pointers, shared pointers can also be passed by reference
    // and rvalue reference. See unique_ptr.cpp (line 89) for a information on
    // passing unique pointers by reference. See references.cpp for more
    // information on references. See move_semantics.cpp for more information on
    // rvalue references. Here, we present code below that calls functions that
    // modify s2 by passing a shared pointer as a reference and as a rvalue
    // reference.
    // 与唯一指针类似，共享指针也可以通过引用和右值引用传递。
    // 有关通过引用传递唯一指针的信息，请参见unique_ptr.cpp（第89行）。
    // 有关引用的更多信息，请参见references.cpp。
    // 有关右值引用的更多信息，请参见move_semantics.cpp。
    // 这里，我们展示了下面的代码，它通过将共享指针作为引用和右值引用传递来调用修改s2的函数。
    modify_ptr_via_ref(s2);
    modify_ptr_via_rvalue_ref(std::move(s2));

    // After running this code, s2 should have x = 15 and y = 645.
    // 运行此代码后，s2应该有x = 15和y = 645。
    std::cout << "Pointer s2 has x=" << s2->GetX() << " and y=" << s2->GetY() << std::endl;

    // Unlike unique pointers, shared pointers can also be passed by value. In
    // this case, the function contains its own copy of a shared pointer, which
    // destroys itself after the function is finished. In this example, before s2
    // is passed to the function by value, its use count is 1. While it is in the
    // function, its use count is 2, because there is another copy of s2's data in
    // the shared pointer instance in the function. After the function goes out of
    // scope, this object in the function is destroyed, and the use count returns
    // to 1.
    // 与唯一指针不同，共享指针也可以通过值传递。
    // 在这种情况下，函数包含自己的共享指针副本，
    // 该副本在函数完成后自行销毁。
    // 在这个例子中，在s2通过值传递给函数之前，
    // 它的使用计数是1。当它在函数中时，
    // 它的使用计数是2，因为在函数中的共享指针实例中
    // 有s2数据的另一个副本。函数超出范围后，
    // 函数中的这个对象被销毁，使用计数返回为1。
    std::cout << "Number of shared pointer object instances using the data in s2: " << s2.use_count() << std::endl;
    copy_shared_ptr_in_function(s2);
    std::cout << "Number of shared pointer object instances using the data in s2 "
                 "after calling copy_shared_ptr_in_function: "
              << s2.use_count() << std::endl;

    return 0;
}
