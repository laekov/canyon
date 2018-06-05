#ifndef CURVEROT_HH
#define CURVEROT_HH
#include <point3.hh>
#include <colors.hh>
#include <ray.hh>
#include <object.hh>
#include <poly.hh>

namespace Canyon {
	 class CurveRot: public Object {
		 public:
			 Point3 a;
			 Vector v;
			 Poly x, y;
			 int n;

			 CurveRot() {}

			 Point3 rayCrossPoint(Ray, void* = 0);
			 std::vector<Ray> rayCrossOut(Ray);

			 bool pointIn(Point3);
			 void read(std::istream& fin);

			 ~CurveRot() {}
	 };
};
#endif
