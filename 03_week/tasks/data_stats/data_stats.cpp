#include <stdexcept>
#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

 DataStats CalculateDataStats(const std::vector<int>& vec) {
    DataStats data;
    
    size_t v_size = vec.size();

    if (v_size == 0) return data;
    long long sum_sq = 0;
    long long mid_memb = 0;
    double avg = 0.;
    
    for (size_t i = 0; i < v_size; ++i) {
        sum_sq += static_cast<long long>(vec[i]) * vec[i];
        avg += static_cast<double>(vec[i]);
        mid_memb += 2 * static_cast<long long>(vec[i]);
    }
    
    avg /= v_size;
    double num = sum_sq - mid_memb * avg + avg * avg * v_size;
    data.sd = std::sqrt(num / v_size);
    data.avg = avg;
    
    return data;
 }
