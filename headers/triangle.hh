#ifndef TRIANGLE_HH
#define TRIANGLE_HH
#include <point3.hh>

class Triangle {
	public:
		Point3 a, b, c;
		Triangle(Point3 a_, Point3 b_, Point3 c_): a(a_), b(b_), c(c_) {}
};

bool pointInTriangle(Triangle, Point3 p);
#endif
