#include <ball.hh>
#include <vector.hh>


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

	std::vector<Ray> Ball::rayCrossOut(Ray r) {
		std::vector<Ray> out_rays;
		Point3 p(this->rayCrossPoint(r));
		if (!p.isNaN()) {
			Vector n((p - this->c).unify());
			Vector reflect_direction(reflectDirection(r.d, n));
			out_rays.push_back(Ray(p, reflect_direction, r.c * this->col * 
						           Colors(this->smooth) *
								   Colors(1. - this->alpha)));
			Vector d_n_dir(n *(r.d * n));
			Vector d_on_dir(r.d - d_on_dir);
			if (this->pointIn(r.p)) {
				d_on_dir = d_on_dir * this->n;
			} else {
				d_on_dir = d_on_dir * (1. / this->n);
			}
			Vector refrac_direction(d_n_dir + d_on_dir);
			out_rays.push_back(Ray(p, reflect_direction, r.c * this->col * 
						           Colors(this->smooth) *
								   Colors(1. - this->alpha)));
			out_rays.push_back(Ray(p, refrac_direction, r.c * this->col * 
						           Colors(this->smooth) *
								   Colors(this->alpha)));
			this->getDiffuseRay(r, out_rays, n, p);
		}
		return out_rays;
	}

	bool Ball::pointIn(Point3 p) {
		return sgn((p - c).len() - r) < 0;
	}
};
