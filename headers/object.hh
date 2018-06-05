#ifndef OBJECT_HH
#define OBJECT_HH
#include <colors.hh>
#include <ray.hh>

#include <vector>
#include <istream>

namespace Canyon {
	class Object {
		public:
			double ray_n;
			double alpha;
			double smooth;
			Colors col;
			Point3 box_lo, box_hi;
			Object(): ray_n(0.), alpha(0.), smooth(0.), col(0.) {}
			virtual Point3 rayCrossPoint(Ray, void* = 0) = 0;
			virtual std::vector<Ray> rayCrossOut(Ray) = 0;
			virtual bool pointIn(Point3) = 0;
			virtual void read(std::istream&) = 0;
			void getDiffuseRay(Ray, std::vector<Ray>&, Vector, Point3);
			void getReflectAndRefracRay(Ray, std::vector<Ray>&, Vector, Point3);
			bool inBox(Ray) const;
			virtual ~Object() {}
	};

};
#endif
