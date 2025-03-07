/**
 * @file condition_variable.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL condition variable.
 * @brief C++ STL条件变量的教程代码。
 */


// This program shows a small example of the usage of std::condition_variable.
// The std::condition_variable class provides the condition variable
// synchronization primitive. The condition variable primitive allows threads
// to wait until a particular condition before they grab a mutex. It also
// allows other threads to signal waiting threads to alert them that
// the condition may be true.
// 本程序展示了std::condition_variable使用的一个小例子。
// std::condition_variable类提供了条件变量同步原语。
// 条件变量原语允许线程在获取互斥锁之前等待特定条件。
// 它还允许其他线程向等待线程发出信号，提醒它们条件可能为真。

// For a more detailed introduction of C style condition variables, see
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf.
// 关于C风格条件变量的更详细介绍，请参见
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf。


// This program runs three threads. Two of these threads run a function that
// increments a global count variable by 1, atomically, and notifies the
// waiting thread when the count variable is 2. When the count variable is
// 2, the waiting thread wakes up, acquires the lock, and prints the count
// value.
// 本程序运行三个线程。其中两个线程运行一个函数，该函数原子性地将全局计数变量加1，
// 并在计数变量为2时通知等待线程。当计数变量为2时，等待线程唤醒，
// 获取锁，并打印计数值。

// Includes the condition variable library header.
// 包含条件变量库头文件。
#include <condition_variable>
// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the mutex library header.
// 包含互斥锁库头文件。
#include <mutex>
// Includes the thread library header.
// 包含线程库头文件。
#include <thread>

// Defining a global count variable, a mutex, and a condition variable to
// be used by both threads.
// 定义一个全局计数变量、一个互斥锁和一个条件变量，
// 供两个线程使用。
int count = 0;
std::mutex m;

// This is the syntax for declaring and default initializing a condition
// variable.
// 这是声明和默认初始化条件变量的语法。
std::condition_variable cv;


// In this function, a thread increments the count variable by
// 1. It also will notify one waiting thread if the count value is 2.
// It is ran by two of the threads in the main function.
// 在此函数中，线程将计数变量增加1。
// 如果计数值为2，它还将通知一个等待线程。
// 该函数由main函数中的两个线程运行。
void add_count_and_notify() {
    std::scoped_lock slk(m);  // 注释掉互斥锁，观察竞态条件
    count += 1;
    std::cout << "count+1!" << std::endl;
    if (count == 2) {
        cv.notify_one();
    }
}

// This function, ran by the waiting thread, waits on the condition
// count == 2. After that, it grabs the mutex m and executes code in
// the critical section.
// Condition variables need an std::unique_lock object to be constructed.
// std::unique_lock is a type of C++ STL synchronization primitive that
// gives more flexibility and features, including the usage with
// condition variables. Particularly, it is moveable but not copy-constructible
// or copy-assignable.
// 此函数由等待线程运行，等待条件count == 2。
// 之后，它获取互斥锁m并在临界区执行代码。
// 条件变量需要一个std::unique_lock对象来构造。
// std::unique_lock是一种C++ STL同步原语，
// 提供更多的灵活性和功能，包括与条件变量一起使用。
// 特别是，它是可移动的，但不是可复制构造或可复制赋值的。
void waiter_thread() {
    std::unique_lock lk(m);
    cv.wait(lk, [] { return count == 2; });

    std::cout << "Printing count: " << count << std::endl;
}

// The main method constructs three thread objects and has two of them run the
// add_count_and_notify function in parallel. After these threads are finished
// executing, we print the count value, from the waiter thread, showing that
// both increments, along with the conditional acquisition in the waiter
// thread, worked successfully.
// main方法构造了三个线程对象，并让其中两个并行运行add_count_and_notify函数。
// 在这些线程执行完成后，我们从等待线程打印计数值，
// 表明两次增量以及等待线程中的条件获取都成功工作了。
int main() {
    std::thread t1(add_count_and_notify);
    std::cout << "t1 created" << std::endl;
    std::thread t2(add_count_and_notify);
    std::cout << "t2 created" << std::endl;
    std::thread t3(waiter_thread);
    std::cout << "t3 created" << std::endl;
    t1.join();
    std::cout << "t1 joined" << std::endl;
    t2.join();
    std::cout << "t2 joined" << std::endl;
    t3.join();
    std::cout << "t3 joined" << std::endl;
    return 0;
}
