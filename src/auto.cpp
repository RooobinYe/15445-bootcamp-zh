/**
 * @file auto.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of the auto keyword.
 * @brief auto关键字使用的教程代码。
 */

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（用于打印）以进行演示。
#include <iostream>
// Includes the std::set library.
// 包含std::set库。
#include <set>
// Includes the C++ string library.
// 包含C++字符串库。
#include <string>
// Includes the std::vector library.
// 包含std::vector库。
#include <vector>
// Includes the std::unordered map library.
// 包含std::unordered map库。
#include <unordered_map>


// The C++ auto keyword is a keyword that tells the compiler to infer the type
// of a declared variable via its initialization expression. It can be
// incredibly useful, as it allows for developer efficiency (where the developer
// no longer has to type out long, unruly type names). It is also useful in the
// context of for-each loops. However, using auto poses a risk where the
// developer may not be aware of the types they are using, and therefore at risk
// for buggy and non functional code. So be careful!
// C++ auto关键字是一个告诉编译器通过初始化表达式推断声明变量类型的关键字。
// 它非常有用，因为它提高了开发效率（开发者不再需要输入冗长、难以管理的类型名称）。
// 它在for-each循环的上下文中也很有用。然而，使用auto存在风险，
// 开发者可能不清楚他们正在使用的类型，因此可能导致错误和无法正常工作的代码。
// 所以要小心使用！

// Basic templated class with very long name, to show the usefulness of auto.
// 具有很长名称的基本模板类，用于展示auto的实用性。
template<typename T, typename U>
class Abcdefghijklmnopqrstuvwxyz {
public:
    Abcdefghijklmnopqrstuvwxyz(T instance1, U instance2) : instance1_(instance1), instance2_(instance2) {}

    void print() const { std::cout << "(" << instance1_ << "," << instance2_ << ")\n"; }

private:
    T instance1_;
    U instance2_;
};

// Templated function that returns an object of this class with a very long
// name.
// 模板函数，返回一个具有很长名称的类的对象。
template<typename T>
Abcdefghijklmnopqrstuvwxyz<T, T> construct_obj(T instance) {
    return Abcdefghijklmnopqrstuvwxyz<T, T>(instance, instance);
}

int main() {
    // The auto keyword is used to initialize the variable a. Here, the type
    // is inferred to be type int.
    // auto关键字用于初始化变量a。这里，类型被推断为int类型。
    auto a = 1;

    // Here are more examples of using auto to declare basic variables.
    // Depending on the IDE being used, it might say what types a, b, and c
    // are.
    // 以下是使用auto声明基本变量的更多示例。
    // 根据所使用的IDE，它可能会显示a、b和c的类型。
    auto b = 3.2;
    auto c = std::string("Hello");

    // auto is not particularly useful for these prior examples. As one can
    // see, typing int a = 1;, float b = 3.2;, and std::string c = "Hello";
    // does not take significant overhead. However, there will definitely
    // be cases where the type name is long and complicated, or when the
    // type name is heavily templated, and using auto may be helpful.
    // auto对于这些先前的示例并不特别有用。正如我们所见，
    // 输入int a = 1;、float b = 3.2;和std::string c = "Hello";
    // 并不会带来显著的开销。然而，肯定会有类型名称冗长复杂的情况，
    // 或者当类型名称高度模板化时，使用auto可能会有所帮助。
    Abcdefghijklmnopqrstuvwxyz<int, int> obj = construct_obj<int>(2);
    auto obj1 = construct_obj<int>(2);

    // Maybe for one line it does not seem all that convenient, but imagine
    // if using a class with a very long name was useful in the code for
    // an extended period of time. Then, I'd imagine it would save a lot of
    // typing time!
    // 也许对于一行代码来说，这看起来并不那么方便，但想象一下，
    // 如果在代码中长时间使用具有很长名称的类会很有用。
    // 那么，我认为它会节省大量的输入时间！

    // One important thing to note about the auto keyword is that it
    // defaults to copying objects, which can lower performance. Take the
    // following example where we construct a int vector, and want to
    // define a variable that is a reference to it.
    // 关于auto关键字需要注意的一个重要事项是，它默认会复制对象，
    // 这可能会降低性能。以下面的例子为例，我们构造一个int向量，
    // 并希望定义一个引用该向量的变量。
    std::vector<int> int_values = {1, 2, 3, 4};

    // The following code deep-copies int_values into copy_int_values,
    // since auto infers the type as std::vector<int>, not std::vector<int>&.
    // 以下代码将int_values深拷贝到copy_int_values中，
    // 因为auto推断类型为std::vector<int>，而不是std::vector<int>&。
    auto copy_int_values = int_values;

    // However, the following code defines ref_int_values, which is a reference
    // to int_values, and therefore does not deep copy the int_values vector.
    // 然而，以下代码定义了ref_int_values，它是int_values的引用，
    // 因此不会深拷贝int_values向量。
    auto &ref_int_values = int_values;

    // The auto keyword is also useful for iterating through C++ containers.
    // For instance, let's construct an unordered map with std::string keys
    // and int values, and discuss methods of iterating through it.
    // auto关键字对于遍历C++容器也很有用。
    // 例如，让我们构造一个具有std::string键和int值的无序映射，
    // 并讨论遍历它的方法。
    std::unordered_map<std::string, int> map;
    map.insert({{"andy", 445}, {"jignesh", 645}});

    // One method mentioned in unordered_map.cpp was to iterate through
    // a map by using a for loop with an iterator. Compare the readability
    // of the two loops below.
    // unordered_map.cpp中提到的一种方法是使用带有迭代器的for循环
    // 遍历映射。比较下面两个循环的可读性。
    std::cout << "Printing elements in map...\n";
    for (std::unordered_map<std::string, int>::iterator it = map.begin(); it != map.end(); ++it) {
        std::cout << "(" << it->first << "," << it->second << ")"
                  << " ";
    }
    std::cout << std::endl;

    std::cout << "Printing elements in map with auto...\n";
    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << "(" << it->first << "," << it->second << ")"
                  << " ";
    }
    std::cout << std::endl;

    // It is also possible to use the auto keyword to iterate over vectors
    // and sets.
    // 也可以使用auto关键字遍历向量和集合。
    std::vector<int> vec = {1, 2, 3, 4};
    std::cout << "Printing elements in vector with auto...\n";
    for (const auto &elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::set<int> set;
    for (int i = 1; i <= 10; ++i) {
        set.insert(i);
    }

    std::cout << "Printing elements in set with auto...\n";
    for (const auto &elem: set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Overall, auto is a useful C++ keyword that can be used to write code more
    // efficiently, and to write cleaner and more readable code.
    // Keep in mind that using auto to iterate through C++ containers is better
    // in practice, since it produces more readable code. However, if you're not
    // sure of the types that are being used, it is always okay to revert back
    // to figuring out the type yourself.
    // 总的来说，auto是一个有用的C++关键字，可以用来更高效地编写代码，
    // 并编写更简洁、更可读的代码。
    // 请记住，在实践中，使用auto遍历C++容器更好，因为它产生更可读的代码。
    // 然而，如果你不确定正在使用的类型，随时可以回到自己确定类型的方式。

    return 0;
}
