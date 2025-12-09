#include <stdexcept>


double ApplyOperations(double a, double b,
    double (**operations)(double, double), size_t countOperations) 
{
    double res = 0.0;
    for (size_t i = 0; i < countOperations; ++i){
        if (operations[i] != nullptr) res += operations[i](a, b);
    }
    return res;
}