#include <istream>

#include <cmath>

#include <double.hh>
#include <point3.hh>

namespace Canyon {
	double Point3::len() {
		return sqrt(sqr(this->x) + sqr(this->y) + sqr(this->z));
	}

	Point3 Point3::unify() {
		register double l(this->len());
		if (sgn(l)) {
			return Point3(this->x / l, this->y / l, this->z / l);
		} else {
			return Point3(0, 0, 0);
		}
	}

	Point3 operator +(const Point3& a, const Point3& b) {
		return Point3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Point3 operator -(const Point3& a, const Point3& b) {
		return Point3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	double operator *(const Point3& a, const Point3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Point3 operator *(const Point3& a, const double& b) {
		return Point3(a.x * b, a.y * b, a.z * b);
	}

	Point3 operator %(const Point3& a, const Point3& b) {
		return Point3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	std::istream& operator<<(std::istream& fin, Point3& p) {
		return fin >> p.x >> p.y >> p.z;
	}
};
