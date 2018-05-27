#ifndef OBJECT_HH
#define OBJECT_HH
#include <colors.hh>
#include <ray.hh>

#include <vector>

namespace Canyon {
	class Object {
		public:
			Colors col;
			double smooth;
			double alpha;
			double n;
			Object() {}
			Object(Colors col_, double smooth_ = 0., double alpha_ = 0.,
				   double n_ = 1.): col(col_) {}
			virtual Point3 rayCrossPoint(Ray) = 0;
			virtual std::vector<Ray> rayCrossOut(Ray) = 0;
			void getDiffuseRay(Ray, std::vector<Ray>&, Vector, Point3);
	};

};
#endif
