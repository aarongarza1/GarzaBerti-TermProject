#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <stack>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "sphere.h"
#include "mesh.h"
#include "Cubemap.h"

#define numVBOs 2;
#define numIBs 2;


class Graphics
{
  public:
    Graphics(int x);
    ~Graphics();
    bool Initialize(int width, int height);
    void HierarchicalUpdate2(double dt);
    void Render();

    Camera* getCamera() { return m_camera; }

  private:
    std::string ErrorString(GLenum error);

    bool collectShPrLocs();
    void ComputeTransforms (double dt, std::vector<float> speed, std::vector<float> dist,
        std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, 
        glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat);

    stack<glm::mat4> modelStack;

    Camera *m_camera;
    Shader *m_shader;
    int gameMode;
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_positionAttrib;
    GLint m_colorAttrib;
    GLint m_tcAttrib;
    GLint m_hasTexture;
    GLint m_isCubemap;

    Object* cubemap;
    Sphere* m_sun;
    Sphere* m_earth;
    Sphere* m_moon;
    Sphere* m_ceres;
    Sphere* m_eris;
    Sphere* m_jupiter;
    Sphere* m_mars;
    Sphere* m_mercury;
    Sphere* m_neptune;
    Sphere* m_saturn;
    Sphere* m_uranus;
    Sphere* m_venus;
    Mesh* m_mesh;
    Sphere* m_skybox;



};

#endif /* GRAPHICS_H */
