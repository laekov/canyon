#include <triangle.hh>
#include <line.hh>
#include <plane.hh>

namespace Canyon {
	bool Triangle::pointIn(Point3 p) {
		Vector a(this->a - p);
		Vector b(this->b - p);
		Vector c(this->c - p);
		Vector u(a % b);
		Vector v(b % c);
		Vector w(c % a);
		return sgn(u * v) == sgn(v * w);
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

	std::vector<Ray> Triangle::rayCrossOut(Ray r) {
		std::vector<Ray> out_rays;
		Point3 cp(this->rayCrossPoint(r));
		out_rays.push_back(Ray(cp, this->reflectDirection(r.d)));
		return out_rays;
	}

	Vector Triangle::reflectDirection(Vector v) {
		Plane p(*this);
		Vector uf(p.n.unify());
		double len_proj(uf * v);
		return v + uf * (len_proj * 2.);
	}
};
