# 15-445/645 C++ Bootcamp
# 15-445/645 C++ 训练营
This bootcamp aims to provide a basic introduction to coding in modern C++. 
本训练营旨在提供现代C++编程的基础介绍。

The features of the C++ language are too vast and expansive to cover in one
bootcamp, and quite frankly, it is learned best through experience. The staff
is certain that 15-445 will make you a more confident C++ programmer! 
However, we do cover some C++ topics that are necessary to know while doing
the programming assignments. This tutorial does not cover basic C/C++ syntax.
It mainly covers C++ programming features, particularly concepts that do not exist in C.
C++语言的特性过于庞大和广泛，无法在一个训练营中全部涵盖，坦率地说，通过实践是学习它的最佳方式。工作人员确信15-445课程将使你成为一个更加自信的C++程序员！然而，我们确实涵盖了一些在完成编程作业时需要了解的C++主题。本教程不涉及基本的C/C++语法，主要涵盖C++编程特性，特别是C语言中不存在的概念。

Feedback for the C++ bootcamp is always appreciated! Feel free to submit issues/PRs.
我们非常感谢对C++训练营的反馈！欢迎提交问题或PR。

## Format
## 格式
The bootcamp consists of C++ code files, located in `src/`, that are meant
to be read in depth. Each of these files can be compiled into an executable
with the same name. Use CMake to build these executables. This set of commands
should build all the executables. After running these commands, these executables
should be located in the `build` directory.
训练营由位于`src/`目录下的C++代码文件组成，这些文件旨在被深入阅读。每个文件都可以编译成同名的可执行文件。使用CMake来构建这些可执行文件。以下命令集应该可以构建所有可执行文件。运行这些命令后，这些可执行文件应位于`build`目录中。

```console
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```
For instance, the `src/references.cpp` file compiles into the `references`
executable, located in `./build`. The same holds for every file in the source
directory.
例如，`src/references.cpp`文件会编译成位于`./build`中的`references`可执行文件。对源目录中的每个文件都是如此。

## Files
## 文件
There are fifteen files in the `src/` directory, each which cover different
concepts. They are meant to be read in the order below, since each file 
builds up on the previous one. However, if you know some modern C++ concepts
and are looking to refresh your knowledge, it is probably okay to start by
reading the files on concepts you are unfamiliar about.
`src/`目录中有十五个文件，每个文件涵盖不同的概念。它们应该按照以下顺序阅读，因为每个文件都是建立在前一个文件的基础上。然而，如果你已经了解一些现代C++概念并希望复习知识，那么从阅读你不熟悉的概念的文件开始可能也是可以的。

### References and Move Semantics
### 引用和移动语义
- `references.cpp`: Covers C++ references.
- `references.cpp`: 涵盖C++引用。
- `move_semantics.cpp`: Covers C++ move semantics.
- `move_semantics.cpp`: 涵盖C++移动语义。
- `move_constructors.cpp`: Covers C++ class move constructors and move assignment operators.
- `move_constructors.cpp`: 涵盖C++类的移动构造函数和移动赋值运算符。

### C++ Templates
### C++模板
- `templated_functions.cpp`: Covers C++ templated functions.
- `templated_functions.cpp`: 涵盖C++模板函数。
- `templated_classes.cpp` Covers C++ templated classes.
- `templated_classes.cpp` 涵盖C++模板类。

### Misc
### 杂项
- `wrapper_class.cpp`: Covers C++ wrapper classes.
- `wrapper_class.cpp`: 涵盖C++包装类。
- `iterator.cpp`: Covers implementing a basic C++ style iterator.
- `iterator.cpp`: 涵盖实现基本的C++风格迭代器。
- `namespaces.cpp`: Covers C++ namespaces.
- `namespaces.cpp`: 涵盖C++命名空间。

### C++ Standard Library (STL) Containers
### C++标准库(STL)容器
- `vectors.cpp`: Covers `std::vector`.
- `vectors.cpp`: 涵盖`std::vector`。
- `set.cpp`: Covers `std::set`.
- `set.cpp`: 涵盖`std::set`。
- `unordered_map.cpp`: Covers `std::unordered_map`.
- `unordered_map.cpp`: 涵盖`std::unordered_map`。
- `auto.cpp`: Covers the usage of the C++ keyword `auto`, including using `auto` to iterate through C++ STL containers.
- `auto.cpp`: 涵盖C++关键字`auto`的用法，包括使用`auto`遍历C++ STL容器。

### C++ Standard Library (STL) Memory
### C++标准库(STL)内存
- `unique_ptr.cpp`: Covers `std::unique_ptr`.
- `unique_ptr.cpp`: 涵盖`std::unique_ptr`。
- `shared_ptr.cpp`: Covers `std::shared_ptr`.
- `shared_ptr.cpp`: 涵盖`std::shared_ptr`。

