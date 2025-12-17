#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>
#include <string>

struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const Coord2D& coords) {
    os << "(" + std::to_string(coords.x) + ", " + std::to_string(coords.y) + ")";
    return os;    
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    if (circle.radius == 0) os << "circle[]";
    else {
        os << "circle[" << circle.coord << ", " 
            << "r = " << std::to_string(circle.radius) << "]";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& creg) {
    if (creg.second) os << "+";
    else os << "-";
    os << creg.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.size() == 0) os << "{}";
    else {
        os << "{";
        for(size_t i = 0; i < list.size(); ++i) {
            os << "\n\t" << list[i];
            if (i != list.size() - 1) os << ",";
        }
        os << "\n}";
    }
    return os;
}

