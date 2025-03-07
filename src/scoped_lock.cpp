/**
 * @file scoped_lock.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL scoped lock.
 * @brief C++ STL作用域锁的教程代码。
 */

// This program provides a small example of the use of std::scoped_lock.
// std::scoped_lock is a mutex wrapper class that provides a RAII-style
// method of obtaining and releasing locks. This means that when the object
// is constructed, the locks are acquired, and when the object is destructed,
// the locks are released.
// 这个程序提供了使用std::scoped_lock的小例子。
// std::scoped_lock是一个互斥锁包装类，它提供了一种RAII风格的
// 获取和释放锁的方法。这意味着当对象被构造时，
// 锁被获取，当对象被析构时，锁被释放。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the mutex library header.
// 包含互斥锁库头文件。
#include <mutex>
// Includes the thread library header.
// 包含线程库头文件。
#include <thread>

// Defining a global count variable and two mutexes to be used by both threads.
// 定义一个全局计数变量和两个由两个线程使用的互斥锁。
int count = 0;
std::mutex m;

// The add_count function allows for a thread to increment the count variable
// by 1, atomically.
// add_count函数允许线程原子地将计数变量增加1。
void add_count() {
    // The constructor of std::scoped_lock allows for the thread to acquire the
    // mutex m.
    // std::scoped_lock的构造函数允许线程获取互斥锁m。
    std::scoped_lock slk(m);
    count += 1;

    // Once the function add_count finishes, the object slk is out of scope, and
    // in its destructor, the mutex m is released.
    // 一旦add_count函数完成，对象slk超出作用域，
    // 在其析构函数中，互斥锁m被释放。
}

// The main method is identical to the one in mutex.cpp. It constructs the
// thread objects, runs add_count on both threads, and prints the result of
// count after execution.
// 主方法与mutex.cpp中的相同。它构造线程对象，
// 在两个线程上运行add_count，并在执行后打印count的结果。
int main() {
    std::thread t1(add_count);
    std::thread t2(add_count);
    t1.join();
    t2.join();

    std::cout << "Printing count: " << count << std::endl;
    return 0;
}
