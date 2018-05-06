#ifndef COLORS_HH
#define COLORS_HH

#include <istream>
#include <ostream>

namespace Canyon {
	const double color_visible_thres = 1e-2;
	class Colors {
		public:
			double r, g, b;
			Colors(double r_ = 0, double g_ = 0, double b_ = 0): r(r_), g(g_), b(b_) {}
			Colors(const Colors& c_): r(c_.r), g(c_.g), b(c_.b) {}
			inline bool visible() {
				return r > color_visible_thres || 
					g > color_visible_thres || 
					b > color_visible_thres;
			}
			inline bool isSource() {
				return r == 1. || g == 1. || b == 1.;
			}
	};

	std::istream& operator >>(std::istream& fin, Colors& c);
	std::ostream& operator <<(std::ostream& fou, const Colors& c);
	Colors operator *(const Colors& a, const Colors& b);
	Colors operator +(const Colors& a, const Colors& b);
};

#endif
