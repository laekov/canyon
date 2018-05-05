#include <ray.hh>
#include <plane.hh>
#include <line.hh>

namespace Canyon {
	std::vector<Ray> rayShootOnTriangle(Ray r, Triangle t) {
		std::vector<Ray> out_rays;
		Line l(r.p, r.d);
		Plane p(t);
		Point3 cross_point(lineCrossPlane(l, p));
		if (cross_point.isNaN()) {
			return out_rays;
		}
		if (sgn((cross_point - r.p) * r.d) <= 0) {
			return out_rays;
		}
		if (!pointInTriangle(t, cross_point)) {
			return out_rays;
		}
		out_rays.push_back(Ray(cross_point, reflectDirection(p, r.d)));
		return out_rays;
	}

	Vector reflectDirection(Plane p, Vector v) {
		Vector uf(p.n.unify());
		double len_proj(uf * v);
		return v + uf * (len_proj * 2.);
	}
};
