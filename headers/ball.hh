#ifndef BALL_HH
#define BALL_HH
#include <point3.hh>
#include <colors.hh>
#include <ray.hh>
#include <object.hh>

namespace Canyon {
	class Ball: public Object {
		public:
			Point3 c;
			double r;
			
			Ball() {}

			Point3 rayCrossPoint(Ray, void* = 0);
			std::vector<Ray> rayCrossOut(Ray);

			bool pointIn(Point3);
			void read(std::istream& fin);
			~Ball() {}
	};
};
#endif
