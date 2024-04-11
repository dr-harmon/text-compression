#include "text_compression.h"

using namespace std;

BinarySearchTree<char,int> TextCompression::computeFrequencies(const string& data) const
{
    BinarySearchTree<char,int> frequencies;

    for (char ch : data) {
        if (frequencies.exists(ch)) {
            frequencies.put(ch, frequencies.get(ch) + 1);
        } else {
            frequencies.put(ch, 1);
        }
    }

    return frequencies;
}

vector<bool> TextCompression::getHuffmanCode(char ch) const
{
    vector<bool> encoding;

    huffmanTree.traversePreorder(
        [ch](int key, char value) { return value == ch; },
        [&encoding]() { encoding.push_back(false); },
        [&encoding]() { encoding.pop_back(); },
        [&encoding]() { encoding.push_back(true); },
        [&encoding]() { encoding.pop_back(); }
    );

    return encoding;
}

char TextCompression::getHuffmanChar(const vector<bool> data, int& index) const
{
    return huffmanTree.search(
        [&data,&index](int freq, char ch) {
            return ch != 0;
        },
        [&data,&index](int freq, char ch) {
            return data[index++];
        }
    );
}

TextCompression::TextCompression(const string& data)
{
    this->data = data;

    auto frequencies = computeFrequencies(data);
    HuffmanQueue queue;
    frequencies.traverseInorder([&](char ch, int freq) {
        queue.emplace(freq, ch);
    });

    while (queue.size() > 1) {
        auto t1 = queue.top();
        queue.pop();
        auto t2 = queue.top();
        queue.pop();
        auto t = HuffmanTree(t1.getRoot().first + t2.getRoot().first, 0, t1, t2);
        queue.push(t);
    }

    huffmanTree = queue.top();
}

vector<bool> TextCompression::encode() const
{
    vector<bool> output;
    for (char ch : data) {
        vector<bool> encoding = getHuffmanCode(ch);
        for (bool bit : encoding) {
            output.push_back(bit);
        }
    }

    return output;
}

string TextCompression::decode(const vector<bool>& data) const
{
    string output;
    int offset = 0;
    while (offset < data.size()) {
        output += getHuffmanChar(data, offset);
    }
    return output;
}
