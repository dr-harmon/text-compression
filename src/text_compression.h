#pragma once

#include <queue>
#include <string>
#include <vector>

#include "bst.h"

// Performs Huffman encoding and decoding of a given string.
class TextCompression {
public:

    // Prepares a Huffman tree based on the given string.
    TextCompression(const std::string& data);

    // Returns the Huffman encoding of the string, where true means a 1 bit
    // and false means a 0 bit.
    std::vector<bool> encode() const;

    // Decodes the given Huffman-encoded bit sequence back to a string.
    std::string decode(const std::vector<bool>& data) const;    

private:

    // A binary search tree where the values are a character in the input string and
    // the keys are how many times that character appears in the string (frequency).
    typedef BinarySearchTree<int,char> HuffmanTree;

    // A priority queue where the elements are Huffman trees with the smallest tree
    // at the top.
    typedef std::priority_queue<HuffmanTree, std::vector<HuffmanTree>, std::greater<HuffmanTree>> HuffmanQueue;

    std::string data;
    HuffmanTree huffmanTree;

    // Constructs a tree of character frequencies in the given string, where each
    // key is a character in the string, and the corresponding value is how often
    // it occurs in the string.
    BinarySearchTree<char,int> computeFrequencies(const std::string& data) const;
 
    // Searches the Huffman tree for the given character and returns the
    // corresponding bit encoding.
    std::vector<bool> getHuffmanCode(char ch) const;

    // Returns the character in the Huffman tree for the given encoding, starting
    // at the given offset. The offset is incremented as each bit is encountered.
    char getHuffmanChar(std::vector<bool> data, int& offset) const;
};
