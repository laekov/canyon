#ifndef DOUBLE_HH
#define DOUBLE_HH

namespace Canyon {
	const double eps = 1e-8;

	int sgn(const double& x);
	double sqr(const double& x);

	const long long NaN_ll = 0xFFF8000000000000ll;
	const double NaN = *(double*)&NaN_ll;
};

#endif
