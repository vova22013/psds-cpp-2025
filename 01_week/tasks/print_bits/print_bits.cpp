#include <iostream>
#include <algorithm>

void PrintBits(long long value, size_t bytes) {
    std::string str_bset = "";
    
    auto bits = bytes * 8;

    for (size_t i = 0; i < bits; ++i) {
        auto b_i = (value >> i) & 1u;

        if (static_cast<bool>(b_i)) str_bset += "1";
        else str_bset += "0";

        if (i % 4 == 3 && i != bits - 1) {
            str_bset += '\'';
        }
    }

    str_bset += "b0";
    
    std::reverse(str_bset.begin(), str_bset.end());
    
    std::cout << str_bset << "\n";
}
