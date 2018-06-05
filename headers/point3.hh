#ifndef Point3_HH
#define Point3_HH
#include <double.hh>
#include <istream>
#include <ostream>
#include <math.h>

namespace Canyon {
	class Point3 {
		public:
			double x, y, z;
			Point3(double x_ = 0, double y_ = 0, double z_ = 0): x(x_), y(y_), z(z_) {}
			Point3(const Point3& p_): x(p_.x), y(p_.y), z(p_.z) {}
			double len() const;
			Point3 unify() const;
			inline bool isNaN() {
				return !(std::isfinite(x) && std::isfinite(y) && std::isfinite(z));
			}
	};

	Point3 operator +(const Point3& a, const Point3& b);
	Point3 operator -(const Point3& a, const Point3& b);
	double operator *(const Point3& a, const Point3& b);
	Point3 operator *(const Point3& a, const double& b);
	Point3 operator *(const double& b, const Point3& a);
	Point3 operator %(const Point3& a, const Point3& b);
	bool operator ==(const Point3& a, const Point3& b);
	double cosarc(const Point3& a, const Point3& b);
	std::istream& operator >>(std::istream&, Point3&);
	std::ostream& operator <<(std::ostream&, const Point3&);
	Point3 vertical(const Point3&);

	const Point3 ERROR_POINT(NAN, NAN, NAN);
};

#endif
