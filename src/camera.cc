#include <fstream>
#include <string>
#include <algorithm>
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
	int Camera::render(Scene& scene, int width_, int height_, char* tmpfile) {
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
#if FALSE
// #ifdef DEBUG_OUT
		Ray trace_ray(eye, vb + vx * 0.65 + vy * 0.3375 - eye);
		trace_ray.c = Colors(1, 1, 1);
		Colors col = scene.getRayResult(trace_ray);
		std::cerr << col << std::endl;
		return 0;
		trace_ray = Ray(eye, vb + vx * 0.5 - eye);
		trace_ray.c = Colors(1, 1, 1);
		col = scene.getRayResult(trace_ray);
		std::cerr << col << std::endl;
		return 0;
#endif
		static int order[2333];
		for (int i = 0; i < this->height; ++ i) {
			order[i] = i;
		}
		std::random_shuffle(order, order + this->height);
		for (int ic = 0; ic < this->height; ++ ic) {
			int i(order[ic]);
#pragma omp parallel for schedule(dynamic, 1)
			for (int j = 0; j < this->width; ++ j) {
				Ray trace_ray(eye, vb + vy * ((double)i / (this->height - 1)) +
						      vx * ((double)j / (this->width - 1)) - eye);
				trace_ray.c = Colors(1, 1, 1);
				this->canvas[i][j] = scene.getRayResult(trace_ray);
#if FALSE 
				std::cerr << i << "/" << this->height << ", " << j << "/" <<
				           	 this->width << "\tRendered strength = " << 
							 colorStrength(this->canvas[i][j]) << "\n";
#endif
			}
#ifdef DEBUG_OUT
			if (((ic + 1) & 0x7) == 0) {
				std::cerr << ic << " lines rendered";
				if (tmpfile) {
					this->save(tmpfile);
					std::cerr << " written to " << tmpfile;
				} 
				std::cerr << '\n';
			}
#endif
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
		for (int i = this->height - 1; i >= 0; -- i) {
			for (int j = 0; j < this->width; ++ j) {
				img.push_back(f2uchar(this->canvas[i][j].r));
				img.push_back(f2uchar(this->canvas[i][j].g));
				img.push_back(f2uchar(this->canvas[i][j].b));
				img.push_back(255);
			}
		}
		lodepng::encode(filename, img, this->width, this->height);
	}

	void Camera::load(const char* filename) {
		std::ifstream fin(filename);
		fin >> this->eye >> this->vb >> this->vx >> this->vy;
	}
};
