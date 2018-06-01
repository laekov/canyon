#include <define.hh>

#include <triangle.hh>
#include <line.hh>
#include <plane.hh>

#ifdef DEBUG_OUT
#include <iostream>
#endif

namespace Canyon {
	bool Triangle::pointIn(Point3 p) {
		Vector a(this->a - p);
		Vector b(this->b - p);
		Vector c(this->c - p);
		Vector u(a % b);
		Vector v(b % c);
		Vector w(c % a);
		return sgn(u * v) > 0 && sgn(v * w) > 0;
	}
	
	Point3 Triangle::rayCrossPoint(Ray r, void*) {
		Line l(r.p, r.d);
		Plane p(*this);
		Point3 cross_point(lineCrossPlane(l, p));
		if (cross_point.isNaN()) {
			return ERROR_POINT;
		}
		if (sgn((cross_point - r.p) * r.d) <= 0) {
			return ERROR_POINT;
		}
		if (!this->pointIn(cross_point)) {
			return ERROR_POINT;
		}
		return cross_point;
	}

	std::vector<Ray> Triangle::rayCrossOut(Ray r) {
		std::vector<Ray> out_rays;
		Point3 cp(this->rayCrossPoint(r));
		Vector nf(Plane(*this).n.unify());
		this->getReflectAndRefracRay(r, out_rays, nf, cp);
		this->getDiffuseRay(r, out_rays, nf, cp);
		return out_rays;
	}

	void Triangle::read(std::istream& fin) {
		fin >> this->a >> this->b >> this->c >> this->col >> this->smooth;
	}

};