### C++ Standard Library (STL) Synch Primitives
### C++标准库(STL)同步原语
- `mutex.cpp`: Covers `std::mutex`.
- `mutex.cpp`: 涵盖`std::mutex`。
- `scoped_lock.cpp`: Covers `std::scoped_lock`.
- `scoped_lock.cpp`: 涵盖`std::scoped_lock`。
- `condition_variable.cpp`: Covers `std::condition_variable`.
- `condition_variable.cpp`: 涵盖`std::condition_variable`。
- `rwlock.cpp`: Covers the usage of several C++ STL synchronization primitive libraries (`std::shared_mutex`, `std::shared_lock`, `std::unique_lock`) to create a reader-writer's lock implementation. 
- `rwlock.cpp`: 涵盖几个C++ STL同步原语库（`std::shared_mutex`, `std::shared_lock`, `std::unique_lock`）的使用，以创建读写锁实现。

### Demo Code for 15-445/645 Bootcamp
### 15-445/645训练营的演示代码
- `spring2024/s24_my_ptr.cpp`: Covers the code used in Spring 2024 bootcamp.
- `spring2024/s24_my_ptr.cpp`: 涵盖2024年春季训练营中使用的代码。

## Other Resources
## 其他资源
There are many other resources that will be helpful while you get accquainted to C++.
I list a few here!
当你熟悉C++时，还有许多其他有用的资源。我在这里列出几个！

- [https://en.cppreference.com/w/](https://en.cppreference.com/w/): Unofficial but quite accurate summary and examples of both C++ and C standards.
- [https://en.cppreference.com/w/](https://en.cppreference.com/w/): 非官方但相当准确的C++和C标准的总结和示例。
- [https://cplusplus.com/](https://cplusplus.com/): Contains both a C++ language [tutorial](https://cplusplus.com/doc/tutorial/) and a C++ library [reference](https://cplusplus.com/reference/).
- [https://cplusplus.com/](https://cplusplus.com/): 包含C++语言[教程](https://cplusplus.com/doc/tutorial/)和C++库[参考](https://cplusplus.com/reference/)。
- [Modern C++ Tutorial](https://github.com/changkun/modern-cpp-tutorial). This GitHub repo contains
some information and exercises that are useful!
- [现代C++教程](https://github.com/changkun/modern-cpp-tutorial)。这个GitHub仓库包含一些有用的信息和练习！

## Appendix: C++ Documentation for Topics Covered in the Bootcamp
## 附录：训练营涵盖主题的C++文档
This documentation may be useful to you! It's very comprehensive (much more comprehensive than this
bootcamp) but it may lack some readability. Overall, I think it's still a good idea to try to read
and understand this documentation, especially when working on the projects. Although the bootcamp
tries to be as comprehensive as possible, it still only covers the bare bones of using modern C++.
这些文档可能对你有用！它非常全面（比本训练营全面得多），但可能缺乏一些可读性。总的来说，我认为尝试阅读和理解这些文档仍然是个好主意，尤其是在处理项目时。虽然训练营尽可能地全面，但它仍然只涵盖了使用现代C++的基础知识。

- [References](https://en.cppreference.com/w/cpp/language/reference)
- [引用](https://en.cppreference.com/w/cpp/language/reference)
- [std::move](https://en.cppreference.com/w/cpp/utility/move)
- [std::move](https://en.cppreference.com/w/cpp/utility/move)
- [Move Constructors](https://en.cppreference.com/w/cpp/language/move_constructor) and [Move Assignment Operators](https://en.cppreference.com/w/cpp/language/move_assignment)
- [移动构造函数](https://en.cppreference.com/w/cpp/language/move_constructor)和[移动赋值运算符](https://en.cppreference.com/w/cpp/language/move_assignment)
- [Templated Functions](https://en.cppreference.com/w/cpp/language/function_template)
- [模板函数](https://en.cppreference.com/w/cpp/language/function_template)
- [Templated Classes](https://en.cppreference.com/w/cpp/language/class_template)
- [模板类](https://en.cppreference.com/w/cpp/language/class_template)
- [Iterators](https://en.cppreference.com/w/cpp/iterator)
- [迭代器](https://en.cppreference.com/w/cpp/iterator)
- [Namespaces](https://en.cppreference.com/w/cpp/language/namespace)
- [命名空间](https://en.cppreference.com/w/cpp/language/namespace)
- [std::vector](https://en.cppreference.com/w/cpp/container/vector)
- [std::vector](https://en.cppreference.com/w/cpp/container/vector)
- [std::set](https://en.cppreference.com/w/cpp/container/set)
- [std::set](https://en.cppreference.com/w/cpp/container/set)
- [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)
- [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)
- [auto](https://en.cppreference.com/w/cpp/language/auto)
- [auto](https://en.cppreference.com/w/cpp/language/auto)
- [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
- [std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
- [std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock)
- [std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock)
- [std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
- [std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
- [std::shared_mutex](https://en.cppreference.com/w/cpp/thread/shared_mutex)
- [std::shared_mutex](https://en.cppreference.com/w/cpp/thread/shared_mutex)
- [std::shared_lock](https://en.cppreference.com/w/cpp/thread/shared_lock)
- [std::shared_lock](https://en.cppreference.com/w/cpp/thread/shared_lock)
- [std::unique_lock](https://en.cppreference.com/w/cpp/thread/unique_lock)
- [std::unique_lock](https://en.cppreference.com/w/cpp/thread/unique_lock)
