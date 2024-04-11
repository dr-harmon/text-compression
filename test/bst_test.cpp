#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include "bst.h"

using namespace std;

TEST_CASE("Copy constructor")
{
    BinarySearchTree<int,char> bstOld;
    bstOld.put(2, 'b');
    bstOld.put(1, 'a');
    bstOld.put(4, 'd');
    bstOld.put(3, 'c');
    bstOld.put(5, 'e');
    BinarySearchTree<int,char> bstNew(bstOld);
    REQUIRE(bstNew.get(1) == 'a');
    REQUIRE(bstNew.get(2) == 'b');
    REQUIRE(bstNew.get(3) == 'c');
    REQUIRE(bstNew.get(4) == 'd');
    REQUIRE(bstNew.get(5) == 'e');
}

TEST_CASE("Assignment operator")
{
    BinarySearchTree<int,char> bstOld;
    bstOld.put(2, 'b');
    bstOld.put(1, 'a');
    bstOld.put(4, 'd');
    bstOld.put(3, 'c');
    bstOld.put(5, 'e');
    BinarySearchTree<int,char> bstNew;
    bstNew.put(6, 'f');
    bstNew.put(7, 'g');
    bstNew.put(8, 'h');
    bstNew = bstOld;
    REQUIRE(bstNew.get(1) == 'a');
    REQUIRE(bstNew.get(2) == 'b');
    REQUIRE(bstNew.get(3) == 'c');
    REQUIRE(bstNew.get(4) == 'd');
    REQUIRE(bstNew.get(5) == 'e');
    REQUIRE_FALSE(bstOld.exists(6));
    REQUIRE_FALSE(bstOld.exists(7));
    REQUIRE_FALSE(bstOld.exists(8));
}

TEST_CASE("Exists")
{
    BinarySearchTree<int,char> bst;
    REQUIRE_FALSE(bst.exists(1));
    bst.put(2, 'b');
    bst.put(1, 'a');
    bst.put(4, 'd');
    bst.put(3, 'c');
    bst.put(5, 'e');
    REQUIRE(bst.exists(1));
    REQUIRE(bst.exists(2));
    REQUIRE(bst.exists(3));
    REQUIRE(bst.exists(4));
    REQUIRE(bst.exists(5));
    REQUIRE_FALSE(bst.exists(0));
    REQUIRE_FALSE(bst.exists(6));
}

TEST_CASE("Get")
{
    BinarySearchTree<int,char> bst;
    bst.put(2, 'b');
    bst.put(1, 'a');
    bst.put(4, 'd');
    bst.put(3, 'c');
    bst.put(5, 'e');
    REQUIRE(bst.get(1) == 'a');
    REQUIRE(bst.get(2) == 'b');
    REQUIRE(bst.get(3) == 'c');
    REQUIRE(bst.get(4) == 'd');
    REQUIRE(bst.get(5) == 'e');
    REQUIRE_THROWS(bst.get(6));
}

TEST_CASE("Replace")
{
    BinarySearchTree<int,char> bst;
    bst.put(2, 'b');
    bst.put(1, 'a');
    bst.put(4, 'd');
    bst.put(3, 'c');
    bst.put(5, 'e');
    bst.put(1, 'A');
    bst.put(2, 'B');
    bst.put(3, 'C');
    bst.put(4, 'D');
    bst.put(5, 'E');
    REQUIRE(bst.get(1) == 'A');
    REQUIRE(bst.get(2) == 'B');
    REQUIRE(bst.get(3) == 'C');
    REQUIRE(bst.get(4) == 'D');
    REQUIRE(bst.get(5) == 'E');
}

TEST_CASE("Traverse")
{
    BinarySearchTree<int,char> bst;
    bst.put(2, 'b');
    bst.put(1, 'a');
    bst.put(4, 'd');
    bst.put(3, 'c');
    bst.put(5, 'e');
    vector<pair<int,char>> list;
    bst.traverseInorder([&list](int k, char v) { list.push_back(make_pair(k, v)); });
    REQUIRE(list == vector<pair<int,char>> {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}});
}

TEST_CASE("DOT (single node)")
{
    BinarySearchTree<int,char> bst;
    bst.put(2, 'b');
    REQUIRE(bst.toDOT() ==
        "digraph G {\n"
        "1[label=\"2: b\"]\n"
        "}\n"
    );
}

TEST_CASE("DOT (multiple nodes)")
{
    BinarySearchTree<int,char> bst;
    bst.put(2, 'b');
    bst.put(1, 'a');
    bst.put(4, 'd');
    bst.put(3, 'c');
    bst.put(5, 'e');
    REQUIRE(bst.toDOT() ==
        "digraph G {\n"
        "1[label=\"2: b\"]\n"
        "1 -> 2\n"
        "2[label=\"1: a\"]\n"
        "1 -> 3\n"
        "3[label=\"4: d\"]\n"
        "3 -> 4\n"
        "4[label=\"3: c\"]\n"
        "3 -> 5\n"
        "5[label=\"5: e\"]\n"
        "}\n"
    );
}

TEST_CASE("DOT (same labels)")
{
    BinarySearchTree<int,char> left;
    left.put(1, 'a');
    BinarySearchTree<int,char> right;
    right.put(1, 'a');
    BinarySearchTree<int,char> root(1, 'a', left, right);
}
