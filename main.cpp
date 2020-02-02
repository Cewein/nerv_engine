#include <glad/glad.h>
#include "dependencies.h"
#include "src/engine.h"


int main()
{
	nerv::init::launch();

	std::vector<float> vertices = {
	-1.0f, -1.0f, -0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -0.0f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, -0.0f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
	 1.0f,  1.0f, -0.0f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 0.0f,
	};

	std::vector<size_t> indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	nerv::object obj(vertices, new nerv::material(nullptr, new nerv::shader("shader/raytraced.frag.glsl")));

	nerv::scene * worldScene = new nerv::scene();
	nerv::camera * cam = new nerv::camera(nerv::camera::projectionType::PERSPECTIVE_PROJECTION);
	cam->transform->translate(glm::vec3(0., 0., 3.));

	while (nerv::window::get().isOpen()) {

		
		cam->sendInfo();

		obj.show();

		nerv::window::get().update();
		nerv::keyboard::updateCameraKeyboard(cam);
		nerv::mouse::updateCameraMouse(cam);
	}

	delete worldScene;

	nerv::window::get().close();
	return EXIT_SUCCESS;
}