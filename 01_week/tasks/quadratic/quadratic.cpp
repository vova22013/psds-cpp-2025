#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>

void SolveQuadratic(int a, int b, int c) {
    double x_1, x_2;
    bool a_is_Zero = (a == 0 ? true : false);
    bool b_is_Zero = (b == 0 ? true : false);
    bool c_is_Zero = (c == 0 ? true : false);
    
    std::cout << std::setprecision(6);
    
    if (a_is_Zero) {
        if (b_is_Zero) {
            if (c_is_Zero) {
                std::cout << "infinite solutions";
            }
            else {
                std::cout << "no solutions";   
            } 
        }
        else {            
            if (c_is_Zero){
                std::cout << c;
            }
            else{
                x_1 = static_cast<double>(-c) / static_cast<double>(b);
                std::cout << x_1;
            }
        }
        
        return;
    }
    else { 
        if (b_is_Zero){ 
            if (c_is_Zero) {
                std::cout << c;
            }
            else {
                if (a * c < 0) {
                    x_1 = std::sqrt(static_cast<double>(-c) / static_cast<double>(a));
                    x_2 = -x_1;
                    
                    if (x_1 > x_2) std::swap(x_1, x_2);
                    
                    std::cout << x_1 << " " << x_2;
                }
                else std::cout << "no solutions";
            }
            return;
        }
        else if (c_is_Zero) {
            x_1 = static_cast<double>(0);
            x_2 = static_cast<double>(-b) / static_cast<double>(a);

            if (x_1 > x_2) std::swap(x_1, x_2);
                
            std::cout << x_1 << " " << x_2;
            
            return;
        }
    }
    
    double b_d = static_cast<double>(b);
    double a_d = static_cast<double>(a);
    double c_d = static_cast<double>(c);

    double D_2 = b_d * b_d - 4 * a_d * c_d;
    double eps = 1e-14;

    if (D_2 < 0) {
        std::cout << "no solutions";
        return;
    } 
    else if (D_2 < eps) {
        x_1 = -b_d / (2 * a_d);
        std::cout << x_1;
    }
    else {
        double D = static_cast<double>(std::sqrt(D_2));
        
        x_1 = (-b_d + D) / (2 * a_d);
        x_2 = (-b_d - D) / (2 * a_d);
        
        if (x_1 > x_2) std::swap(x_1, x_2);
        
        std::cout << x_1 << " " << x_2;
    }
}
