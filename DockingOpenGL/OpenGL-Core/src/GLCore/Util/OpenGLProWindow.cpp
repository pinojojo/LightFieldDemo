#include "glpch.h"
#include "OpenGLProWindow.h"
#include <GLFW/glfw3.h>


OpenGLProWindow::OpenGLProWindow(int position_x, int position_y, int width, int height)
{
    GLFWwindow* window;
    int windowSizeW = width, windowSizeH = height;

    if (!glfwInit())
        return;

    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    // make the window's context current
    //glfwMakeContextCurrent(window);

    // reset the window hints to default
    glfwDefaultWindowHints();

    //glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    // show the window
    //glfwShowWindow(window);
}
