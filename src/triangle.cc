#include <triangle.hh>
#include <line.hh>
#include <plane.hh>

namespace Canyon {
	bool pointInTriangle(Triangle t, Point3 p) {
		Vector a(t.a - p);
		Vector b(t.b - p);
		Vector c(t.c - p);
		Vector u(a % b);
		Vector v(b % c);
		Vector w(c % a);
		return sgn(u * v) == sgn(v * w);
	}
};
