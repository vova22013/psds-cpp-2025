#include <stdexcept>


double ApplyOperations(const double a, const double b,
    double (*operations[])(const double, const double), size_t countOperations) 
{
    double res = 0.0;
    for (size_t i = 0; i < countOperations; ++i){
        if (operations[i] != nullptr) res += operations[i](a, b);
    }
    return res;
}