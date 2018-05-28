#include <ball.hh>
#include <vector.hh>

#include <assert.h>
#include <iostream>

namespace Canyon {
	Point3 Ball::rayCrossPoint(Ray l) {
		Vector v(this->c - l.p);
		double proj_len(v * l.d.unify());
		Point3 a(l.p + l.d * proj_len);
		if (!this->pointIn(a)) {
			return ERROR_POINT;
		}
		double deltad(sqrt(sqr(this->r) + sqr((a - this->c).len())));
		Point3 p1(l.p + l.d.unify() * (proj_len - deltad));
		Point3 p2(l.p - l.d.unify() * (proj_len + deltad));
		double d1(p1 * l.d);
		if (sgn(d1) < 0) {
			d1 = 1e100;
		}
		double d2(p2 * l.d);
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
			if (sgn(n * ray.d) > 0) {
				n = n * -1.;
			}
			bool all_reflect(0);
			if (this->alpha > 0.) {
				double stheta(sin(acos(n * ray.d.unify())));
				if (this->pointIn(ray.p)) {
					stheta *= this->n;
				} else {
					stheta /= this->n;
				}
				if (stheta < 1.) {
					double theta(asin(stheta));
					Vector dn(n *(n * ray.d));
					Vector dvert(ray.d - dn);
					Vector refrac_direction(dn.unify() +
							                dvert.unify() * tan(theta));
					Ray refrac(p, refrac_direction, 
							   ray.c * this->col * 
							   Colors(this->smooth) *
							   Colors(this->alpha));
					out_rays.push_back(refrac);
				} else {
					all_reflect = 1;
				}
			}
			if (this->alpha < 1. || all_reflect) {
				Vector reflect_direction(reflectDirection(ray.d, n));
				if (sgn(n * reflect_direction) < 0) {
					reflect_direction = reflect_direction * -1.;
				}
				Ray refl(p, reflect_direction, ray.c * 
				    	 this->col * Colors(this->smooth) *
						 Colors(all_reflect ? 1. :
							    1. - this->alpha));
				out_rays.push_back(refl);
			}
			this->getDiffuseRay(ray, out_rays, n, p);
		}
		return out_rays;
	}

	bool Ball::pointIn(Point3 p) {
		return sgn((p - c).len() - r) < 0;
	}
};
