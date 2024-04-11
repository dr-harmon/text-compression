#pragma once

#include <string>
#include <vector>

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

    std::string data;
};
