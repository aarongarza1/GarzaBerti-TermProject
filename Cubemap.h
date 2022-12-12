#ifndef CUBEMAP_H
#define CUBEMAP_H
#include <vector>
#include "graphics_headers.h"
#include "Texture.h"
    class Cubemap
    {
    public:
        Cubemap();
        Cubemap(glm::vec3 pivot);
        Cubemap(glm::vec3 pivot, const char* fname);

        ~Cubemap();
        void Update(glm::mat4 model);
        void Render(GLint posAttrib, GLint colAttrib, GLint tcAttribLoc, GLint hasTextureLoc);

        glm::mat4 GetModel();

        bool InitBuffers();
        void setupVerticies();


        GLuint getTextureID() { return m_texture->getTextureID(); }

        bool hasTex;
    private:
        glm::vec3 pivotLocation;
        glm::mat4 model;
        std::vector<Vertex> Vertices;
        std::vector<unsigned int> Indices;
        GLuint VB;
        GLuint IB;

        GLuint vao;

        float angle;

        Texture* m_texture;
    };

#endif

