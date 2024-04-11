# Text Compression

In this assignment, you are to complete exercise P-12.5 from the textbook:

>Implement a compression and decompression scheme that is based on Huffman coding.

[Huffman coding](https://en.wikipedia.org/wiki/Huffman_coding) is described in Section 12.4. It encodes a string as a bit vector that takes up less space than the original string. It can also decode the bit vector back to the original string.

Read Section 12.4 completely before starting the assignment. If any part of the algorithm is unclear, consult other books and websites for additional context and source code examples.

## Requirements

In the project, two classes have been provided for you:

* `BinarySearchTree`
* `TextCompression`

Parts of each class are marked `TODO`. Your task is to replace those parts with your own code so that `TextCompression` can perform Huffman encoding and decoding and all test cases pass.

In a real application, the Huffman tree would be transferred to the receiver for decoding. In this assignment, however, the tree will simply be retained in memory and re-used for the decoding.

There is no file I/O in this assignment. All operations will be performed in memory, and you may ignore memory errors (assume infinite RAM). You may also assume that the input string contains only ASCII characters (no Unicode).

## Binary Search Tree

A Huffman tree is a binary tree, not a binary search tree (BST). Its keys are character frequencies that may be duplicated, and those keys are not used for locating entries. However, the algorithms for constructing and traversing a BST can be applied to Huffman trees. Therefore, a `BinarySearchTree` class is provided for you in this assignment.

### BinarySearchTree Class

Certain methods of the class, such as `search`, have been tweaked from the usual BST definition to support Huffman coding. Others, such as the constructors, have been added specifically to help build Huffman trees. 

Since Huffman trees are typically small and do not need to be modified for decoding, the `BinarySearchTree` class does not provide operations to remove nodes nor keep the tree balanced.

You are not required to use all of the methods provided in the `BinarySearchTree` class. However, you _must_ implement the `put` function of the class (marked `TODO`). You may also add methods to the class as you see fit.

### Lambdas

The `BinarySearchTree` class makes extensive use of lambdas. Remember that when providing a lambda to a function, you may need to explicitly declare how to capture the variables used by the lambda. To capture a variable by value, simply add the variable name within the square brackets:

    [ch]() { ... }

To capture a variable by reference, do the same, but prefix it with an ampersand:

    [&encoding]() { ... }

Refer to any C++ resource for additional lambda documentation and usage examples.

## Priority Queue

For this assignment, use the `std::priority_queue` class from the STL as your priority queue implementation. Note that this class keeps the largest elements at the top, so you will need to find a way to reverse this ordering for the Huffman coding algorithm.

The `std::priority_queue` class requires a total ordering of the elements. One way to provide this ordering is by overloading the less-than or greater-than operator in the element's class. For example:

    bool operator<(const BinarySearchTree<K,V>& other) const { ... }

## Hints

* For debugging, you may find the `BinarySearchTree::toDOT` method helpful. This method produces a visual representation of the tree in [DOT format](https://en.wikipedia.org/wiki/DOT_(graph_description_language)). To use it, simply print the output of `toDOT`, then copy and paste that output to a [Graphviz](https://graphviz.org) viewer such as [Edotor](https://edotor.net).
* For the `char` type, you can use the null character (0 or `'\0'`) to indicate the absence of a value. Note that both the null character and the space character (`' '`) will appear to be missing in the `toDOT` output.
* The Huffman coding pseudocode in Example 12.9 says `for each character c in X do`. This means each _unique_ character, not each individual character. For example, in the string "abcabc" there are three characters, not six.
