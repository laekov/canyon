#ifndef DOUBLE_HH
#define DOUBLE_HH

#include <cmath>

namespace Canyon {
	const double eps = 1e-8;
	const double PI = acos(-1);
    const double INF = 1e99;

	int sgn(const double& x);
	double sqr(const double& x);
	double randf();
};

#endif
