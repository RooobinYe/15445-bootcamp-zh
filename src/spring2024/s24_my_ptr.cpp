#include <iostream>
#include <memory>
#include <utility>

// This file contains the code used in the Spring2024 15-445/645 C++ bootcamp.
// It dives deeply into C++ new features like move constructor/assign operator, move semantics, unique_ptr,
// shared_ptr, wrapper class, etc., by implementing a simple version of unique_ptr from scratch.
// 本文件包含2024年春季15-445/645 C++训练营中使用的代码。
// 它通过从头实现一个简单版本的unique_ptr，深入探讨了C++的新特性，如移动构造函数/赋值运算符、移动语义、unique_ptr、
// shared_ptr、包装类等。

// **IMPORTANT NOTES**:
// **重要说明**:
//   1. please read `move_semantics.cpp` and `move_constructors.cpp` in `src` before reading this file!
//   1. 在阅读本文件之前，请先阅读`src`目录中的`move_semantics.cpp`和`move_constructors.cpp`！
//   2. please BEGIN your reading from the MAIN function!
//   2. 请从MAIN函数开始阅读！

// It is our implementation of std::unique_pointer<T>, and the real implementation is more complex!
// A template allows us to replace any type T, with what we want later in our code.
// 这是我们对std::unique_pointer<T>的实现，真实的实现要复杂得多！
// 模板允许我们在代码中用我们想要的任何类型替换T。
template<typename T>
class Pointer {
public:
    Pointer() {
        ptr_ = new T;
        *ptr_ = 0;
        std::cout << "New object on the heap: " << *ptr_ << std::endl;
    }
    Pointer(T val) {
        ptr_ = new T;
        *ptr_ = val;
        std::cout << "New object on the heap: " << val << std::endl;
    }
    // Destructor is called whenever an instance gets out of scope (just when the stack pops).
    // 当实例超出作用域（即当栈弹出时）就会调用析构函数。
    ~Pointer() {
        if (ptr_) {
            std::cout << "Freed: " << *ptr_ << std::endl;
            delete ptr_;
        }
    }

    // Copy constructor is explicitly deleted.
    // 显式删除复制构造函数。
    Pointer(const Pointer<T> &) = delete;
    // Copy assignment operator is explicitly deleted.
    // 显式删除复制赋值运算符。
    Pointer<T> &operator=(const Pointer<T> &) = delete;

    // Add move constructor: useful when we need to EXTEND the lifetime of an object!
    // 添加移动构造函数：当我们需要延长对象的生命周期时很有用！
    Pointer<T>(Pointer<T> &&another) : ptr_(another.ptr_) { another.ptr_ = nullptr; }
    // Add move assign operator: useful when we need to EXTEND the lifetime of an object!
    // 添加移动赋值运算符：当我们需要延长对象的生命周期时很有用！
    Pointer<T> &operator=(Pointer<T> &&another) {
        if (ptr_ == another.ptr_) { // In case `p = std::move(p);`
                                    // 防止情况：`p = std::move(p);`
            return *this;
        }
        if (ptr_) { // We must free the existing pointer before overwriting it! Otherwise we LEAK!!
                    // 在覆盖之前必须释放现有指针！否则会内存泄漏！！
            delete ptr_;
        }
        ptr_ = another.ptr_;
        another.ptr_ = nullptr; // NOTE: L14 avoids freeing nullptr during the destruction.
                                // 注意：L14避免在析构期间释放nullptr。
        return *this;
    }

    // Overload operator *, in order to make the Pointer<T> feel like a "pointer".
    // Note that the line below is an example of the following syntax we can use with our unique ptr type.
    // `p1.set_val(10)` -> `*p1 = 10`
    // 重载运算符*，使Pointer<T>感觉像一个"指针"。
    // 注意，下面的行是我们可以对自定义unique ptr类型使用的语法示例。
    // `p1.set_val(10)` -> `*p1 = 10`
    T &operator*() { return *ptr_; }

    T get_val() { return *ptr_; }
    void set_val(T val) { *ptr_ = val; }

private:
    T *ptr_;
};

// INCORRECT version of smart_generator
// smart_generator的错误版本
template<typename T>
Pointer<int> &dumb_generator(T init) {
    Pointer<T> p(init);
    return p; // NOOO! A DANGLING REFERENCE!
              // 不！这是一个悬挂引用！
}

