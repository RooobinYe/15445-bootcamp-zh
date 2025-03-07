/**
 * @file wrapper_class.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code on wrapper classes.
 * @brief 包装类的教程代码。
 */

// A C++ wrapper class is a class that manages a resource. A resource
// could be memory, file sockets, or a network connection. Wrapper classes
// often use the RAII (Resource Acquisition is Initialization) C++
// programming technique. Using this technique implies that the resource's
// lifetime is tied to its scope. When an instance of the wrapper class is
// constructed, this means that the underlying resource it is managing is
// available, and when this instance is destructed, the resource also
// is unavailable.
// Here are a couple resources on RAII that are useful:
// https://en.cppreference.com/w/cpp/language/raii (RAII docs on the CPP
// docs website)
// Interesting Stack Overflow answers to "What is meant by RAII?":
// https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii
// C++包装类是一个管理资源的类。资源可以是内存、文件套接字或网络连接。
// 包装类通常使用RAII（资源获取即初始化）C++编程技术。
// 使用这种技术意味着资源的生命周期与其作用域相关联。
// 当包装类的实例被构造时，这意味着它管理的底层资源可用，
// 当这个实例被析构时，资源也变得不可用。
// 以下是一些关于RAII的有用资源：
// https://en.cppreference.com/w/cpp/language/raii（CPP文档网站上的RAII文档）
// Stack Overflow上对"RAII是什么意思？"的有趣回答：
// https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii

// In this file, we will look at a basic implementation of a wrapper class that
// manages an int*. We will also look at usage of this class.
// 在本文件中，我们将看一个管理int*的包装类的基本实现。
// 我们还将看看这个类的使用方法。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the utility header for std::move.
// 包含utility头文件以使用std::move。
#include <utility>

// The IntPtrManager class is a wrapper class that manages an int*. The
// resource that this class is managing is the dynamic memory accessible via
// the pointer ptr_. By the principles of the RAII technique, a wrapper class
// object should not be copyable, since one object is supposed to manage one
// resource. Therefore, the copy assignment operator and copy constructor are
// deleted from this class. However, the class is still moveable from different
// lvalues/owners, and has a move constructor and move assignment operator.
// Another reason that wrapper classes forbid copying is because they destroy
// their resource in the destructor, and if two objects are managing the same
// resource, there is a risk of double deletion of the resource.
// IntPtrManager类是一个管理int*的包装类。
// 这个类管理的资源是通过指针ptr_访问的动态内存。
// 根据RAII技术的原则，包装类对象不应该是可复制的，
// 因为一个对象应该管理一个资源。因此，
// 复制赋值运算符和复制构造函数从这个类中删除。
// 然而，该类仍然可以从不同的左值/所有者移动，
// 并具有移动构造函数和移动赋值运算符。
// 包装类禁止复制的另一个原因是它们在析构函数中销毁资源，
// 如果两个对象管理相同的资源，则存在资源的双重删除风险。
class IntPtrManager {
public:
    // All constructors of a wrapper class are supposed to initialize a resource.
    // In this case, this means allocating the memory that we are managing.
    // The default value of this pointer's data is 0.
    // 包装类的所有构造函数都应该初始化资源。
    // 在这种情况下，这意味着分配我们正在管理的内存。
    // 此指针数据的默认值为0。
    IntPtrManager() {
        ptr_ = new int;
        *ptr_ = 0;
    }

    // Another constructor for this wrapper class that takes a initial value.
    // 这个包装类的另一个构造函数，接受一个初始值。
    IntPtrManager(int val) {
        ptr_ = new int;
        *ptr_ = val;
    }

    // Destructor for the wrapper class. The destructor must destroy the
    // resource that it is managing; in this case, the destructor deletes
    // the pointer!
    // 包装类的析构函数。析构函数必须销毁它正在管理的资源；
    // 在这种情况下，析构函数删除指针！
    ~IntPtrManager() {
        // Note that since the move constructor marks objects invalid by setting
        // their ptr_ value to nullptr, we have to account for this in the
        // destructor. We don't want to be calling delete on a nullptr!
        // 注意，由于移动构造函数通过将对象的ptr_值设置为nullptr来标记对象无效，
        // 我们必须在析构函数中考虑这一点。我们不想对nullptr调用delete！
        if (ptr_) {
            delete ptr_;
        }
    }

    // Move constructor for this wrapper class. Note that after the move
    // constructor is called, effectively moving all of other's data into
    // the specified instance being constructed, the other object is no
    // longer a valid instance of the IntPtrManager class, since it has
    // no memory to manage.
    // 这个包装类的移动构造函数。注意，在调用移动构造函数后，
    // 有效地将其他对象的所有数据移入正在构造的指定实例，
    // 其他对象不再是IntPtrManager类的有效实例，
    // 因为它没有内存可管理。
    IntPtrManager(IntPtrManager &&other) {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    // Move assignment operator for this wrapper class. Similar techniques as
    // the move constructor.
    // 这个包装类的移动赋值运算符。与移动构造函数使用类似的技术。
    IntPtrManager &operator=(IntPtrManager &&other) {
        if (ptr_ == other.ptr_) {
            return *this;
        }
        if (ptr_) {
            delete ptr_;
        }
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    // We delete the copy constructor and the copy assignment operator,
    // so this class cannot be copy-constructed.
    // 我们删除了复制构造函数和复制赋值运算符，
    // 所以这个类不能被复制构造。
    IntPtrManager(const IntPtrManager &) = delete;
    IntPtrManager &operator=(const IntPtrManager &) = delete;

    // Setter function.
    // 设置器函数。
    void SetVal(int val) { *ptr_ = val; }

    // Getter function.
    // 获取器函数。
    int GetVal() const { return *ptr_; }

private:
    int *ptr_;
};

int main() {
    // We initialize an instance of IntPtrManager. After it is initialized, this
    // class is managing an int pointer.
    // 我们初始化一个IntPtrManager的实例。初始化后，
    // 这个类正在管理一个int指针。
    IntPtrManager a(445);

    // Getting the value works as expected.
    // 获取值按预期工作。
    std::cout << "1. Value of a is " << a.GetVal() << std::endl;

    // Setting the value goes through, and the value can retrieved as expected.
    // 设置值生效，可以按预期检索值。
    a.SetVal(645);
    std::cout << "2. Value of a is " << a.GetVal() << std::endl;

    // Now, we move the instance of this class from the a lvalue to the b lvalue
    // via the move constructor.
    // 现在，我们通过移动构造函数将这个类的实例从a左值移动到b左值。
    IntPtrManager b(std::move(a));

    // Retrieving the value of b works as expected because b is now managing the
    // data originally constructed by the constructor that created a. Note that
    // calling GetVal() on a will segfault, and a is supposed to effectively be
    // empty and unusable in this state.
    // 检索b的值按预期工作，因为b现在管理的是最初由创建a的构造函数构造的数据。
    // 注意，对a调用GetVal()将导致段错误，
    // 并且a在这种状态下应该是空的且不可用的。
    std::cout << "Value of b is " << b.GetVal() << std::endl;

    // Once this function ends, the destructor for both a and b will be called.
    // a's destructor will note that the ptr_ it is managing has been set to
    // nullptr, and will do nothing, while b's destructor should free the memory
    // it is managing.
    // 一旦这个函数结束，a和b的析构函数都将被调用。
    // a的析构函数会注意到它管理的ptr_已被设置为nullptr，
    // 而不会做任何事情，而b的析构函数应该释放它管理的内存。

    return 0;
}
