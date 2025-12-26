#include <iostream>
#include <cmath>
#include <numbers>
#include <iomanip>

constexpr double eps_ = 1e-12;
constexpr double pi_ = std::numbers::pi;

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
public:
    Phasor() = default;
    Phasor(double A, double phi);
    Phasor(double A, double phi, struct ExpTag);
    Phasor(double A, double phi_deg, struct DegTag);
    Phasor(double real, double imag, struct AlgTag);
    Phasor(const Phasor& p);
    Phasor(double real);

public:
    void SetPolar(double r, double phi);
    void SetCartesian(double x, double y);

    double Magnitude() const;
    double Phase() const;
    double PhaseDeg() const;
    
    double Abs() const;
    double Angle() const;
    double AngleDeg() const;

    double Real() const;
    double Imag() const;

    Phasor Conj() const;
    Phasor Inv() const;

    Phasor operator+(const Phasor& other) const;
    Phasor operator-(const Phasor& other) const;
    Phasor operator*(const Phasor& other) const;
    Phasor operator/(const Phasor& other) const;

    Phasor operator-() const;

    Phasor& operator+=(const Phasor& other);
    Phasor& operator-=(const Phasor& other);
    Phasor& operator*=(const Phasor& other);
    Phasor& operator/=(const Phasor& other);

    bool operator==(const Phasor& other) const;
    bool operator!=(const Phasor& other) const;

    Phasor& operator=(const Phasor& other);

    friend std::ostream& operator<<(std::ostream& os, const Phasor& p);

    friend Phasor const operator+(const double& real, const Phasor& p);
    friend Phasor const operator-(const double& real, const Phasor& p);
    friend Phasor const operator*(const double& real, const Phasor& p);
    friend Phasor const operator/(const double& real, const Phasor& p);

private:
    double m_A = 0.;
    double m_phi = 0.;
};

Phasor::Phasor(double A, double phi)
    : m_A(A), m_phi(phi) {
    if (m_A < eps_) {
        m_A = -m_A;
        if (m_phi <= eps_) m_phi += pi_;
        else m_phi -= pi_;
    }
    if (m_phi > pi_ || m_phi < -pi_) {
        while(m_phi > pi_) {
            m_phi -= 2 * pi_;
        }
        while (m_phi < -pi_) {
            m_phi += 2 * pi_;
        }
    }
    if (std::abs(m_phi + pi_) < eps_) m_phi *= -1; 
};

Phasor::Phasor(double A, double phi, struct ExpTag)
    : Phasor(A, phi) {};

Phasor::Phasor(double A, double phi_deg, struct DegTag)
    : Phasor(A, phi_deg * (pi_ / 180)) {};

Phasor::Phasor(double real, double imag, struct AlgTag) {
    m_A = std::sqrt(real * real + imag * imag);
    m_phi = std::atan(imag / real);
    if (real < 0 && imag < 0) m_phi -= pi_; 
    else if (real < 0 && imag > 0) m_phi += pi_; 
};

Phasor::Phasor(double real) : m_A(real) {
    if (m_A < eps_) m_A = -m_A;
};

Phasor::Phasor(const Phasor& p) {
    m_A = p.m_A;
    m_phi = p.m_phi;
}

Phasor Phasor::operator+(const Phasor& other) const {
    double real = this->Real() + other.Real();
    double imag = this->Imag() + other.Imag();
    return Phasor(real, imag, AlgTag());
}

Phasor Phasor::operator-(const Phasor& other) const {
    double real = this->Real() - other.Real();
    double imag = this->Imag() - other.Imag();
    return Phasor(real, imag, AlgTag());
}

Phasor Phasor::operator*(const Phasor& other) const {
    Phasor res = *this;
    res.m_A *= other.m_A;
    res.m_phi += other.m_phi;
    return res;
}