template<typename T>
Pointer<T> smart_generator(T init) {
    Pointer<T> p(init);
    return std::move(p);
    // Actually `return p` will also work, since C++ is smart, it knows move construtor should be invoked in this place.
    // You can refer to `Automatic l-values returned by value may be moved instead of copied` in
    // https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/ for more information.
    // 实际上`return p`也可以工作，因为C++很聪明，它知道在这个位置应该调用移动构造函数。
    // 你可以参考https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/中的
    // `按值返回的自动左值可能会被移动而不是复制`获取更多信息。
}

void take_ownership(std::unique_ptr<int> p) {
    // Do something...
    // 做一些事情...
}

void not_take_ownership(int *p) {
    // Never `delete p` here!!
    // 永远不要在这里`delete p`!!
}

int main() {
    /* ======================================================================
       === Part 1: Common errors you come across in bustub ==================
       === 第1部分：在bustub中常遇到的错误 ===============================
       ====================================================================== */
    // When coding in C++/in this class, you will see a variable type called "unique_ptr"...
    // 当在C++/本课程中编程时，你会看到一种称为"unique_ptr"的变量类型...
    std::unique_ptr<int> ptr = std::make_unique<int>(3);
    // What does this mean? Why we don't use the raw pointer like `int *p = new int`? (The answer is in Part 2)
    // And later, when you need to pass this unique_ptr to a function, you may write the following code (please
    // try to uncomment next line)...
    // 这是什么意思？为什么我们不使用原始指针，如`int *p = new int`？（答案在第2部分）
    // 之后，当你需要将这个unique_ptr传递给函数时，你可能会写以下代码（请尝试取消下一行的注释）...
    // take_ownership(ptr);
    // It doesn't work. The error is `Call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'`.
    // You may search the Internet, and other people tell you to add a thing called `std::move`...
    // 这不起作用。错误是`对'std::unique_ptr<int>'的隐式删除的复制构造函数的调用`。
    // 你可能会搜索互联网，其他人会告诉你添加一个叫做`std::move`的东西...
    take_ownership(std::move(ptr));
    // It works! Looks great! And you continue coding...
    // Later, you may want to use p1 again (please try to uncomment next line)...
    // 它起作用了！看起来不错！然后你继续编码...
    // 之后，你可能想再次使用p1（请尝试取消下一行的注释）...
    // *ptr = 3;
    // Another error :(, and it says `segmentation fault`.
    // It looks confusing. What exactly happened?
    // We will explain it in this bootcamp, by implementing a simple version of unique_ptr from scratch!
    // 另一个错误:(，它说`段错误`。
    // 这看起来很混乱。到底发生了什么？
    // 我们将通过从头实现一个简单版本的unique_ptr来在本训练营中解释它！

    /* ======================================================================
       === Part 2: Why we need unique_ptr rather than the raw pointer =======
       === 第2部分：为什么我们需要unique_ptr而不是原始指针 ===============
       ====================================================================== */
    // What's the problem of merely using the raw pointer?
    // 仅使用原始指针有什么问题？
    int *p = new int; // Malloc
                      // 分配内存
    *p = 456 * 12 / 34 + 23;
    if (*p == 76) {
        delete p; // You may forget to add this line, and have `memory leak` problem!
                  // 你可能忘记添加这行，从而产生`内存泄漏`问题！
        return 0;
    }
    delete p; // Free
              // 释放内存

    // Raw pointers are dangerous! If you don't pay attention, you will come across problems like memory leaks, double
    // freeing, use after freeing...
    // The reason is that in C++, raw pointers have no inherent mechanism to clean up automatically!
    // Programmers have to allocate and deallocate heap memory all by themselves, and it is easy to go wrong.
    // 原始指针很危险！如果你不注意，你会遇到内存泄漏、重复释放、释放后使用等问题...
    // 原因是在C++中，原始指针没有固有的自动清理机制！
    // 程序员必须自己分配和释放堆内存，很容易出错。

    // We notice that, different from the memory in heap, the local variables in the stack will be created and deleted
    // automatically. Can we bind a raw pointer with a local variable in the stack?
    // It means, when this local variable is created, the heap memory for this raw pointer is automatically malloced.
    // And when this local variable dies, the raw pointer will be freed automatically. (For more details: search RAII)
    // 我们注意到，与堆中的内存不同，栈中的局部变量会自动创建和删除。
    // 我们能否将原始指针与栈中的局部变量绑定？
    // 这意味着，当创建这个局部变量时，这个原始指针的堆内存会自动分配。
    // 当这个局部变量消亡时，原始指针会自动释放。（更多详情：搜索RAII）

    // Let's use C++ class to implement it!
    // Consider a class whose only job is to hold and "own" a raw pointer, and then deallocate that pointer when the
    // class object went out of scope... This class is called `smart pointer`, and unique_ptr is one of smart pointers.
    // But, why we can't copy unique_ptr? What is std::move?
    // 让我们使用C++类来实现它！
    // 考虑一个类，其唯一的工作是持有和"拥有"一个原始指针，然后在类对象超出作用域时释放该指针...
    // 这个类被称为`智能指针`，unique_ptr是智能指针之一。
    // 但是，为什么我们不能复制unique_ptr？什么是std::move？

    /* ======================================================================
       === Part 3: Let's implement a unique_ptr class from scratch ==========
       === 第3部分：让我们从头实现一个unique_ptr类 =====================
       ====================================================================== */
    // We only show the last version of our own unique_ptr class.
    // Here is the brief roadmap during the implementation:
    //  1. First version: with default copy constructor & assign operator, without move constructor & assign operator
    //     Problem: `Pointer p2 = p1` will cause `double free` problem
    //     Copy constructor & assign operator are evil in this case, since it will allow both p1 and p2 to manage the
    //     same raw pointer! Solution: disable copy constructor & assign operator
    //  2. Second version: without copy constructor & assign operator, without move constructor & assign operator
    //     `Pointer p2 = p1` won't compile, which is good. We can use reference `Pointer &p2 = p1` instead. But...
    //     Problem: we cannot implement functions like dumb_generator() or smart_generator()!
    //     Solution: add things called move constructor & assign operator
    //  3. Final version: without copy constructor & assign operator, with move constructor & assign operator
    //     `Pointer p4 = std::move(p3);`
    //     `std::move` guarantees this line of code invokes the `move constructor`(rather than `copy constructor`), to
    //     transfer the ownership of the raw pointer from p3 to p4!
    //     After this line, p3 will not be valid anymore!
    //     The ptr_ in p3 will be nullptr, please don't use p3 anymore unless you reassign it.
    // Now you understand what is `std::move`, why copy functions are deleted... And how to use unique_ptr!
    // Reference: Chapter 22 in Learncpp Website
    // (https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/)
    // 我们只展示自己的unique_ptr类的最终版本。
    // 这是实现过程中的简要路线图：
    //  1. 第一版：有默认复制构造函数和赋值运算符，没有移动构造函数和赋值运算符
    //     问题：`Pointer p2 = p1`会导致`双重释放`问题
    //     在这种情况下，复制构造函数和赋值运算符是有害的，因为它们会让p1和p2同时管理同一个
    //     原始指针！解决方案：禁用复制构造函数和赋值运算符
    //  2. 第二版：没有复制构造函数和赋值运算符，没有移动构造函数和赋值运算符
    //     `Pointer p2 = p1`不会编译，这很好。我们可以使用引用`Pointer &p2 = p1`代替。但是...
    //     问题：我们无法实现像dumb_generator()或smart_generator()这样的函数！
    //     解决方案：添加移动构造函数和赋值运算符
    //  3. 最终版本：没有复制构造函数和赋值运算符，有移动构造函数和赋值运算符
    //     `Pointer p4 = std::move(p3);`
    //     `std::move`保证这行代码调用`移动构造函数`（而不是`复制构造函数`），
    //     将原始指针的所有权从p3转移到p4！
    //     在这行之后，p3将不再有效！
    //     p3中的ptr_将变为nullptr，除非重新赋值，否则请不要再使用p3。
    // 现在你理解了什么是`std::move`，为什么删除复制函数...以及如何使用unique_ptr！
    // 参考：Learncpp网站第22章
    // (https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/)
    Pointer<int> p1(4);
    std::cout << "Hi from p1 " << p1.get_val() << std::endl;
    p1.set_val(10);
    std::cout << "Hi again from p1 " << p1.get_val() << std::endl;

    {
        // Problem in next line: both have the ownership of this raw pointer! Double free here!
        // Pointer<int> p2 = p1; // Code for 1st version implementation.
        // Solution: never allow to copy ownership of the pointer! Never copy!
        // After deleting copy assign operator & constructor, maybe we can use pointer to rewrite `p2 = p1`.
        // 下一行的问题：两者都拥有这个原始指针的所有权！这里会双重释放！
        // Pointer<int> p2 = p1; // 第一版实现的代码。
        // 解决方案：永远不允许复制指针的所有权！永远不要复制！
        // 删除复制赋值运算符和构造函数后，也许我们可以使用指针重写`p2 = p1`。
        Pointer<int> *p2 = &p1; // Code for 2nd version implementation.
                                // 第二版实现的代码。
        std::cout << "Hi from p2 " << p2->get_val() << std::endl;
        // Wait this is dumb, we have a raw pointer again... Maybe we can use C++ reference, which is safer!
        // It's semantically the same thing with `Pointer<int> *p2 = &p1`, except the programmer doesn't **know** the
        // pointer (i.e. address of p2). 等等，这很蠢，我们又有了一个原始指针...也许我们可以使用C++引用，这更安全！
        // 语义上与`Pointer<int> *p2 = &p1`相同，只是程序员不**知道**指针（即p2的地址）。
        Pointer<int> &p22 = p1; // Code for 2nd version implementation.
                                // 第二版实现的代码。
        std::cout << "Hi from p22 " << p22.get_val() << std::endl;
    }
    // But reference doesn't solve everything :(
    // Sometimes we want to use the heap to extend the scope of the stack, like what dumb_generator() does!
    // Ex: pass down one element from a thread to another.
    // Please try to uncomment the following code!
    // 但引用并不能解决所有问题 :(
    // 有时我们想使用堆来扩展栈的作用域，就像dumb_generator()所做的那样！
    // 例如：将一个元素从一个线程传递到另一个线程。
    // 请尝试取消以下代码的注释！
    // Pointer<int>& dumb_pointer = dumb_generator(2); // Something will go horribly wrong, but what?
    // 会出现可怕的错误，但是是什么？
    // dumb_pointer.set_val(10); // Uh oh...
    // 哦不...

    // We need a way to "move the ownership". Please check move assign operator/constructor in Pointer class.
    // And we change dumb_generator() to smart_generator()...
    // Code for final version implementation:
    // 我们需要一种"转移所有权"的方法。请查看Pointer类中的移动赋值运算符/构造函数。
    // 我们将dumb_generator()改为smart_generator()...
    // 最终版本实现的代码：
    Pointer<int> p3 = smart_generator<int>(2);
    p3.set_val(10);
    Pointer<int> p4 = std::move(p3);

    // Let's make the user experience better.
    // 让我们改善用户体验。
    // 1. Templates.
    // 1. 模板。
    Pointer<float> p5(5.1);
    std::cout << "Hi from float p5 " << p5.get_val() << std::endl;
    // 2. Operator overload.
    // 2. 运算符重载。
    Pointer<char> c1('a');
    *c1 = 'b';
    std::cout << "Hi from char c1 " << *c1 << std::endl;

    // You may be confused about:
    //  `Pointer<T> &&` (in the move constructor and assign operator)
    //                         VS
    //  `Pointer<T> &` (in the copy constructor and assign operator)
    // 你可能对以下内容感到困惑：
    //  `Pointer<T> &&`（在移动构造函数和赋值运算符中）
    //                         对比
    //  `Pointer<T> &`（在复制构造函数和赋值运算符中）

    // You have 2 options now. First, consider it as a syntax to distinguish copy and move, and go straight to Part 4;
    // Second, here is a quick explanation:
    // 1. You need to know lvalue & rvalue. According to Abi, a simplified definition of lvalues is that lvalues are
    // objects that refer to a location in memory. Rvalues are anything that is not a lvalue.
    // 2. `Pointer<T> &&` is a rvalue reference, while `Pointer<T> &` is a lvalue reference.
    // 3. `std::move(p)` will cast p from a lvalue to something, for example, a rvalue.
    // 4. For `Pointer p2 = p1`, it will invoke copy constructor, since p1 is a lvalue.
    // 5. For `Pointer p2 = std::move(p1)`, it will invoke move constructor, since std::move(p1) is a rvalue.
    // 现在你有两个选择。首先，将其视为区分复制和移动的语法，然后直接转到第4部分；
    // 其次，这里有一个简短的解释：
    // 1. 你需要了解左值和右值。根据Abi的说法，左值的简化定义是左值是指向内存位置的对象。右值是任何不是左值的东西。
    // 2. `Pointer<T> &&`是右值引用，而`Pointer<T> &`是左值引用。
    // 3. `std::move(p)`会将p从左值转换为某物，例如，右值。
    // 4. 对于`Pointer p2 = p1`，它将调用复制构造函数，因为p1是左值。
    // 5. 对于`Pointer p2 = std::move(p1)`，它将调用移动构造函数，因为std::move(p1)是右值。

    /* ======================================================================
       === Part 4: Some important takeaways for unique_ptr & shared_ptr =====
       === 第4部分：unique_ptr和shared_ptr的一些重要要点 ===============
       ====================================================================== */
    // Several important takeaways for unique_ptr: (Reference: https://www.learncpp.com/cpp-tutorial/stdunique_ptr/)
    // 1. Always use std::make_unique() to create a unique_ptr.
    // unique_ptr的几个重要要点：（参考：https://www.learncpp.com/cpp-tutorial/stdunique_ptr/）
    // 1. 始终使用std::make_unique()创建unique_ptr。
    std::unique_ptr<int> up{std::make_unique<int>(1)};
    // Please avoid writing the following code!
    // int *rp = new int;
    // std::unique_ptr<int> up1{ rp };
    // std::unique_ptr<int> up2{ rp }; // WRONG!
    // 请避免编写以下代码！
    // int *rp = new int;
    // std::unique_ptr<int> up1{ rp };
    // std::unique_ptr<int> up2{ rp }; // 错误！

    // 2. Ways to pass std::unique_ptr to a function.
    // 2. 将std::unique_ptr传递给函数的方法。
    not_take_ownership(up.get());
    // Unique_ptr `up` is still valid here!
    // Unique_ptr `up`在这里仍然有效！
    take_ownership(std::move(up));
    // Unique_ptr `up`在这里不能使用！
    // Unique_ptr `up` cannot be used here!

    // Several important takeaways for shared_ptr: (Reference: https://www.learncpp.com/cpp-tutorial/stdshared_ptr/)
    // 0. Multiple shared ptrs can have the ownership of a raw pointer at the same time.
    //    Shared_ptr will count the number of shared ptrs that own the same raw pointer,
    //    and free the raw pointer **only if** count == 0.
    // shared_ptr的几个重要要点：（参考：https://www.learncpp.com/cpp-tutorial/stdshared_ptr/）
    // 0. 多个shared ptr可以同时拥有一个原始指针的所有权。
    //    Shared_ptr将计算拥有同一原始指针的shared ptr的数量，
    //    并且**仅当**计数== 0时才释放原始指针。
    std::shared_ptr<int> sp1{std::make_shared<int>(1)};
    {
        // You can use copy constructor & assign operator for shared_ptr.
        // 你可以对shared_ptr使用复制构造函数和赋值运算符。
        std::shared_ptr<int> sp2 = sp1;
        std::cout << "Count: " << sp1.use_count() << std::endl; // Output: 2
                                                                // 输出：2
    }
    std::cout << "Count: " << sp1.use_count() << std::endl; // Output: 1
                                                            // 输出：1
    // 1. Always make a copy of an existing std::shared_ptr.
    // 1. 始终复制现有的std::shared_ptr。
    int *rp = new int;
    std::shared_ptr<int> sp3{rp};
    // std::shared_ptr<int> sp4{ rp }; // WRONG!
    // 错误！
    std::shared_ptr<int> sp4{sp3};
    // 2. Always use std::make_shared() to create a shared_ptr.
    // 2. 始终使用std::make_shared()创建shared_ptr。

    return 0;
}
