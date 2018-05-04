#ifndef LINE_HH
#define LINE_HH

#include "point3.hh"
#include "vector.hh"

namespace Canyon {
	class Line {
		public:
			Point3 p;
			Vector v;
			Line(Point3 p_, Vector v_): p(p_), v(v_) {}
	};
};
#endif
