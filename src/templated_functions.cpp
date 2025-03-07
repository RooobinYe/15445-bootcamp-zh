/**
 * @file templated_functions.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for templated functions.
 * @brief 模板函数的教程代码。
 */

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>

// Templates are a language feature in C++ that allow you to write code that
// can work with multiple data types, without actually specifying those types.
// In C++, you can create both templated functions and templated classes. We'll
// talk about templated functions in this file.
// 模板是C++中的一种语言特性，允许你编写可以与多种数据类型
// 一起工作的代码，而无需实际指定这些类型。
// 在C++中，你可以创建模板函数和模板类。我们将
// 在本文件中讨论模板函数。

// Here is a basic templated function that adds two numbers.
// Syntax note: You will see code with both template<class T> and
// template<typename T>. Although these statements are equivalent, there are
// differences between the class and typename keywords. This blog article covers
// this difference, but you won't need to know this for the class:
// https://mariusbancila.ro/blog/2021/03/15/typename-or-class/
// 这是一个基本的模板函数，用于将两个数字相加。
// 语法说明：你会看到同时使用template<class T>和
// template<typename T>的代码。虽然这些语句是等价的，但
// class和typename关键字之间存在差异。这篇博客文章涵盖了
// 这个差异，但你在课程中不需要了解这一点：
// https://mariusbancila.ro/blog/2021/03/15/typename-or-class/
template<typename T>
T add(T a, T b) {
    return a + b;
}

// It is possible to pass multiple type names via templates into functions.
// This function will print both of these values out.
// 可以通过模板向函数传递多个类型名。
// 这个函数将打印这两个值。
template<typename T, typename U>
void print_two_values(T a, U b) {
    std::cout << a << " and " << b << std::endl;
}

// It is also possible to create specialized templated functions, that do
// different things for different types. Take the following contrived example,
// which prints the type if its a float type, but just prints hello world for
// all other types.
// 也可以创建特化的模板函数，对不同类型
// 做不同的事情。看下面这个人为的例子，
// 如果是float类型，它会打印类型，但对于所有
// 其他类型，它只打印hello world。
template<typename T>
void print_msg() {
    std::cout << "Hello world!\n";
}

// Specialized templated function, specialized on the float type.
// 特化的模板函数，专门针对float类型。
template<>
void print_msg<float>() {
    std::cout << "print_msg called with float type!\n";
}

// Lastly, template parameters do not have to be classes. Take this basic (yet
// very contrived) function that takes in a bool as a template parameter and
// does different things to the argument depending on the boolean argument.
// 最后，模板参数不必是类。看这个基本的（但非常
// 人为的）函数，它将bool作为模板参数，并根据
// 布尔参数对参数做不同的处理。
template<bool T>
int add3(int a) {
    if (T) {
        return a + 3;
    }

    return a;
}

int main() {
    // First, let's see the add function called on both ints and floats.
    // 首先，让我们看看add函数在整数和浮点数上的调用。
    std::cout << "Printing add<int>(3, 5): " << add<int>(3, 5) << std::endl;
    std::cout << "Printing add<float>(2.8, 3.7): " << add<float>(2.8, 3.7) << std::endl;

    // It is also possible for a templated function to interpret the type of its
    // arguments, although if you're a beginner in modern C++, it's preferred you
    // don't do this because then you might not be sure of the types being passed
    // into your functions.
    // 模板函数也可以解释其参数的类型，
    // 虽然如果你是现代C++的初学者，最好不要
    // 这样做，因为这样你可能不确定传递给
    // 函数的类型。
    std::cout << "Printing add(3, 5): " << add(3, 5) << std::endl;

    // Second, let's see the print_two_values function being called with two
    // different types.
    // 其次，让我们看看使用两种不同类型调用print_two_values函数。
    std::cout << "Printing print_two_values<int, float>(3, 3.2): ";
    print_two_values<int, float>(3, 3.2);

    // Let's see what happens when we called print_msg with and without the float
    // type being passed in. As expected, the first call to print_msg prints out
    // the general output, while the second one, with the float argument,
    // recognizes its type parameter and calls the specialized function.
    // 让我们看看当我们调用print_msg时，传入和不传入float类型
    // 会发生什么。正如预期的那样，对print_msg的第一次调用打印出
    // 一般输出，而第二次调用（带有float参数）识别其
    // 类型参数并调用特化函数。
    std::cout << "Calling print_msg<int>(): ";
    print_msg<int>();
    std::cout << "Calling print_msg<float>(): ";
    print_msg<float>();

    // add3 has the specified behavior for both a true and false templated
    // argument, as we can see here.
    // add3对于true和false模板参数都有指定的行为，
    // 如我们在这里看到的。
    std::cout << "Printing add3<true>(3): " << add3<true>(3) << std::endl;
    std::cout << "Printing add3<false>(3): " << add3<false>(3) << std::endl;

    // Lastly, it's important to note that most of these are contrived examples,
    // and it is possible to code some of these functions (e.g. passing a boolean
    // as an argument instead of a templated argument) without using templates.
    // However, in the class, you'll be seeing code similar to this in the
    // codebase, so it's good to understand templated functions in these contexts!
    // 最后，重要的是要注意这些大多是人为的例子，
    // 可以不使用模板来编写其中一些函数（例如，将布尔值
    // 作为参数而不是模板参数传递）。
    // 然而，在课程中，你会在代码库中看到类似这样的代码，
    // 所以在这些上下文中理解模板函数是很好的！

    return 0;
}
