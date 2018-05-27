#include <ray.hh>
#include <plane.hh>
#include <line.hh>

namespace Canyon {
	Vector reflectDirection(Vector v, Vector n) {
		Vector uf(n.unify());
		double len_proj(uf * v);
		return v - uf * (len_proj * 2.);
	}
};
