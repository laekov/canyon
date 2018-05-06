#ifndef OBJECT_HH
#define OBJECT_HH
#include <colors.hh>
#include <ray.hh>

#include <vector>

namespace Canyon {
	class Object {
		public:
			Colors col;
			Object() {}
			Object(Colors col_): col(col_) {}
			virtual Point3 rayCrossPoint(Ray);
			virtual std::vector<Ray> rayCrossOut(Ray);
	};

};
#endif
