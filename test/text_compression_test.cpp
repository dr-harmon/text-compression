#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include "text_compression.h"

using namespace std;

TEST_CASE("Huffman encode/decode (Figure 12.8)")
{
    string data = "a fast runner need never be afraid of the dark";
	TextCompression tc(data);
    auto encoding = tc.encode();
    string encodingStr;
	for (bool bit : encoding) {
		encodingStr += bit ? "1" : "0";
	}
    // The encoded string depends on how duplicate frequencies
    // are ordered, so the test only verifies the length.
    REQUIRE(encodingStr.length() == 165);
	REQUIRE(tc.decode(encoding) == data);
}
