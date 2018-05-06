#ifndef CAMERA_HH
#define CAMERA_HH

#include <point3.hh>
#include <colors.hh>
#include <vector.hh>

namespace Canyon {
	class Camera {
		public:
			Point3 eye, vb;
			Vector vx, vy;
			Colors** canvas;
			int height, width;

			Camera(): canvas(0) {}
			~Camera() {
				if (this->canvas) {
					for (int i = 0; i < this->height; ++ i) {
						if (this->canvas[i]) {
							delete [] this->canvas[i];
						}
					}
					delete [] this->canvas;
				}
			}

			int render(struct Scene&, int, int);
			int save(const char*);
	};
};

#endif
