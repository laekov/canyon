#ifndef PLANE_HH
#define PLANE_HH

#include "point3.hh"
#include "vector.hh"
#include "triangle.hh"

class Plane {
	public:
		Point3 p;
		Vector n;
		Plane(Triangle t_) {
			this->p = t_.a;
			this->n = (t_.c - t_.a) % (t_.b - t_.a);
		}
		Plane(Point3 a, Point3 b, Point3 c) {
			this->p = a;
			this->n = (c - a) % (b - a);
		}
};

double lineCrossPlaneRatio(struct Line, Plane);
Point3 lineCrossPlane(struct Line, Plane);
#endif
