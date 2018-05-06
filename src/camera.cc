#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>

#include <define.hh>
#include <colors.hh>
#include <scene.hh>
#include <camera.hh>
#include <ray.hh>

#include <lodepng.h>

#ifdef DEBUG_OUT
#include <iostream>
#endif

namespace Canyon {
	int Camera::render(Scene& scene, int width_, int height_) {
		this->width = width_;
		this->height = height_;
		if (this->canvas) {
			for (int i = 0; i < this->height; ++ i) {
				delete [] this->canvas[i];
			}
			delete [] this->canvas;
		}
		this->canvas = new Colors*[this->height];
		for (int i = 0; i < this->height; ++ i) {
			this->canvas[i] = new Colors[this->width];
		}
		for (int i = 0; i < this->height; ++ i) {
			for (int j = 0; j < this->width; ++ j) {
				Ray trace_ray(eye, vb + vy * ((double)i / (this->height - 1)) + vx * ((double)j / (this->width - 1)) - eye);
				trace_ray.c = Colors(1, 1, 1);
				this->canvas[i][j] = scene.getRayResult(trace_ray);
#ifdef DEBUG_OUT
				static const char clrs[] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0};
				std::cerr << clrs << i << "/" << this->height << ", " << j << "/" << this->width << "\tRendered       ";
#endif
			}
		}
#ifdef DEBUG_OUT
		std::cerr << "Render down\n";
#endif
		return 0;
	}

	typedef unsigned char uchar;

	inline uchar f2uchar(double x) {
		if (x > 1.) {
			return 255;
		}
		uchar r(round(x * 255));
		return r;
	}

	int Camera::save(const char* filename) {
		std::vector<uchar> img;
		for (int i = 0; i < this->height; ++ i) {
			for (int j = 0; j < this->width; ++ j) {
				img.push_back(f2uchar(this->canvas[i][j].r));
				img.push_back(f2uchar(this->canvas[i][j].g));
				img.push_back(f2uchar(this->canvas[i][j].b));
				img.push_back(0);
			}
		}
		lodepng::encode(filename, img, this->width, this->height);
	}
};
