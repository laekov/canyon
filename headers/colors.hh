#ifndef COLORS_HH
#define COLORS_HH

#include <istream>

namespace Canyon {
	class Colors {
		public:
			double r, g, b;
			Colors(double r_, double g_, double b_): r(r_), g(g_), b(b_) {}
			Colors(const Colors& c_): r(c_.r), g(c_.g), b(c_.b) {}
	};

	std::istream& operator >>(std::istream& fin, Colors& c);
	Colors operator *(const Colors& a, const Colors& b);
};

#endif
