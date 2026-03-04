namespace {
    constexpr double m_in_inch = 0.0254;
    constexpr double m_in_foot = 0.3048;
    constexpr double m_in_cm = 0.01;
}


// m
constexpr long double operator""_m_to_m(long double m) {
    return m;
}
constexpr long double operator""_m_to_in(long double m) {
    return m / m_in_inch;
}
constexpr long double operator""_m_to_ft(long double m) {
    return m / m_in_foot;
}
constexpr long double operator""_m_to_cm(long double m) {
    return m / m_in_cm;
}


// cm
constexpr long double operator""_cm_to_cm(long double cm) {
    return cm;
}
constexpr long double operator""_cm_to_in(long double cm) {
    return cm / (m_in_inch / m_in_cm);
}
constexpr long double operator""_cm_to_ft(long double cm) {
    return cm / (m_in_foot / m_in_cm);
}
constexpr long double operator""_cm_to_m(long double cm) {
    return cm * m_in_cm;
}


// foot
constexpr long double operator""_ft_to_ft(long double ft) {
    return ft;
}
constexpr long double operator""_ft_to_in(long double ft) {
    return ft * (m_in_foot / m_in_inch);
}    
constexpr long double operator""_ft_to_m(long double ft) {
    return ft * m_in_foot;
}
constexpr long double operator""_ft_to_cm(long double ft) {
    return ft * (m_in_foot / m_in_cm);
}


// inch
constexpr long double operator""_in_to_in(long double in) {
    return in;
}
constexpr long double operator""_in_to_ft(long double in) {
    return in * (m_in_inch / m_in_foot);
}
constexpr long double operator""_in_to_m(long double in) {
    return in * m_in_inch;
}
constexpr long double operator""_in_to_cm(long double in) {
    return in * (m_in_inch / m_in_cm);
}