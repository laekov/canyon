#include <fstream>
#include <iostream>

#include <camera.hh>
#include <scene.hh>

int main() {
	Canyon::Scene scene;
	std::ifstream fin("data/faces.mypoints");
	scene.load(fin);
	fin.close();
	Canyon::Camera cam;
	cam.eye = Canyon::Point3(50, -5, 50);
	cam.vb = Canyon::Point3(49, 0, 49);
	cam.vx = Canyon::Vector(2, 0, 0);
	cam.vy = Canyon::Vector(0, 0, 2);
	cam.render(scene, 640, 640);
	cam.save("QAQ");
}

