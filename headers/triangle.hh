#ifndef TRIANGLE_HH
#define TRIANGLE_HH
#include <point3.hh>
#include <object.hh>

namespace Canyon {
	class Triangle: public Object {
		public:
			Point3 a, b, c;
			Triangle() {}
			Triangle(Point3 a_, Point3 b_, Point3 c_, Colors col_): a(a_),
			    b(b_), c(c_), Object(col_) {}

			Point3 rayCrossPoint(Ray, void* = 0);
			std::vector<Ray> rayCrossOut(Ray);

			bool pointIn(Point3);
			virtual void read(std::istream&);
	};

};
#endif
