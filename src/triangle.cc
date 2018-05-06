#include <define.hh>

#include <triangle.hh>
#include <line.hh>
#include <plane.hh>

#ifdef DEBUG_OUT
#include <iostream>
#endif

namespace Canyon {
	const int diffuse_reflect_count = 500;

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
		out_rays.push_back(Ray(cp, refd, r.c * this->col * Colors(this->smooth)));
		if (this->smooth < 1.) {
			refd = refd.unify();
			Vector u0(vertical(refd));
			Vector u1(refd % u0);
			int e(diffuse_reflect_count * colorStrength(r.c));
			double erat(log(e + 3) / e);
			for (int i = 0; i < e; ++ i) {
				double theta(randf() * PI * .5);
				double alpha(randf() * PI * 2);
				Vector u(u0 * cos(alpha) + u1 * sin(alpha));
				Vector d(refd * cos(theta) + u * sin(theta));
				double weaken_rat((1. - this->smooth) * erat * cos(theta));
				out_rays.push_back(Ray(cp, d, r.c * this->col * Colors(weaken_rat)));
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
