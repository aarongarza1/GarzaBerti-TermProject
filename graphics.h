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
    float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }
  private:
    std::string ErrorString(GLenum error);

    bool collectShPrLocs();
    void ComputeTransforms (double dt, std::vector<float> speed, std::vector<float> dist,
        std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, 
        glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat);

    stack<glm::mat4> modelStack;

    Camera *m_camera;
    Shader *m_shader;
    Shader* m_shaderCubemap;
    int gameMode;
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_normalMatrix;
    GLint m_positionAttrib;
    GLint m_colorAttrib;
    GLint m_tcAttrib;
    GLint m_hasTexture;

    //light stuff
    GLint globalAmbLoc;
    GLint lightALoc;
    GLint lightDLoc;
    GLint lightSLoc;
    GLint lightPosLoc;

    GLint mAmbLoc;
    GLint mDiffLoc;
    //GLint mNormLoc;
    GLint mSpecLoc;
    GLint mShineLoc;

    GLint hasN;

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
    Cubemap* m_skybox;
    std::vector<Mesh*> asteroidBelt;
    std::vector<Mesh*> asteroidBelt2;
    std::vector<float> randomFloats1;
    std::vector<float> randomFloats2;
    std::vector<float> randomFloats3;




    //LIGHT SETTINGS
    glm::vec3 initialLightLoc = glm::vec3(5.0f, 2.0f, 3.0f);
    float lightPos[3];
    glm::mat4 rMat;
    // white light
    float globalAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float lightAmbient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float lightDiffuse[4] = { 0.9f, 0.8f, .8f, 1.0f };
    float lightSpecular[4] = { 0.2f, 0.15f, 0.1f, 1.0f };
};

#endif /* GRAPHICS_H */
