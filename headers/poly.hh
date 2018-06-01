#ifndef POLY_HH
#define POLY_HH
#include <double.hh>
#include <vector>
namespace Canyon {
    class Poly {
        public:
            int n;
            std::vector<double> a;
            inline double operator [](const int& idx) const {
                return idx >= 0 && idx <= n ? a[idx] : 0.;
            }
            inline double& operator [](const int& idx) {
                return a[idx];
            }
            Poly(int n_ = 0): n(n_), a(n_ + 1) {}
            Poly(const Poly& p_): n(p_.n), a(p_.a) {}
            void cut();
            double f(double) const;
            double df(double) const;
            Poly dy() const;
            std::vector<double> getZeroPoints(double = -INF, double = INF) const;
            Poly sqr() const;
            inline double operator()(const double& x) const {
                return this->f(x);
            }
    };
    Poly operator +(const Poly&, const Poly&);
    Poly operator -(const Poly&, const Poly&);
    Poly operator *(const Poly&, const Poly&);
    Poly operator *(const Poly&, const double&);
};
#endif
