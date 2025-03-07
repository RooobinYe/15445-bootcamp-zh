/**
 * @file move_semantics.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for move semantics.
 * @brief 移动语义的教程代码。
 */

// Move semantics in C++ are a useful concept that allows for the efficient
// and optimized transfer of ownership of data between objects. One of the
// main goals of move semantics is to increase performance, since moving an
// object is faster and more efficient than deep copying the object.
// C++中的移动语义是一个有用的概念，它允许在对象之间高效
// 且优化地转移数据的所有权。移动语义的主要目标之一
// 是提高性能，因为移动对象比深度复制对象
// 更快且更高效。

// To understand move semantics, one must understand the concept of lvalues
// and rvalues. A simplified definition of lvalues is that lvalues are objects
// that refer to a location in memory. Rvalues are anything that is not a
// lvalue.
// 要理解移动语义，必须理解左值和右值的概念。
// 左值的简化定义是指那些引用内存位置的对象。
// 右值是任何不是左值的东西。

// std::move is the most common way of moving an object from one lvalue to
// another. std::move casts an expression to a rvalue. This allows for us to
// interact with a lvalue as a rvalue, and allows for the ownership to be
// transferred from one lvalue to another.
// std::move是将对象从一个左值移动到另一个左值的最常见方式。
// std::move将表达式转换为右值。这允许我们
// 将左值视为右值进行交互，并允许所有权从一个左值
// 转移到另一个左值。

// In the code below, we include some examples for identifying whether
// expressions in C++ are lvalues or rvalues, how to use std::move, and passing
// rvalues references into functions.
// 在下面的代码中，我们包含了一些例子，用于识别
// C++中的表达式是左值还是右值，如何使用std::move，以及
// 将右值引用传递给函数。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the utility header for std::move.
// 包含utility头文件以使用std::move。
#include <utility>
// Includes the header for std::vector. We'll cover vectors more in
// containers.cpp, but what suffices to know for now is that vectors are
// essentially dynamic arrays, and the type std::vector<int> is an array of
// ints. Mainly, vectors take up a non-negligible amount of memory, and are here
// to show the performance benefits of using std::move.
// 包含std::vector的头文件。我们将在containers.cpp中更详细地介绍向量，
// 但现在只需知道向量本质上是动态数组，
// 类型std::vector<int>是一个整数数组。
// 主要是，向量占用不可忽视的内存量，
// 这里展示使用std::move的性能优势。
#include <vector>

// Function that takes in a rvalue reference as an argument.
// It seizes ownership of the vector passed in, appends 3 to
// the back of it, and prints the values in the vector.
// 接收右值引用作为参数的函数。
// 它夺取传入向量的所有权，在其末尾
// 添加3，并打印向量中的值。
void move_add_three_and_print(std::vector<int> &&vec) {
    std::vector<int> vec1 = std::move(vec);
    vec1.push_back(3);
    for (const int &item: vec1) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

// Function that takes in a rvalue reference as an argument.
// It appends 3 to the back of the vector passed in as an argument,
// and prints the values in the vector. Notably, it does not seize
// ownership of the vector. Therefore, the argument passed in would
// still be usable in the callee context.
// 接收右值引用作为参数的函数。
// 它在作为参数传入的向量末尾添加3，
// 并打印向量中的值。值得注意的是，它不会夺取
// 向量的所有权。因此，传入的参数
// 在被调用者上下文中仍然可用。
void add_three_and_print(std::vector<int> &&vec) {
    vec.push_back(3);
    for (const int &item: vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    // Take this expression. Note that 'a' is a lvalue, since it's a variable that
    // refers to a specific space in memory (where 'a' is stored). 10 is a rvalue.
    // 看这个表达式。注意'a'是一个左值，因为它是一个变量，
    // 引用内存中的特定空间（存储'a'的地方）。10是一个右值。
    int a = 10;

    // Let's see a basic example of moving data from one lvalue to another.
    // We define a vector of integers here.
    // 让我们看一个将数据从一个左值移动到另一个左值的基本例子。
    // 这里我们定义了一个整数向量。
    std::vector<int> int_array = {1, 2, 3, 4};

    // Now, we move the values of this array to another lvalue.
    // 现在，我们将这个数组的值移动到另一个左值。
    std::vector<int> stealing_ints = std::move(int_array);

    // Rvalue references are references that refer to the data itself, as opposed
    // to a lvalue. Calling std::move on a lvalue (such as stealing_ints) will
    // result in the expression being cast to a rvalue reference.
    // 右值引用是指向数据本身的引用，与左值相对。
    // 在左值（如stealing_ints）上调用std::move将导致
    // 表达式被转换为右值引用。
    std::vector<int> &&rvalue_stealing_ints = std::move(stealing_ints);

    // However, note that after this, it is still possible to access the data in
    // stealing_ints, since that is the lvalue that owns the data, not
    // rvalue_stealing_ints.
    // 然而，请注意，在此之后，仍然可以访问stealing_ints中的数据，
    // 因为拥有数据的是左值stealing_ints，而不是rvalue_stealing_ints。
    std::cout << "Printing from stealing_ints: " << stealing_ints[1] << std::endl;

    // It is possible to pass in a rvalue reference into a function. However,
    // once the rvalue is moved from the lvalue in the caller context to a lvalue
    // in the callee context, it is effectively unusable to the caller.
    // Essentially, after move_add_three_and_print is called, we cannot use the
    // data in int_array2. It no longer belongs to the int_array2 lvalue.
    // 可以将右值引用传递给函数。但是，
    // 一旦右值从调用者上下文中的左值移动到被调用者上下文中的左值，
    // 对调用者来说它实际上是不可用的。
    // 本质上，在调用move_add_three_and_print后，我们不能使用
    // int_array2中的数据。它不再属于左值int_array2。
    std::vector<int> int_array2 = {1, 2, 3, 4};
    std::cout << "Calling move_add_three_and_print...\n";
    move_add_three_and_print(std::move(int_array2));

    // It would be unwise to try to do anything with int_array2 here. Uncomment
    // the code to try it out! (On my machine, this segfaults...) NOTE: THIS MIGHT
    // WORK FOR YOU. THIS DOES NOT MEAN THAT THIS IS WISE TO DO!
    // 在这里尝试对int_array2做任何事都是不明智的。取消注释
    // 代码来尝试一下！（在我的机器上，这会导致段错误...）注意：这可能
    // 在你的机器上可行。但这并不意味着这样做是明智的！
    // std::cout << int_array2[1] << std::endl;

    // If we don't move the lvalue in the caller context to any lvalue in the
    // callee context, then effectively the function treats the rvalue reference
    // passed in as a reference, and the lvalue in this context still owns the
    // vector data.
    // 如果我们不将调用者上下文中的左值移动到被调用者上下文中的任何左值，
    // 那么函数实际上将传入的右值引用视为引用，
    // 而在这个上下文中的左值仍然拥有向量数据。
    std::vector<int> int_array3 = {1, 2, 3, 4};
    std::cout << "Calling add_three_and_print...\n";
    add_three_and_print(std::move(int_array3));

    // As seen here, we can print from this array.
    // 如这里所见，我们可以从这个数组打印。
    std::cout << "Printing from int_array3: " << int_array3[1] << std::endl;

    return 0;
}
