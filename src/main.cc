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
	cam.eye = Canyon::Point3(50, 3, 50);
	cam.vb = Canyon::Point3(49, 3.9, 49.2);
	cam.vx = Canyon::Vector(2, 0, 0);
	cam.vy = Canyon::Vector(0, 0, 1.6);
	// cam.render(scene, 800, 640);
	cam.render(scene, 400, 320);
	// cam.render(scene, 200, 160);
	cam.save("qaq.png");
}

