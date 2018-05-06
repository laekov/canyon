#include <define.hh>

#include <triangle.hh>
#include <line.hh>
#include <plane.hh>

#ifdef DEBUG_OUT
#include <iostream>
#endif

namespace Canyon {
	const double alpha_count = 0.3;
	const double theta_count = 0.4;

	bool Triangle::pointIn(Point3 p) {
		Vector a(this->a - p);
		Vector b(this->b - p);
		Vector c(this->c - p);
		Vector u(a % b);
		Vector v(b % c);
		Vector w(c % a);
		return sgn(u * v) > 0 && sgn(v * w) > 0;
	}
	
	Point3 Triangle::rayCrossPoint(Ray r) {
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

	double colorStrength(Colors x) {
		return Point3(x.r, x.g, x.b).len();
	}

	std::vector<Ray> Triangle::rayCrossOut(Ray r) {
		std::vector<Ray> out_rays;
		Point3 cp(this->rayCrossPoint(r));
		Vector refd(this->reflectDirection(r.d));
		Vector nf(Plane(*this).n.unify());
		if (sgn(nf * refd) < 0) {
			nf = nf * -1;
		}
		out_rays.push_back(Ray(cp, refd, r.c * this->col * Colors(this->smooth)));
		if (this->smooth < 1.) {
			Vector u0(vertical(nf));
			Vector u1(nf % u0);
			double difc(sqrt(colorStrength(r.c) / color_visible_thres));
			int ea(alpha_count * difc);
			int et(theta_count * difc);
			if (ea < 2) {
				ea = 2;
			}
			if (et < 2) {
				et = 2;
			}
			double erat(log(ea * et + 3) / (ea * et));
			double cea(1. / (ea + 1));
			double cet(1. / et);
			for (int i = 0; i < ea; ++ i) {
				for (int j = 0; j < et; ++ j) {
					double theta((ea - i + randf()) * PI * .5 * cea);
					double alpha((j + randf()) * cet * PI * 2);
					Vector u(u0 * cos(alpha) + u1 * sin(alpha));
					Vector d(nf * cos(theta) + u * sin(theta));
					double weaken_rat((1. - this->smooth) * erat * cos(theta));
					out_rays.push_back(Ray(cp, d, r.c * this->col * Colors(weaken_rat), 1));
				}
			}
		}
		return out_rays;
	}

	Vector Triangle::reflectDirection(Vector v) {
		Plane p(*this);
		Vector uf(p.n.unify());
		double len_proj(uf * v);
		return v - uf * (len_proj * 2.);
	}
};
