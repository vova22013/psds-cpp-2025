#include <cstdint>
#include <stdexcept>
#include <iostream>


enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {
    if (flags > CheckFlags::ALL) {
        std::cout << "";
        return;
    }

    bool the_first = true;
    std::string str_flags = "[";

    if (static_cast<uint8_t>(flags) &
        static_cast<uint8_t>(CheckFlags::TIME)) {
        str_flags += "TIME";
        the_first = false;
    }
    if (static_cast<uint8_t>(flags) &
        static_cast<uint8_t>(CheckFlags::DATE)) {
        the_first ? str_flags += "DATE" : str_flags += ",DATE";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::USER) ) {
        the_first ? str_flags += "USER" : str_flags += ",USER";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::CERT)) {
        the_first ? str_flags += "CERT" : str_flags += ",CERT";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::KEYS)) {
        the_first ? str_flags += "KEYS" : str_flags += ",KEYS";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::DEST)) {
        the_first ? str_flags += "DEST" : str_flags += ",DEST";
        the_first = false;
    }

    str_flags += "]";
    std::cout << str_flags;
}
