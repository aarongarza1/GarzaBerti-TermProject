#ifndef ENGINE_H
#define ENGINE_H


#include <assert.h>
#include "window.h"
#include "graphics.h"

static void cursorPositionCallBack(GLFWwindow*, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// camera
static glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 12.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 10.0f, -16.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

static bool firstMouse = true;
static float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
static float pitch = 0.0f;
static float lastX = 800.0f / 2.0;
static float lastY = 600.0 / 2.0;
static float fov = 45.0f;
static int currOffset = 0;
// timing
static float deltaTime = 0.0f;	// time between current frame and last frame
static float lastFrame = 0.0f;
class Engine
{
  public:
    Engine(const char*  name, int width, int height);
    
    ~Engine();
    bool Initialize();
    void Run();
    void ProcessInput();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void Display(GLFWwindow*, double);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    void UpdateCamera() { m_graphics->getCamera()->UpdateView((m_graphics->getSpaceship()->getLocalBack() + glm::vec3(2.5, 2.5, 2.5) *  m_graphics->getSpaceship()->getForward()) + glm::vec3(0.0, 0.8, 0.0),
        m_graphics->getSpaceship()->getLocalBack(),
        m_graphics->getSpaceship()->getLocalUp(), 
        fov); }
    
  
  private:
    // Window related variables
    Window *m_window;    
    const char* m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    bool gameMode;
    bool change = false;
    glm::mat4 spaceShip;
    glm::vec3 firstCameraPos;
    glm::vec3 secondCameraPos;
    Graphics *m_graphics;
    glm::vec3 camOffset = { 2., 0.0, 2. };
    glm::vec3 gameModeOffsets[6] = {
        {0.0, 0.0, 1.2},
        {0.0, 0.0, -1.2},
        {1.2, 0.0, 0.0},
        {-1.2, 0.0, 0.0},
        {0.0, 1.2, 0.0},
        {0.0, -1.2, 0.0}
    };
    bool m_running;
    int currentOffset = 0;
};

#endif // ENGINE_H
