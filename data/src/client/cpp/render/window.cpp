#include "../../header/render/window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };

/******************************************************************************
 * WindowManager
******************************************************************************/
WindowManager::WindowManager(int argc, char *argv[])
{
    initSDLWindow();
    initOpenGL(argc, argv);
}

bool WindowManager::initSDLWindow()
{
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void WindowManager::clearWindow()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::swapWindow()
{
    SDL_GL_SwapWindow(window);
}