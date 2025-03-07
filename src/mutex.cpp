/**
 * @file mutex.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL mutex.
 * @brief C++ STL互斥锁的教程代码。
 */

// This program shows a small example of the usage of std::mutex. The
// std::mutex class provides the mutex synchronization primitive.
// 本程序展示了std::mutex使用的一个小例子。
// std::mutex类提供了互斥锁同步原语。

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the mutex library header.
// 包含互斥锁库头文件。
#include <mutex>
// Includes the thread library header.
// 包含线程库头文件。
#include <thread>

// Defining a global count variable and a mutex to be used by both threads.
// 定义一个全局计数变量和一个互斥锁，供两个线程使用。
int count = 0;

// This is the syntax for declaring and default initializing a mutex.
// 这是声明和默认初始化互斥锁的语法。
std::mutex m;

// The add_count function allows for a thread to increment the count variable
// by 1, atomically.
// add_count函数允许线程以原子方式将计数变量
// 增加1。
void add_count() {
    // Acquire the lock before accessing count, the shared resource.
    // 在访问共享资源count之前获取锁。
    m.lock();
    count += 1;
    // Release the lock after accessing count, the shared resource.
    // 在访问共享资源count之后释放锁。
    m.unlock();
}

// The main method constructs two thread objects and has them both run the
// add_count function in parallel. After these threads are finished executing,
// we print the count value, showing that both increments worked successfully.
// The std::thread library is the C++ STL library used to construct threads.
// You may view it as a C++ equivalent of the pthread library in C.
// main方法构造了两个线程对象，并让它们并行运行
// add_count函数。在这些线程执行完成后，
// 我们打印计数值，显示两次增量都成功工作了。
// std::thread库是用于构造线程的C++ STL库。
// 你可以将其视为C语言中pthread库的C++等价物。
int main() {
    std::thread t1(add_count);
    std::thread t2(add_count);
    t1.join();
    t2.join();

    std::cout << "Printing count: " << count << std::endl;
    return 0;
}
