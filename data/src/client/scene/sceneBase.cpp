#include "./sceneBase.h"

BaseScene::BaseScene(WindowManager *window)
{
    this->window = window;
}
bool BaseScene::init()
{
}
SCENE_ID BaseScene::reactController(ControllerParam param)
{
}
SCENE_ID BaseScene::executeCommand(int command)
{
}
void BaseScene::drawWindow()
{
}