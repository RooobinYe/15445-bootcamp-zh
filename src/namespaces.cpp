/**
 * @file namespaces.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code on the usage of namespaces.
 * @brief 命名空间使用的教程代码。
 */

// Namespaces provide scope to identifiers (the names of functions, types,
// variables). They are used to organize code into logical groups (e.g. a
// library might be one namespace). They also can prevent naming collisons
// between different identifiers. For instance, the C++ standard library
// uses the std namespace. This is why the print function in C++ is identified
// by std::cout, because the cout function is declared in the std
// namespace. C++ uses the :: operator for scope resolution, and therefore
// it is useful in differentiating which namespace a function, type,
// or class is declared in.
// 命名空间为标识符（函数、类型、变量的名称）提供作用域。
// 它们用于将代码组织成逻辑组（例如，一个库可能是一个命名空间）。
// 它们还可以防止不同标识符之间的命名冲突。
// 例如，C++标准库使用std命名空间。这就是为什么C++中的打印函数被标识为
// std::cout，因为cout函数是在std命名空间中声明的。
// C++使用::运算符进行作用域解析，因此
// 它有助于区分函数、类型或类是在哪个命名空间中声明的。

// In this file, we will introduce namespaces, namespace syntax, the using
// keyword, and calling functions from other namespaces.
// 在本文件中，我们将介绍命名空间、命名空间语法、using
// 关键字，以及从其他命名空间调用函数。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>

// This is the syntax to declare a namespace.
// 这是声明命名空间的语法。
namespace ABC {
    // We define a function spam in the ABC namespace. This is used in line 57.
    // 我们在ABC命名空间中定义一个函数spam。这在57（80）行使用。
    void spam(int a) { std::cout << "Hello from ABC::spam: " << a << std::endl; }

    // namespace DEF is a nested namespace, because it is declared inside namespace
    // ABC. The syntax for declaring a nested namespace is identical to the syntax of
    // declaring a non-nested namespace.
    // 命名空间DEF是一个嵌套命名空间，因为它是在命名空间ABC内部声明的。
    // 声明嵌套命名空间的语法与声明非嵌套命名空间的语法相同。
    namespace DEF {
        // We define a function bar inside the N::M namespace.
        // 我们在ABC::DEF命名空间内定义一个函数bar。
        void bar(float a) { std::cout << "Hello from ABC::DEF::bar: " << a << std::endl; }

        // We define a function uses_bar inside the ABC::DEF namespace. However, since
        // bar is in the same namespace as uses_bar (they're both in the ABC::DEF
        // namespace), the function bar is just referred to by its name in the
        // function uses_bar.
        // 我们在ABC::DEF命名空间内定义一个函数uses_bar。然而，由于
        // bar与uses_bar在同一个命名空间中（它们都在ABC::DEF
        // 命名空间中），函数bar在uses_bar函数中
        // 仅通过其名称引用。
        void uses_bar(float a) {
            std::cout << "Hello from uses_bar: ";
            bar(a);
        }

        // We define a function uses_spam in the ABC::DEF namespace. To refer to
        // ABC::spam from the ABC::DEF namespace, we have no other option but to
        // refer to it by its full identifier. Attempting to refer to it by spam
        // will result in a compilation error, stating that no function called spam
        // or ABC::DEF::spam exists. Note that it is possible to refer to every
        // function by its full identifier, but doing this makes coding speed
        // inefficient.
        // 我们在ABC::DEF命名空间内定义一个函数uses_spam。要从
        // ABC::DEF命名空间引用ABC::spam，我们别无选择，只能
        // 通过其完整标识符引用它。尝试通过spam引用它
        // 将导致编译错误，指出不存在名为spam
        // 或ABC::DEF::spam的函数。请注意，可以通过完整标识符引用每个
        // 函数，但这样做会使编码效率
        // 降低。
        void uses_spam(int a) {
            std::cout << "Hello from uses_spam: ";
            ABC::spam(a);

            // Try uncommenting this code, which calls spam(a), here.
            // 尝试取消注释此代码，它在这里调用spam(a)。
            // spam(a);
        }
    } // namespace DEF

    // We define a function uses_DEF_bar inside the ABC namespace, but not inside the
    // DEF namespace. Since bar and uses_DEF_bar are both in the ABC namespace, the
    // function bar is referred to by DEF::bar (which is the differentiating
    // namespace) in the uses_DEF_bar function.
    // 我们在ABC命名空间内定义一个函数uses_DEF_bar，但不在
    // DEF命名空间内。由于bar和uses_DEF_bar都在ABC命名空间中，
    // 函数bar在uses_DEF_bar函数中通过DEF::bar（这是区分
    // 命名空间）引用。
    void uses_DEF_bar(float a) {
        std::cout << "Hello from uses_DEF_bar: ";
        DEF::bar(a);
    }
} // namespace ABC

