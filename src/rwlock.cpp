/**
 * @file rwlock.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL std::shared_lock and std::unique_lock
 * (particularly usage of them as RWLocks).
 * @brief C++ STL std::shared_lock和std::unique_lock的教程代码
 * （特别是它们作为读写锁的用法）。
 */

// Although C++ does not have a specific reader-writer's lock library, it is
// possible to emulate one by using the std::shared_mutex, std::shared_lock,
// and std::unique_lock libraries. This program shows a small example on how
// to do this.
// 虽然C++没有特定的读写锁库，但可以通过使用std::shared_mutex、std::shared_lock
// 和std::unique_lock库来模拟一个。这个程序展示了如何做到这一点的小例子。

// The std::shared_mutex is a mutex that allows for both shared, read-only
// locking, and exclusive, write-only locking. std::shared_lock can be used
// as an RAII-style read lock, and std::unique_lock can be used as a RAII-style
// write lock. scoped_lock.cpp talks about RAII-style locking in C++.
// std::shared_mutex是一种互斥锁，允许共享的只读锁定和独占的只写锁定。
// std::shared_lock可用作RAII风格的读锁，std::unique_lock可用作RAII风格的
// 写锁。scoped_lock.cpp讨论了C++中的RAII风格锁定。

// If you would prefer to review the conceptuals of readers-writers locks and
// the reader-writers problem, you can refer to the 15-213/513/613 slides here:
// https://www.cs.cmu.edu/afs/cs/academic/class/15213-s23/www/lectures/25-sync-advanced.pdf
// 如果你想复习读写锁的概念和读写问题，可以参考15-213/513/613的幻灯片：
// https://www.cs.cmu.edu/afs/cs/academic/class/15213-s23/www/lectures/25-sync-advanced.pdf

// Includes std::cout (printing) for demo purposes.
// 包含std::cout（打印）用于演示目的。
#include <iostream>
// Includes the mutex library header.
// 包含互斥锁库头文件。
#include <mutex>
// Includes the shared mutex library header.
// 包含共享互斥锁库头文件。
#include <shared_mutex>
// Includes the thread library header.
// 包含线程库头文件。
#include <thread>

// Defining a global count variable and a shared mutex to be used by all threads.
// The std::shared_mutex is a mutex that allows for shared locking, as well as
// exclusive locking.
// 定义一个全局计数变量和一个由所有线程使用的共享互斥锁。
// std::shared_mutex是一种互斥锁，允许共享锁定和独占锁定。
int count = 0;
std::shared_mutex m;

// This function uses a std::shared_lock (reader lock equivalent) to gain
// read only, shared access to the count variable, and reads the count
// variable.
// 此函数使用std::shared_lock（相当于读取锁）获取对count变量的只读共享访问，
// 并读取count变量。
void read_value() {
    std::shared_lock lk(m);
    std::cout << "Reading value " + std::to_string(count) + "\n" << std::flush;
}

// This function uses a std::unique_lock (write lock equivalent) to gain
// exclusive access to the count variable and write to the value.
// 此函数使用std::unique_lock（相当于写锁）获取对count变量的独占访问并写入值。
void write_value() {
    std::unique_lock lk(m);
    count += 3;
}

// The main method constructs six thread objects and has two of them run the
// write_value function, and four of them run the read_value function, all
// in parallel. This means that the output is not deterministic, depending
// on which threads grab the lock first. Run the program a few times, and
// see if you can get different outputs.
// 主方法构造了六个线程对象，让其中两个运行write_value函数，四个运行read_value函数，
// 全部并行运行。这意味着输出不是确定性的，取决于哪些线程首先获取锁。
// 多运行几次程序，看看你是否能得到不同的输出。
int main() {
    std::thread t1(read_value);
    std::thread t2(write_value);
    std::thread t3(read_value);
    std::thread t4(read_value);
    std::thread t5(write_value);
    std::thread t6(read_value);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    return 0;
}
