/**
 * @file move_constructors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for move constructors and move assignment operators.
 * @brief 移动构造函数和移动赋值运算符的教程代码。
 */

// Move constructors and move assignment operators are methods implemented
// inside of classes to effectively move resources from one object to the
// other, typically using std::move. These class methods take in another
// object of the same type, and move its resources to the instance
// where the method is called. In this file, we will explore implementing
// and using move constructors and move assignment operators.
// 移动构造函数和移动赋值运算符是在类内部实现的方法，
// 用于有效地将资源从一个对象移动到另一个对象，
// 通常使用std::move。这些类方法接收同类型的另一个对象，
// 并将其资源移动到调用该方法的实例中。
// 在本文件中，我们将探讨移动构造函数和移动赋值运算符的实现和使用。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the utility header for std::move.
// 包含std::move的实用工具头文件。
#include <utility>
// Includes the C++ string library.
// 包含C++字符串库。
#include <string>
// Includes the header for uint32_t.
// 包含uint32_t的头文件。
#include <cstdint>
// Includes the header for std::vector. We'll cover vectors more in
// containers.cpp, but what suffices to know for now is that vectors are
// essentially dynamic arrays, and the type std::vector<std::string> is an array
// of strings. Mainly, vectors take up a non-negligible amount of memory, and
// are here to show the performance benefits of using std::move.
// 包含std::vector的头文件。我们将在containers.cpp中更详细地介绍向量，
// 但现在只需知道向量本质上是动态数组，类型std::vector<std::string>是一个字符串数组。
// 主要是，向量占用不可忽视的内存，
// 这里展示了使用std::move的性能优势。
#include <vector>

// Basic person class, with an implemented move constructor and move assignment
// operator, and a deleted copy constructor and copy assignment operator. This
// means that once an Person object is instantiated, it cannot be copied. It
// must be moved from one lvalue to another. Classes without copy operators are
// useful when it is imperative to only have one defined instance of a class.
// For instance, if a class manages a dynamically allocated memory block, then
// creating more than one instance of this class, without proper handling, can
// result in double deletion or memory leaks.
// 基本的Person类，实现了移动构造函数和移动赋值运算符，
// 并删除了复制构造函数和复制赋值运算符。这意味着
// 一旦实例化了Person对象，就不能复制它。它
// 必须从一个左值移动到另一个左值。没有复制运算符的类
// 在只需要一个定义的类实例时非常有用。
// 例如，如果一个类管理动态分配的内存块，那么
// 创建此类的多个实例，如果没有适当的处理，可能
// 导致双重删除或内存泄漏。
class Person {
public:
    Person() : age_(0), nicknames_({}), valid_(true) {}

    // Keep in mind that this constructor takes in a std::vector<std::string>
    // rvalue. This makes the constructor more efficient because it doesn't deep
    // copy the vector instance when constructing the person object.
    // 请记住，此构造函数接收std::vector<std::string>右值。
    // 这使构造函数更高效，因为在构造Person对象时
    // 不会深拷贝向量实例。
    Person(uint32_t age, std::vector<std::string> &&nicknames) :
        age_(age), nicknames_(std::move(nicknames)), valid_(true) {}

    // Move constructor for class Person. It takes in a rvalue with type Person,
    // and moves the contents of the rvalue passed in as an argument to this
    // Person object instance. Note the usage of std::move. In order to ensure
    // that nicknames in object person is moved, and not deep copied, we use
    // std::move. std::move will cast the lvalue person.nicknames_ to an rvalue,
    // which represents the value itself. Also note that I don't call std::move
    // on the age_ field. Since it's an integer type, it's too small to incur a
    // significant copying cost. Generally, for numeric types, it's okay to copy
    // them, but for other types, such as strings and object types, one should
    // move the class instance unless copying is necessary.
    // Person类的移动构造函数。它接收一个类型为Person的右值，
    // 并将作为参数传入的右值的内容移动到这个
    // Person对象实例。注意std::move的使用。为了确保
    // 对象person中的nicknames被移动而不是深拷贝，我们使用
    // std::move。std::move将左值person.nicknames_转换为右值，
    // 代表值本身。还要注意，我没有在age_字段上调用std::move。
    // 因为它是一个整数类型，太小，不会产生
    // 显著的复制成本。通常，对于数值类型，复制它们是可以的，
    // 但对于其他类型，如字符串和对象类型，应该
    // 移动类实例，除非必须复制。
    Person(Person &&person) : age_(person.age_), nicknames_(std::move(person.nicknames_)), valid_(true) {
        std::cout << "Calling the move constructor for class Person.\n";
        // The moved object's validity tag is set to false.
        // 移动对象的有效性标记设置为false。
        person.valid_ = false;
    }