// Both namespace A and namespace B have a function named foo with the same
// arguments and return value. This code will compile because overall, the
// two foo functions have different full identifiers, which are A::foo and
// B::foo.
// 命名空间A和命名空间B都有一个名为foo的函数，具有相同的
// 参数和返回值。这段代码将会编译，因为总体上，
// 两个foo函数有不同的完整标识符，即A::foo和
// B::foo。
namespace A {
    void foo(int a) { std::cout << "Hello from A::foo: " << a << std::endl; }
} // namespace A

namespace B {
    void foo(int a) { std::cout << "Hello from B::foo: " << a << std::endl; }

    void peloton(int a) { std::cout << "Hello from B::peloton: " << a << std::endl; }
} // namespace B

namespace C {
    void eggs(int a) { std::cout << "Hello from C::eggs: " << a << std::endl; }
} // namespace C


// One of the uses of the using keyword is to bring the current namespace into
// the current scope. This statement will bring namespace B into the current
// scope. This means that B::foo can be referred to as foo in code anywhere
// below this line of code. In main, we will see that B::foo can be referred to
// by B::foo and by foo.
// using关键字的一个用途是将当前命名空间引入
// 当前作用域。这条语句将把命名空间B引入当前
// 作用域。这意味着B::foo可以在此代码行下的任何地方
// 作为foo引用。在main中，我们将看到B::foo可以通过
// B::foo和foo引用。
using namespace B;

// Another use of the using keyword is to bring certain members of a namespace
// into the current scope. This statement will bring C::eggs into the current
// scope. This means that eggs can be referred to as eggs anywhere below this
// line of code.
// using关键字的另一个用途是将命名空间的某些成员
// 引入当前作用域。这条语句将把C::eggs引入当前
// 作用域。这意味着eggs可以在此代码行下的任何地方
// 作为eggs引用。
using C::eggs;

int main() {
    // The following line of code calls function spam (line 25). Calling spam(2)
    // will not work, as there is no function with the identifier spam, just
    // ABC::spam.
    // 以下代码行调用函数spam（第25行）。调用spam(2)
    // 将不起作用，因为没有标识符为spam的函数，只有
    // ABC::spam。
    ABC::spam(2);

    // The following line of code calls function bar.
    // 以下代码行调用函数bar。
    ABC::DEF::bar(4.45);

    // The following line of code calls uses_bar. As expected, uses_bar will
    // print "Hello from uses_bar", and then call ABC::DEF::bar.
    // 以下代码行调用uses_bar。如预期的那样，uses_bar将
    // 打印"Hello from uses_bar"，然后调用ABC::DEF::bar。
    ABC::DEF::uses_bar(6.45);

    // The following line of code calls uses_spam. As expected, uses_spam will
    // print "Hello from uses_spam", and then call ABC::spam.
    // 以下代码行调用uses_spam。如预期的那样，uses_spam将
    // 打印"Hello from uses_spam"，然后调用ABC::spam。
    ABC::DEF::uses_spam(37);

    // The following line of code calls uses_DEF_bar. As expected, uses_DEF_bar
    // will print "Hello from uses_DEF_bar", and then call ABC::DEF::bar.
    // 以下代码行调用uses_DEF_bar。如预期的那样，uses_DEF_bar
    // 将打印"Hello from uses_DEF_bar"，然后调用ABC::DEF::bar。
    ABC::uses_DEF_bar(3.12);

    // Now, let's talk the two foo functions. A::foo and B::foo are different
    // functions with the same argument, and yet they are allowed to coexist,
    // since they have different identifiers.
    // 现在，让我们讨论两个foo函数。A::foo和B::foo是不同的
    // 函数，具有相同的参数，但它们被允许共存，
    // 因为它们有不同的标识符。
    A::foo(122);
    B::foo(150);

    // However, since line 106 brought the B namespace into the current scope,
    // it is possible to access anything from the B namespace without the B
    // namespace identifier. Therefore, it is possible to call B::foo by
    // identifying it as foo.
    // 然而，由于第106行将B命名空间引入了当前作用域，
    // 可以在没有B命名空间标识符的情况下访问B命名空间中的任何内容。
    // 因此，可以通过将其标识为foo来调用B::foo。
    foo(440);

    // Likewise, since the entire namespace B was brought into the current
    // scope, it is also possible to refer to B::peloton, another function in
    // namespace B, as peloton.
    // 同样，由于整个命名空间B被引入了当前作用域，
    // 也可以将B::peloton（命名空间B中的另一个函数）
    // 称为peloton。
    peloton(721);

    // Keep in mind that using the using keyword to bring an entire namespace
    // to the current scope can be risky, as you can risk naming conflicts
    // if you are not careful. Therefore, we don't recommend you doing this.
    // However, it is possible to bring certain members of a namespace to
    // the current scope, such as the example on line 111. Here, we refer
    // to C::eggs by identifying it as eggs.
    // 请记住，使用using关键字将整个命名空间
    // 引入当前作用域可能有风险，因为如果不小心，
    // 你可能会冒命名冲突的风险。因此，我们不建议你这样做。
    // 然而，可以将命名空间的某些成员引入
    // 当前作用域，例如第111行的示例。在这里，我们
    // 通过将其标识为eggs来引用C::eggs。
    eggs(999);

    return 0;
}
