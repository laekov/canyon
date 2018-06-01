#include <poly.hh>
#include <iostream>
#include <algorithm>

namespace Canyon {
    void Poly::cut() {
        for (; n && !sgn(a[n]); -- n) {
            a.pop_back();
        }
    }

    double Poly::f(double t) const {
        double y(0);
        for (int i = n; i >= 0; -- i) {
            y = y * t + a[i];
        }
        return y;
    }

    double Poly::df(double t) const {
        double y(0);
        for (int i = n; i; -- i) {
            y = y * t + a[i] * i;
        }
        return y;
    }

    Poly Poly::dy() const {
        if (n == 0) {
            return Poly(0); 
        }
        Poly dp(n - 1);
        for (int i = n; i; -- i) {
            dp.a[i - 1] = a[i] * i;
        }
        dp.cut();
        return dp;
    }

    double newtonIter(const Poly& p, double x0) {
        static const int max_iteration = 29;
        double prv_x(0);
        int cnt(0);
        do {
            prv_x = x0;
            x0 -= p(x0) / p.df(x0);
        } while (++ cnt < max_iteration && (sgn(x0 - prv_x) || sgn(p(x0))));
        return x0;
    }

#define FIND_ZERO_POINT(l, r) { \
    if (sgn((r) - (l))) { \
        double s(newtonIter(*this, ((l) + (r))* .5)); \
        if (!sgn(this->f(s))) { \
            result.push_back(s); \
        } \
    } \
}
    std::vector<double> Poly::getZeroPoints(double rl, double rr) const {
        std::vector<double> result;
        if (n == 0) {
            if (a[0] == 0) {
                result.push_back(rl);
                result.push_back(rr);
            }
        } else {
            Poly dp(this->dy());
            std::vector<double> dpz(dp.getZeroPoints(rl, rr));
            size_t dn(dpz.size());
            if (dn == 0) {
                FIND_ZERO_POINT(rl, rr);
            } else {
                FIND_ZERO_POINT(rl, dpz[0]);
                dpz.push_back(rr);
                for (size_t i = 0; i < dn; ++ i) {
                    FIND_ZERO_POINT(dpz[i], dpz[i + 1]);
                }
            }
        }
        return result;
    }

    Poly operator +(const Poly& a, const Poly& b) {
        Poly c(std::max(a.n, b.n));
        for (int i = 0; i <= a.n; ++ i) {
            c[i] += a[i];
        }
        for (int i = 0; i <= a.n; ++ i) {
            c[i] += b[i];
        }
        c.cut();
        return c;
    }

    Poly operator -(const Poly& a, const Poly& b) {
        Poly c(std::max(a.n, b.n));
        for (int i = 0; i <= a.n; ++ i) {
            c[i] += a[i];
        }
        for (int i = 0; i <= a.n; ++ i) {
            c[i] -= b[i];
        }
        c.cut();
        return c;
    }

    Poly Poly::sqr() const {
        return *this * *this;
    }
    
    Poly operator *(const Poly& a, const double& b) {
        Poly r(a);
        for (int i = 0; i <= a.n; ++ i) {
			r[i] *= b;
		}
		r.cut();
		return r;
	}

    Poly operator *(const Poly& a, const Poly& b) {
        Poly r(a.n + b.n);
        for (int i = 0; i <= a.n; ++ i) {
            for (int j = 0; j <= b.n; ++ j) {
                r.a[i + j] += a[i] * b[j];
            }
        }
        r.cut();
        return r;
    }

};
