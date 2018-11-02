#include "../../header/main/mainProgram.h"
#include "../../header/render/window.h"
#include "../../header/render/shader.h"
#include "../../header/render/rawmodel.h"

/******************************************************************************
 * メイン関数
******************************************************************************/
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK))
    {
        printf("error sdlinit\n");
        return false;
    }

    WindowManager window(argc, argv);
    ShaderManager::initShader();
    RawModel model = ModelLoader().loadFile("./data/res/gui/obj/mononoke.obj");

    window.clearWindow();
    ShaderManager::startShader();
    model.drawModel();
    ShaderManager::stopShader();
    window.swapWindow();
    SDL_Delay(1000);

    return 0;
}
