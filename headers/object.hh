#ifndef OBJECT_HH
#define OBJECT_HH
#include <colors.hh>
#include <ray.hh>

#include <vector>
#include <istream>

namespace Canyon {
	class Object {
		public:
			Colors col;
			double smooth;
			double alpha;
			double ray_n;
			Point3 box_lo, box_hi;
			Object(): ray_n(0.), alpha(0.), smooth(0.), col(0.) {}
			Object(Colors col_, double smooth_ = 0., double alpha_ = 0.,
				   double n_ = 1.): col(col_) {}
			virtual Point3 rayCrossPoint(Ray, void* = 0) = 0;
			virtual std::vector<Ray> rayCrossOut(Ray) = 0;
			virtual bool pointIn(Point3) = 0;
			virtual void read(std::istream&) = 0;
			void getDiffuseRay(Ray, std::vector<Ray>&, Vector, Point3);
			void getReflectAndRefracRay(Ray, std::vector<Ray>&, Vector, Point3);
			bool inBox(Ray) const;
	};

};
#endif
