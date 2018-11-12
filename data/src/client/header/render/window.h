#pragma once

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
/******************************************************************************
 * ウィンドウ関係に必要なヘッダーの読み込み
******************************************************************************/
#include <GL/glut.h>
#include <SDL2/SDL.h>
/******************************************************************************
 * class WindowManager
 * 機能1：SDL_WindowやSDL_Rendererを保持する
 * 機能2：コンストラクタでSDL_WindowやSDL_Rendererを初期化
 * 機能3：画面を初期化するclearWindow
 * 機能4：画面を表示するswapWindow
******************************************************************************/
class WindowManager
{
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool initSDLWindow();
  bool initOpenGL(int argc, char *argv[]);

public:
  WindowManager(int argc, char *argv[]);
  void clearWindow();
  void swapWindow();
};
