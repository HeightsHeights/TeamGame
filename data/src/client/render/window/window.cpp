#include "./window.h"

#include <GL/glut.h>

GLfloat light0pos[] = {0.0, 3.0, 5.0, 1.0};

/******************************************************************************
 * WindowManager
******************************************************************************/
WindowManager::WindowManager(int argc, char *argv[], const char *windowName)
{
    initSDLWindow(windowName);
    initOpenGL(argc, argv);
}

bool WindowManager::initSDLWindow(const char *windowName)
{
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL)
    {
        fprintf(stderr, "Error --> SDL_CreateWindow()\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        fprintf(stderr, "Error --> SDL_CreateRenderer()\n");
        return false;
    }
    return true;
}

bool WindowManager::initOpenGL(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void WindowManager::clearWindow()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::swapWindow()
{
    glFlush();
    SDL_GL_SwapWindow(window);
}