#include <double.hh>

#include <cstdlib>

namespace Canyon {
	int sgn(const double& x) {
		return x < -eps ? -1 : (x > eps ? 1 : 0);
	}

	double sqr(const double& x) {
		return x * x;
	}

	double randf() {
		return (rand() & 0xffffff) / (double)0xffffff;
	}
};
