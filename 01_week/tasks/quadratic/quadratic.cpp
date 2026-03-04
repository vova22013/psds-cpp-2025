#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>

void SolveQuadratic(int a, int b, int c) {
    double x_1, x_2;
    bool a_is_zero = (a == 0);
    bool b_is_zero = (b == 0);
    bool c_is_zero = (c == 0);
    
    std::cout << std::setprecision(6);
    
    if (a_is_zero && b_is_zero && c_is_zero) {
        std::cout << "infinite solutions";
        return;
    } else if (a_is_zero && b_is_zero && !c_is_zero) {
        std::cout << "no solutions";   
        return;
    } else if (a_is_zero && !b_is_zero && c_is_zero) {
        std::cout << c;
        return;
    } else if (a_is_zero && !b_is_zero && !c_is_zero) {
        x_1 = static_cast<double>(-c) / b;
        std::cout << x_1;
        return;
    } else if (!a_is_zero && b_is_zero && c_is_zero) {
        std::cout << "0";
        return;
    } else if (!a_is_zero && b_is_zero && !c_is_zero) {
        if (a * c > 0) {
            std::cout << "no solutions";
            return;
        }
        x_2 = std::sqrt(static_cast<double>(-c) / a);
        x_1 = -x_2;
        std::cout << x_1 << " " << x_2;
        return;
    } else if (!a_is_zero && !b_is_zero && c_is_zero) {
        x_1 = 0.;
        x_2 = static_cast<double>(-b) / a;
        if (x_1 > x_2) std::swap(x_1, x_2);    
        std::cout << x_1 << " " << x_2;
        return;
    }

    double D_2 = static_cast<double>(b) * b - 4.0 * a * c;
    double eps = 1e-14;

    if (D_2 < 0) {
        std::cout << "no solutions";
        return;
    } 
    else if (D_2 < eps) {
        x_1 = static_cast<double>(-b) / (2. * a);
        std::cout << x_1;
        return;
    }
    else {
        double D = std::sqrt(D_2);
        x_1 = (-b + D) / (2. * a);
        x_2 = (-b - D) / (2. * a);
        if (x_1 > x_2) std::swap(x_1, x_2);
        std::cout << x_1 << " " << x_2;
        return;
    }
}
