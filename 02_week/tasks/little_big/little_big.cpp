#include <stdexcept>
#include <iostream>
#include <cmath>

void PrintMemoryBodyTemplate(char* num_ptr_char, size_t size, bool flag_rvrs) {
    std::string byteset = "";
    for (size_t j = 0; j < size; ++j) {
        unsigned char temp = *(num_ptr_char + j);
        size_t count_hex_in_byte = 2;
        std::string byte = "";

        for (size_t i = 0; i < count_hex_in_byte; ++i) {
            auto power = static_cast<int>(std::pow(16, 1 - i));
            size_t remain = static_cast<int>(temp / power);
            if (power == temp || remain != 0) {
                temp -= remain * power;
            }

            char hex_conv;
            if (remain < 10) hex_conv = static_cast<char>(remain + '0');
            else hex_conv = static_cast<char>(remain - 10 + 'A');
            byte += hex_conv;
        }
        byteset += byte;
    }

    if (flag_rvrs) {
        for (size_t i = 0; i < byteset.size() / 2; ++i) {
            if (i % 2 == 0) {
                std::swap(byteset[i], byteset[byteset.size() - 1 - (i + 1)]);
            }
            else {
                std::swap(byteset[i], byteset[byteset.size() - 1 - (i - 1)]);
            }
        }
    }

    byteset.insert(0, "0x");
    std::cout << byteset << "\n";
}

void PrintMemory(int num, bool flag_rvrs = false) {
    char* num_ptr_char = reinterpret_cast<char*>(&num);

    size_t size_int = sizeof(int);
    PrintMemoryBodyTemplate(num_ptr_char, size_int, flag_rvrs);
}

void PrintMemory(double num, bool flag_rvrs = false) {
    char* num_ptr_char = reinterpret_cast<char*>(&num);

    size_t size_double = sizeof(double);
    PrintMemoryBodyTemplate(num_ptr_char, size_double, flag_rvrs);
}