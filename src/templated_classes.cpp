/**
 * @file templated_classes.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for templated classes.
 * @brief 模板类的教程代码。
 */

// Includes std::cout (printing).
// 包含std::cout（打印）。
#include <iostream>

// Templates can be also used to implement classes. For instance, here is a
// basic templated class that stores one element of a templated type and
// prints it when the print function is called.
// 模板也可以用于实现类。例如，这里是一个
// 基本的模板类，它存储一个模板类型的元素，
// 当调用print函数时打印它。
template<typename T>
class Foo {
public:
    Foo(T var) : var_(var) {}
    void print() { std::cout << var_ << std::endl; }

private:
    T var_;
};

// You can also pass in multiple type names via templates into classes.
// For instance, here's another basic templated class that stores two
// elements of a templated type and prints them when the print function
// is called.
// 你也可以通过模板向类传递多个类型名。
// 例如，这里有另一个基本的模板类，它存储两个
// 模板类型的元素，当调用print函数时打印它们。
template<typename T, typename U>
class Foo2 {
public:
    Foo2(T var1, U var2) : var1_(var1), var2_(var2) {}
    void print() { std::cout << var1_ << " and " << var2_ << std::endl; }

private:
    T var1_;
    U var2_;
};

// It is also possible to create specialized templated classes, that do
// different things for different types. Take the following contrived example,
// which instantiates a class with a print function that outputs the value of
// the variable stored if it's any other type but float. If the class is
// instantiated with a float type, it prints out hello float and the variable
// the class stores in its var_ field.
// 也可以创建特化的模板类，对不同类型做
// 不同的事情。看下面这个人为的例子，
// 它实例化一个带有print函数的类，如果它是除float之外的任何其他类型，
// 该函数输出存储的变量的值。如果类是
// 用float类型实例化的，它会打印出hello float和
// 类在其var_字段中存储的变量。
template<typename T>
class FooSpecial {
public:
    FooSpecial(T var) : var_(var) {}
    void print() { std::cout << var_ << std::endl; }

private:
    T var_;
};

// Specialized templated class, specialized on the float type.
// 特化的模板类，专门针对float类型。
template<>
class FooSpecial<float> {
public:
    FooSpecial(float var) : var_(var) {}
    void print() { std::cout << "hello float! " << var_ << std::endl; }

private:
    float var_;
};

// Template parameters don't have to be types. They can also be values!
// 模板参数不必是类型。它们也可以是值！
template<int T>
class Bar {
public:
    Bar() {}
    void print_int() { std::cout << "print int: " << T << std::endl; }
};

int main() {
    // First, let us construct an object from a templated class. The Foo
    // class template is instantiated with an int template argument. This
    // would make a's type class Foo<int> instead of Foo. a's print
    // function works as expected.
    // 首先，让我们从模板类构造一个对象。Foo
    // 类模板用int模板参数实例化。这
    // 会使a的类型为Foo<int>而不是Foo。a的print
    // 函数按预期工作。
    Foo<int> a(3);
    std::cout << "Calling print on Foo<int> a(3): ";
    a.print();

    // It is also possible for a templated class to interpret the type
    // of its arguments. Once again, if you're a beginner, think twice
    // before doing this if you are unsure of the types you are
    // instantiating your class with.
    // 模板类也可以解释其参数的类型。
    // 再次强调，如果你是初学者，如果你不确定
    // 用来实例化类的类型，在这样做之前要三思。
    Foo b(3.4f);
    std::cout << "Calling print on Foo b(3.4f): ";
    b.print();

    // Second, we construct an object from a templated class with multiple
    // type arguments.
    // 其次，我们从具有多个类型参数的模板类构造一个对象。
    Foo2<int, float> c(3, 3.2f);
    std::cout << "Calling print on Foo2<int, float> c(3, 3.2f): ";
    c.print();

    // Let's see what happens when we instantiate FooSpecial both with
    // and without the float type argument. As expected when we call
    // print from d, it prints the variable and not "hello float".
    // When we call print from e, which is an instance of the
    // instantiated FooSpecial<float> class, it prints hello float!
    // 让我们看看当我们同时用和不用float类型参数
    // 实例化FooSpecial时会发生什么。正如预期的那样，当我们
    // 从d调用print时，它打印变量而不是"hello float"。
    // 当我们从e调用print时，e是实例化的
    // FooSpecial<float>类的实例，它打印hello float！
    FooSpecial<int> d(5);
    std::cout << "Calling print on FooSpecial<int> d(5): ";
    d.print();

    FooSpecial<float> e(4.5);
    std::cout << "Calling print on FooSpecial<float> e(4.5): ";
    e.print();

    // Lastly, let's see what happens when we construct an object from a
    // templated class with non-type arguments.
    // 最后，让我们看看当我们从带有非类型参数的
    // 模板类构造对象时会发生什么。
    Bar<150> f;
    std::cout << "Calling print_int on Bar<150> f: ";
    f.print_int();

    // Once again, these are contrived examples, but it is still important
    // to understand them you'll be seeing code similar to this in the Bustub
    // codebase, so it's good to understand templated classes in these contexts!
    // 再次强调，这些是人为的例子，但理解它们仍然很重要，
    // 你将在Bustub代码库中看到类似这样的代码，
    // 所以在这些上下文中理解模板类是很好的！

    return 0;
}
