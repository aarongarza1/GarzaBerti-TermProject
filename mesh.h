#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"
#include "Texture.h"

class Mesh
{
public:
    Mesh();
    Mesh(glm::vec3 pivot, const char* fname);
    Mesh(glm::vec3 pivot, const char* fname, const char* tname);

    ~Mesh();
    void Update(glm::mat4 model);
    void Render(GLint posAttrib, GLint colAttrib);
    void Render(GLint positionAttribLoc, GLint colorAttribLoc, GLint tcAttribLoc, GLint hasTex);

    glm::mat4 GetModel();

    bool InitBuffers();
    bool loadModelFromFile(const char* path);

    bool hasTex;
    bool hasNorm;
    GLuint getTextureID() { return m_texture->getTextureID(); }
    float matAmbient[4] = { 0.2, 0.2, 0.2, 1.0 };
    float matDiff[4] = { 1.0, 1., 1., 1.0 };
    float matSpec[4] = { .8, .8, .8, 1.0 };
    float matShininess = 10.0;
    void setShininess(float x) { matShininess = x; }
    void setAmbient(float x, float y, float z) { matAmbient[0] = x; matAmbient[1] = y; matAmbient[2] = z; }
    void setDiff(float x, float y, float z) { matDiff[0] = x; matAmbient[1] = y; matAmbient[2] = z; }
    void setSpec(float x, float y, float z) { matSpec[0] = x; matSpec[1] = y; matSpec[2] = z; }


private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    Texture* m_texture;

    GLuint vao;

    float angle;
};

#endif