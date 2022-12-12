#pragma once

#include "graphics_headers.h"
#include <vector>
class Skybox
{

    bool load_cube_map_side(
        GLuint texture, GLenum side_target, const char* file_name);
    void create_cube_map(
        const char* front,
        const char* back,
        const char* top,
        const char* bottom,
        const char* left,
        const char* right,
        GLuint* tex_cube);
	void initializeVertices();
	unsigned int loadCubemap(std::vector<std::string> faces);
};

