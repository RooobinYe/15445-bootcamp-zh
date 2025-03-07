/**
 * @file references.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for references.
 * @brief 引用的教程代码。
 */

// A reference in C++ is a method of creating an alias to a variable, where
// these aliases refer to the same data in memory. References are useful for
// keeping track of state, passing arguments into functions, and for general
// performance improvements. In general, it is important to understand
// references to do well in this class.
// 在C++中，引用是创建变量别名的一种方法，这些别名引用内存中的相同数据。
// 引用对于跟踪状态、向函数传递参数以及一般性能改进都很有用。
// 总的来说，理解引用对于在这门课程中取得好成绩很重要。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>

// A function that takes an int reference and adds 3 to it.
// 一个接收整数引用并给它加3的函数。
void add_three(int &a) { a = a + 3; }

int main() {
    // Take this expression. Note that b has type int& (int reference),
    // since it is a reference to a. This means that a and b both refer to the
    // same data. You can declare references by setting your variables type via
    // the single ampersand syntax.
    // 看这个表达式。注意b的类型是int&（整数引用），
    // 因为它是a的引用。这意味着a和b都引用相同的数据。
    // 你可以通过使用单个&符号语法设置变量类型来声明引用。
    int a = 10;
    int &b = a;

    // As stated, if we try to print b, we will get 10.
    // 如前所述，如果我们尝试打印b，将得到10。
    std::cout << "b is " << b << std::endl;

    // References can also be passed into functions. Take the function add_three,
    // which takes in an int reference and adds 3 to it. If we call this function,
    // on a, since a is being taken as a reference, then a's value in the caller
    // context will change value.
    // 引用也可以传递给函数。以add_three函数为例，
    // 它接收一个整数引用并给它加3。如果我们在a上调用这个函数，
    // 由于a被当作引用传入，那么调用者上下文中a的值也会改变。
    add_three(a);
    std::cout << "a is " << a << std::endl;

    return 0;
}
