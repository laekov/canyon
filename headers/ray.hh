#ifndef RAY_HH
#define RAY_HH
#include <vector>

#include "point3.hh"
#include "vector.hh"
#include "colors.hh"

namespace Canyon {
	class Ray {
		public:
			Point3 p;
			Vector d;
			Colors c;
			bool diffused;
			Ray(Point3 p_, Vector d_, Colors c_ = Colors(0, 0, 0),
			    bool diff_ = 0): p(p_), d(d_), c(c_), diffused(diff_) { }
			Ray(const Ray& r_): p(r_.p), d(r_.d), c(r_.c),
		                        diffused(r_.diffused) { }
			inline void darker(Colors delta_c) {
				c = c * delta_c;
			}
	};
	Vector reflectDirection(Vector v, Vector n);
};
#endif
