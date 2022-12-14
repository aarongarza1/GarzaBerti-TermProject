#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    void UpdateView(glm::vec3 speed, glm::vec3 rot, float fov);
    glm::vec3 returnCamFront();
    glm::vec3 getCameraPos() { return cameraPos; }
private:
    float x = 0.0f;
    float y = 1.0f;
    float z = 12.0f;
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraFront = glm::vec3(0.0f, 10.0f, -16.0f);
    glm::vec3 cameraPos = glm::vec3(0., 1., 12.);
    float fov = 45.f;
    int width;
    int height;
};


#endif /* CAMERA_H */