    // Move assignment operator for class Person.
    // Person类的移动赋值运算符。
    Person &operator=(Person &&other) {
        std::cout << "Calling the move assignment operator for class Person.\n";
        age_ = other.age_;
        nicknames_ = std::move(other.nicknames_);
        valid_ = true;

        // The moved object's validity tag is set to false.
        // 移动对象的有效性标记设置为false。
        other.valid_ = false;
        return *this;
    }

    // We delete the copy constructor and the copy assignment operator,
    // so this class cannot be copy-constructed.
    // 我们删除复制构造函数和复制赋值运算符，
    // 因此不能复制构造此类。
    Person(const Person &) = delete;
    Person &operator=(const Person &) = delete;

    uint32_t GetAge() { return age_; }

    // This ampersand at the return type implies that we return a reference
    // to the string at nicknames_[i]. This also implies that we don't copy
    // the resulting string, and the memory address this returns under the
    // hood is actually the one pointing to the nicknames_ vector's memory.
    // 返回类型中的这个&符号表示我们返回nicknames_[i]
    // 字符串的引用。这也意味着我们不复制
    // 结果字符串，这个返回的内存地址实际上
    // 指向nicknames_向量的内存。
    std::string &GetNicknameAtI(size_t i) { return nicknames_[i]; }

    void PrintValid() {
        if (valid_) {
            std::cout << "Object is valid." << std::endl;
        } else {
            std::cout << "Object is invalid." << std::endl;
        }
    }

private:
    uint32_t age_;
    std::vector<std::string> nicknames_;
    // Keeping track of whether an object's data is valid, i.e. whether
    // all of its data has been moved to another instance.
    // 跟踪对象的数据是否有效，即是否
    // 所有数据都已移动到另一个实例。
    bool valid_;
};

int main() {
    // Let's see how move constructors and move assignment operators can be
    // implemented and used in a class. First, we create an instance of the class
    // Person. Note that the object andy is a valid object.
    // 让我们看看如何在类中实现和使用移动构造函数和移动赋值运算符。
    // 首先，我们创建类Person的一个实例。注意，对象andy是一个有效对象。
    Person andy(15445, {"andy", "pavlo"});
    std::cout << "Printing andy's validity: ";
    andy.PrintValid();

    // To move the contents of the andy object to another object, we can use
    // std::move in a couple ways. This method calls the move assignment operator.
    // 要将andy对象的内容移动到另一个对象，我们可以使用
    // std::move以几种方式。此方法调用移动赋值运算符。
    Person andy1;
    andy1 = std::move(andy);

    // Note that andy1 is valid, while andy is not a valid object.
    // 注意andy1是有效的，而andy不是有效对象。
    std::cout << "Printing andy1's validity: ";
    andy1.PrintValid();
    std::cout << "Printing andy's validity: ";
    andy.PrintValid();

    // This method calls the move constructor. After this operation, the contents
    // of the original andy object have moved to andy1, then moved to andy2. The
    // andy and andy1 lvalues are effectively defunct (and should not be used,
    // unless they are re-initialized).
    // 此方法调用移动构造函数。此操作后，原始andy对象的内容
    // 已移动到andy1，然后移动到andy2。andy和andy1左值
    // 实际上已经失效（不应使用，除非重新初始化）。
    Person andy2(std::move(andy1));

    // Note that andy2 is valid, while andy1 is not a valid object.
    // 注意andy2是有效的，而andy1不是有效对象。
    std::cout << "Printing andy2's validity: ";
    andy2.PrintValid();
    std::cout << "Printing andy1's validity: ";
    andy1.PrintValid();

    // However, note that because the copy assignment operator is deleted, this code
    // will not compile. The first line of this code constructs a new object via the
    // default constructor, and the second line invokes the copy assignment operator
    // to re-initialize andy3 with the deep-copied contents of andy2. Try uncommenting
    // these lines of code to see the resulting compiler errors.
    // Person andy3;
    // andy3 = andy2;
    // 然而，注意由于复制赋值运算符被删除，此代码
    // 将无法编译。此代码的第一行通过默认构造函数构造一个新对象，
    // 第二行调用复制赋值运算符重新初始化andy3，
    // 并深拷贝andy2的内容。尝试取消注释这些代码行，
    // 查看生成的编译器错误。
    // Person andy3;
    // andy3 = andy2;

    // Because the copy constructor is deleted, this code will not compile. Try
    // uncommenting this code to see the resulting compiler errors.
    // Person andy4(andy2);
    // 由于复制构造函数被删除，此代码将无法编译。尝试
    // 取消注释此代码，查看生成的编译器错误。
    // Person andy4(std::move(andy2));

    return 0;
}
