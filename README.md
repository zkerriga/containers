# Сontainers
🔧⚙️ In this project, I studied the [documentation](http://www.cplusplus.com/) of containers from [STL](https://en.wikipedia.org/wiki/Standard_Template_Library) and tried to reproduce their work.

### I had a task before me:
I had to implement the following containers: [std::list](http://www.cplusplus.com/reference/list/list/), [std::vector](http://www.cplusplus.com/reference/vector/vector/), [std::map](http://www.cplusplus.com/reference/map/map/), [std::set](http://www.cplusplus.com/reference/set/set/) and the following adapters: [std::stack](http://www.cplusplus.com/reference/stack/stack/), [std::queue](http://www.cplusplus.com/reference/queue/queue/). I couldn't use STL and any algorithms and functions from C++11 and newer. I also had to create an automated testing system for my containers to demonstrate how they work!

___

#### `ft::list`
In the implementation of **a doubly-linked list**, I created a separate `ListNode` class. I tried to implement all operations in **a functional style** to ensure the safety and speed of working with the list. I also created two iterator classes that could be combined using [std::enable_if](https://en.cppreference.com/w/cpp/types/enable_if), which doesn't work in C++98 in the required context.

#### `ft::vector`
In this container we are working with **continuous memory**. A special feature of the container are [random-access iterators](https://www.cplusplus.com/reference/iterator/RandomAccessIterator/) that can quickly access any part of the array.

#### `ft::map` and `ft::set`
Both containers refer to a separate `TreeNode` class, which implements working with [red-black trees](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree). I relied on algorithms from a research paper from **Princeton University** that describes working effectively with **Left-leaning Red-Black Trees**. In this context, the binary tree must interact with iterators, so I added a link to the parent of each node to the implementation and provided for working with a special `endNode` that referred to the beginning, end, and top of the tree. The difference between `ft::map` and `ft::set` is only in the value stored in the `TreeNode`.

#### `ft::stack` and `ft::queue`
These adapters simply interact with internal containers to implement [LIFO](https://en.wikipedia.org/wiki/FIFO_and_LIFO_accounting) and [FIFO](https://en.wikipedia.org/wiki/FIFO_and_LIFO_accounting) principles.
