#include "colors.hh"

namespace Canyon {
	std::istream& operator >>(std::istream& fin, Colors& c) {
		fin >> c.r >> c.g >> c.b;
		c.r /= 256;
		c.g /= 256;
		c.b /= 256;
		return fin;
	}
	std::ostream& operator <<(std::ostream& fou, const Colors& c) {
		return fou << "RGB(" << c.r << ", " << c.g << ", " << c.b << ")";
	}

	Colors operator +(const Colors& a, const Colors& b) {
		return Colors(a.r + b.r, a.g + b.g, a.b + b.b);
	}
	Colors operator *(const Colors& a, const Colors& b) {
		return Colors(a.r * b.r, a.g * b.g, a.b * b.b);
	}
};
