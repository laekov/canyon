#include <ball.hh>
#include <vector.hh>

#include <assert.h>
#include <iostream>

namespace Canyon {
	Point3 Ball::rayCrossPoint(Ray l, void*) {
		if (!this->inBox(l)) {
			return ERROR_POINT;
		}
		Vector v(this->c - l.p);
		Vector uld(l.d.unify());
		double proj_len(v * uld);
		Point3 a(l.p + uld * proj_len);
		if (!this->pointIn(a)) {
			return ERROR_POINT;
		}
		double deltad(sqrt(sqr(this->r) - sqr((a - this->c).len())));
		Point3 p1(l.p + uld * (proj_len - deltad));
		Point3 p2(l.p + uld * (proj_len + deltad));
		double d1((p1 - l.p) * l.d);
		if (sgn(d1) < 0) {
			d1 = 1e100;
		}
		double d2((p2 - l.p) * l.d);
		if (sgn(d2) < 0) {
			d2 = 1e100;
		}
		return d1 < d2 ? p1 : p2;
	}

	std::vector<Ray> Ball::rayCrossOut(Ray ray) {
		std::vector<Ray> out_rays;
		Point3 p(this->rayCrossPoint(ray));
		if (!p.isNaN()) {
			Vector n((p - this->c).unify());
			this->getReflectAndRefracRay(ray, out_rays, n, p);
			this->getDiffuseRay(ray, out_rays, n, p);
		}
		return out_rays;
	}

	bool Ball::pointIn(Point3 p) {
		return sgn((p - c).len() - r) < 0;
	}

	void Ball::read(std::istream& fin) {
		fin >> this->c >> this->r >> this->col >> this->smooth >> this->alpha
			>> this->ray_n;
		this->box_lo = this->c - Point3(this->r, this->r, this->r);
		this->box_hi = this->c + Point3(this->r, this->r, this->r);
	}
};
