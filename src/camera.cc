#include <opencv2/opencv.hpp>
#include <cmath>

#include <define.hh>
#include <colors.hh>
#include <scene.hh>
#include <camera.hh>
#include <ray.hh>


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

	inline uchar f2uchar(double x) {
		if (x > 1.) {
			return 255;
		}
		uchar r(round(x * 255));
		return r;
	}

	int Camera::save(const char* filename) {
		cv::Mat img(this->height, this->width, CV_8UC(4));
		cv::Mat w;
		w = img(cv::Range(0, this->height), cv::Range(0, this->width));
		for (int x = 0; x < this->height; ++ x) {
			for (int y = 0; y < this->width; ++ y) {
				w(cv::Range(this->height - x - 1, this->height - x), cv::Range(this->width - y - 1, this->width - y)) = cv::Scalar(
						f2uchar(this->canvas[x][y].r), 
						f2uchar(this->canvas[x][y].g), 
						f2uchar(this->canvas[x][y].b), 0);
			}
		}
		std::vector<int> compression_params;
		compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);

		cv::namedWindow("Display img", cv::WINDOW_AUTOSIZE);
		cv::imshow("Display img", img);
		cv::waitKey(0);

		// cv::imwrite(filename, img, compression_params);
	}
};
