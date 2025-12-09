#include <stdexcept>
#include <iostream>
#include <cmath>

void PrintMemory(int num, bool flag_rvrs = false) {
    void* address_num = &num;
    char* num_ptr_char = static_cast<char*>(address_num);

    std::string byteset = "";
    int size_int = sizeof(int);
    for (int j = 0; j < size_int; ++j) {
        unsigned char temp = *(num_ptr_char + j);
        size_t count_hex_in_byte = 2;
        std::string byte = "";

        for (size_t i = 0; i < count_hex_in_byte; ++i) {
            auto power = static_cast<int>(pow(16, 1 - i));
            size_t remain = static_cast<int>(temp / power);
            if (power == temp || remain != 0) {
                temp -= remain * power;
            }

            char hex_conv;
            if (remain < 10) hex_conv = static_cast<char>(remain + '0');
            else hex_conv = static_cast<char>(remain - 10 + 'A');

            byte.append(1, hex_conv);
        }
        byteset.append(byte);
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

    byteset.insert(0, static_cast<std::string>("0x"));
    std::cout << byteset << "\n";
}

void PrintMemory(double num, bool flag_rvrs = false) {
    void* address_num = &num;
    char* num_ptr_char = static_cast<char*>(address_num);

    std::string byteset = "";
    int size_double = sizeof(double);
    for (int j = 0; j < size_double; ++j) {
        unsigned char temp = *(num_ptr_char + j);
        size_t count_hex_in_byte = 2;
        std::string byte = "";

        for (size_t i = 0; i < count_hex_in_byte; ++i) {
            auto power = static_cast<int>(pow(16, 1 - i));
            size_t remain = static_cast<int>(temp / power);
            if (power == temp || remain != 0) {
                temp -= remain * power;
            }

            char hex_conv;
            if (remain < 10) hex_conv = static_cast<char>(remain + '0');
            else hex_conv = static_cast<char>(remain - 10 + 'A');

            byte.append(1, hex_conv);
        }
        byteset.append(byte);
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

    byteset.insert(0, static_cast<std::string>("0x"));
    std::cout << byteset << "\n";
}