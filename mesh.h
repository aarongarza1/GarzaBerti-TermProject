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
    void Update(glm::mat4 model, bool move);
    void Render(GLint posAttrib, GLint colAttrib);
    void Render(GLint positionAttribLoc, GLint colorAttribLoc, GLint tcAttribLoc, GLint hasTex);

    glm::mat4 GetModel();
    glm::vec3 getLocalBack() { return localBack;  };
    glm::vec3 getLocalUp() { return localUp; };
    glm::vec3 getForward() { return forward; }
    bool InitBuffers();
    bool loadModelFromFile(const char* path);
    void UpdateVars(glm::vec3 rotStuff);
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
    void setSpeed(glm::vec3 speed) { engineSpeed += speed;  }

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    float rotSpeex;
    float rotSpeey;
    float rotSpeez;
    glm::vec3 engineSpeed;
    GLuint VB;
    glm::mat4 inverted;
    glm::vec3 forward;
    GLuint IB;
    glm::vec3 localBack;
    glm::vec3 localUp;
    Texture* m_texture;
    bool first = true;
    GLuint vao;

    float angle;
};

#endif