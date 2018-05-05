#ifndef TRIANGLE_HH
#define TRIANGLE_HH
#include <point3.hh>
#include <object.hh>
#include <ray.hh>

namespace Canyon {
	class Triangle: public Object {
		public:
			Point3 a, b, c;
			Triangle() {}
			Triangle(Point3 a_, Point3 b_, Point3 c_, Colors col_): a(a_), b(b_), c(c_), Object(col_) {}
			Point3 rayCrossPoint(Ray);
			std::vector<Ray> rayCrossOut(Ray);
			Vector reflectDirection(Vector);
			bool pointIn(Point3);
	};

};
#endif