Phasor Phasor::operator/(const Phasor& other) const {
    Phasor res = *this;
    res.m_A /= other.m_A;
    res.m_phi -= other.m_phi;
    return res;
}

Phasor Phasor::operator-() const {
    if (m_phi > 0) return Phasor(m_A, m_phi - std::numbers::pi, ExpTag());
    else return Phasor(m_A, m_phi + std::numbers::pi, ExpTag());
}

Phasor& Phasor::operator+=(const Phasor& other) {
    double real = this->Real() + other.Real();
    double imag = this->Imag() + other.Imag();
    this->SetCartesian(real, imag);
    return *this;
}

Phasor& Phasor::operator-=(const Phasor& other) {
    double real = this->Real() - other.Real();
    double imag = this->Imag() - other.Imag();
    this->SetCartesian(real, imag);
    return *this;
}

Phasor& Phasor::operator*=(const Phasor& other) {
    m_A *= other.m_A;
    m_phi += other.m_phi;
    return *this;
}

Phasor& Phasor::operator/=(const Phasor& other) {
    m_A /= other.m_A;
    m_phi -= other.m_phi;
    return *this;
}

bool Phasor::operator==(const Phasor& other) const {
    if (std::abs(m_A - other.m_A) < eps_ &&
        std::abs(m_phi - other.m_phi) < eps_) return true;
    return false;
}

bool Phasor::operator!=(const Phasor& other) const {
    if (std::abs(m_A - other.m_A) > eps_ ||
        std::abs(m_phi - other.m_phi) > eps_) return true;
    return false;
}

Phasor& Phasor::operator=(const Phasor& other) {
    if (this == &other) return *this;
    
    m_A = other.m_A;
    m_phi = other.m_phi;
    return *this;
}

void Phasor::SetPolar(double r, double phi) {
    m_A = r;
    m_phi = phi;
}

void Phasor::SetCartesian(double x, double y) {
    m_A = std::sqrt(x * x + y * y);
    m_phi = std::atan(y / x);
}

double Phasor::Magnitude() const { 
    return m_A; 
}

double Phasor::Phase() const { 
    return m_phi;
}

double Phasor::PhaseDeg() const { 
    return m_phi * (180 / pi_); 
}

double Phasor::Abs() const { 
    return Magnitude(); 
}

double Phasor::Angle() const { 
    return Phase(); 
}

double Phasor::AngleDeg() const { 
    return PhaseDeg(); 
}

double Phasor::Real() const {
    return m_A * cos(m_phi);
}

double Phasor::Imag() const {
    return m_A * sin(m_phi);
}

Phasor Phasor::Conj() const {
    double real = this->Real();
    double imag = -this->Imag();
    return Phasor(real, imag, AlgTag());
}

Phasor Phasor::Inv() const {
     return Phasor(1 / m_A, -m_phi, ExpTag());
}

Phasor MakePhasorCartesian(double x, double y) {
    return Phasor(x, y, AlgTag());
}

Phasor MakePhasorPolar(double r, double phi) {
    return Phasor(r, phi, ExpTag());
}

Phasor MakePhasorPolarDeg(double r, double phi_deg) {
    return Phasor(r, phi_deg, DegTag());
}

Phasor const operator+(const double& real, const Phasor& p) {
    return Phasor(p.Real() + real, p.Imag(), AlgTag());
}

Phasor const operator-(const double& real, const Phasor& p) {
    return Phasor(real - p.Real(), -p.Imag(), AlgTag());
}

Phasor const operator*(const double& real, const Phasor& p) {
    return Phasor(p.m_A * real, p.m_phi, ExpTag());
}

Phasor const operator/(const double& real, const Phasor& p) {
    return Phasor(real / p.m_A, -p.m_phi, ExpTag());
}

std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    os << std::showpoint << std::setprecision(5) << p.Magnitude() << "*e(j*" << p.PhaseDeg() << ") [" 
        << p.Real() << " + j*" << p.Imag() << "]";
    return os; 
} 
