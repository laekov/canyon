#include <fstream>
#include <iostream>
#include <cstring>

#include <camera.hh>
#include <scene.hh>

int main(int args, char* argv[]) {
	char default_scene_file[] = "data/faces.mypoints";
	char default_cam_config_file[] = "data/cam.mypoints";
	char default_output_file[] = "results/tmp.png";
	char* scene_file = default_scene_file;
	char* cam_config_file = default_cam_config_file;
	char* output_file = default_output_file;
	int nwid(200);
	int nhei(160);
	for (int i = 1; i < args; ++ i) {
		if (!strcmp(argv[i], "-x")) {
			nwid = atoi(argv[++ i]);
		} else if (!strcmp(argv[i], "-y")) {
			nhei = atoi(argv[++ i]);
		} else if (!strcmp(argv[i], "-o")) {
			output_file = argv[++ i];
		} else if (!strcmp(argv[i], "-scene")) {
			scene_file = argv[++ i];
		} else if (!strcmp(argv[i], "-camera")) {
			cam_config_file = argv[++ i];
		}
	}
	Canyon::Scene scene;
	scene.load(scene_file);
	Canyon::Camera cam;
	cam.load(cam_config_file);
	cam.render(scene, nwid, nhei, output_file);
}

