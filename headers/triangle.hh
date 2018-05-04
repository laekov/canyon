#ifndef TRIANGLE_HH
#define TRIANGLE_HH
#include <point3.hh>
#include <colors.hh>

namespace Canyon {
	class Triangle {
		public:
			Point3 a, b, c;
			Colors col;
			Triangle(Point3 a_, Point3 b_, Point3 c_, Colors col_): a(a_), b(b_), c(c_), col(col_) {}
	};

	bool pointInTriangle(Triangle, Point3 p);
};
#endif
