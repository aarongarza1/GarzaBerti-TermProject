

#include "engine.h"
#include "glm/ext.hpp"
#include <chrono>
#include <thread>
Engine::Engine(const char* name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;

}


Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT);
  if(!m_window->Initialize())
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }
  glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetScrollCallback(m_window->getWindow(), scroll_callback);
  glfwSetCursorPosCallback(m_window->getWindow(), cursorPositionCallBack);
  glfwSetKeyCallback(m_window->getWindow(), key_callback);

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while (!glfwWindowShouldClose(m_window->getWindow()))
  {
      ProcessInput();
      Display(m_window->getWindow(), glfwGetTime());
      glfwPollEvents();
  }
  m_running = false;

}

void Engine::ProcessInput()
{
    m_graphics->getCamera()->UpdateView(cameraPos, cameraFront, fov);
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->getWindow(), true);
    if (!gameMode)
    {
        
        //glfwSetCursorPosCallback(m_window->getWindow(), NULL);
        m_graphics->setGameMode(gameMode);
        secondCameraPos = m_graphics->getCamera()->getCameraPos();
        float cameraSpeed = 0.1;//static_cast<float>(2.5 * deltaTime);
        
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
           change = true;
            m_graphics->setRot(glm::vec3(-1., 0., 0.), glm::vec3(.01, 0., 0.));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
            change = true;
            m_graphics->setRot(glm::vec3(1., 0., 0.), glm::vec3(-.01, 0., 0.));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
           change = true;
            m_graphics->setRot(glm::vec3(0., 0., -1.), glm::vec3(0., 0., -.01));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
          change = true;
            m_graphics->setRot(glm::vec3(0., 0., 1.), glm::vec3(0., 0., .01));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
           change = true;
            m_graphics->setRot(glm::vec3(0., -1., 0.), glm::vec3(0., .01, 0.));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
            change = true;
            m_graphics->setRot(glm::vec3(0., 1., 0.), glm::vec3(0., -.01, 0.));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
           change = true;
            m_graphics->setSpeed(glm::vec3(0.02, 0.02, 0.02));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            if (change)
            {
                m_graphics->setFirst(false);
            }
            change = true;
            m_graphics->setSpeed(glm::vec3(-0.03, -0.03, -0.03));
        }
        UpdateCamera();
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_F) == GLFW_PRESS)
    {
        gameMode = false;
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_R) == GLFW_PRESS)
    {
        gameMode = true;
        m_graphics->setGameMode(gameMode);
        if (gameMode)
            fov == 45;
        m_graphics->findClosestPlanet(secondCameraPos);
        
        firstCameraPos = m_graphics->getClosestPlanet();
        secondCameraPos = firstCameraPos;
        m_graphics->getCamera()->UpdateView(firstCameraPos + gameModeOffsets[currOffset], cameraFront, fov);
    }
    if (gameMode)
    {
        glfwSetKeyCallback(m_window->getWindow(), key_callback);
        firstCameraPos = m_graphics->getClosestPlanet();
        secondCameraPos = firstCameraPos;
        m_graphics->getCamera()->UpdateView(firstCameraPos + gameModeOffsets[currOffset], cameraFront, fov);
    }/*
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_RELEASE)
        {
            if (currentOffset + 1 > 5)
                currentOffset = 0;
            else
                currentOffset += 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_RELEASE)
        {
            if (currentOffset - 1 < 0)
                currentOffset = 5;
            else
                currentOffset -= 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        
    }*/



}

void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
 
    glfwGetCursorPos(window, &xpos, &ypos);
    std::cout << "Position: (" << xpos << ":" << ypos << ")";
}

unsigned int Engine::getDT()
{
  //long long TimeNowMillis = GetCurrentTimeMillis();
  //assert(TimeNowMillis >= m_currentTimeMillis);
  //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  //m_currentTimeMillis = TimeNowMillis;
  //return DeltaTimeMillis;
    return glfwGetTime();
}

long long Engine::GetCurrentTimeMillis()
{
  //timeval t;
  //gettimeofday(&t, NULL);
  //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  //return ret;
    return (long long) glfwGetTime();
}

void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render();
    m_window->Swap();
    m_graphics->HierarchicalUpdate2(time);
        
}

static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos) {
    float xposIn = static_cast<float>(xpos);
    float yposIn = static_cast<float>(ypos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        if (currOffset + 1 > 5)
            currOffset = 0;
        else
            currOffset += 1;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        if (currOffset - 1 < 0)
            currOffset = 5;
        else
            currOffset -= 1;
    }
}