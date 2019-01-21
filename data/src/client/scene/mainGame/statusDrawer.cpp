#include "./statusDrawer.h"

#include <fstream>

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

static const SDL_Color black = {0, 0, 0, 0};

StatusDrawer::StatusDrawer()
{
}
StatusDrawer::~StatusDrawer()
{
    cleanUp();
}

bool StatusDrawer::init()
{
    const std::string IMAGE_NAME[StatusDrawer::IMAGE_NUMBER - IMAGE_9 - 1] =
        {
            "nameFrames/nameFrameRed",
            "nameFrames/nameFrameBlue",
            "nameFrames/nameFrameYellow",
            "nameFrames/nameFrameGreen",
            "icon",
            "hp",
            "hpback",
        };

    std::string numbersNameTemplate = "numbers/number_";
    int i;
    for (i = IMAGE_0; i <= IMAGE_9; i++)
    {
        char numberString[4];
        sprintf(numberString, "%d", i);

        std::string imageName = numbersNameTemplate + std::string(numberString);
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + imageName + PNG_FILE_EXTENSION).c_str());

        if (image[i] == NULL)
        {
            return false;
        }
    }
    for (; i < IMAGE_NUMBER; i++)
    {
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + IMAGE_NAME[i - IMAGE_9 - 1] + PNG_FILE_EXTENSION).c_str());
        if (image[i] == NULL)
        {
            return false;
        }
    }
    return true;
}
void StatusDrawer::cleanUp()
{
}
void StatusDrawer::draw(Vector2f pos, COLOR_ID cid, unsigned int hp, bool alive, const char *name)
{
    if (hp > 999)
    {
        hp = 999;
    }

    float brightness = (float)(hp + 50) / 100;
    GuiRect dst = GuiRect(pos.x, pos.y, UNIT_WIDTH, UNIT_WIDTH);
    image[IMAGE_ICON]->draw(NULL, &dst, (alive) ? 1.0f : 0.5f);

    dst = GuiRect(pos.x, pos.y - UNIT_WIDTH * 9 / 8, 4 * UNIT_WIDTH, UNIT_WIDTH);
    image[IMAGE_NAME_FRAME_RED + cid]->draw(NULL, &dst, (alive) ? 1.0f : 0.5f);

    GuiText *nameText = GuiTextLoader().load(FID_NORMAL, name, black);
    dst = GuiRect(pos.x + UNIT_WIDTH * 2 - std::string(name).length() * 15 / 2, pos.y - UNIT_WIDTH * 11 / 8, std::string(name).length() * 15, 30);
    nameText->draw(NULL, &dst, (alive) ? 1.0f : 0.5f);
    delete nameText;

    for (int i = 0; i < 3; i++)
    {
        if (i == 2 && hp == 0)
        {
            break;
        }
        dst = GuiRect(pos.x + UNIT_WIDTH * (3 - i), pos.y, UNIT_WIDTH, UNIT_WIDTH);
        image[hp % 10]->draw(NULL, &dst, brightness);
        hp = hp / 10;
    }
}

void StatusDrawer::drawTeamStatus(Vector2f pos, unsigned int hp, CHARA_ID cid)
{
    if (cid == CHARA_MUSH)
    {
        GuiRect dst = GuiRect(pos.x, pos.y, HP_WIDTH, UNIT_WIDTH);
        image[IMAGE_HPBACK]->draw(NULL, &dst, 0.0f);
        float chp = HP_WIDTH * ((float)hp / MAX_HP);
        dst = GuiRect(pos.x, pos.y, chp, UNIT_WIDTH);
        image[IMAGE_HP]->draw(NULL, &dst, 1.0f);
        dst = GuiRect(pos.x - 125, pos.y, UNIT_WIDTH, UNIT_WIDTH);
        image[IMAGE_ICON]->draw(NULL, &dst, 1.0f);
    }
    else
    {
        GuiRect dst = GuiRect(pos.x, pos.y, HP_WIDTH, UNIT_WIDTH);
        image[IMAGE_HPBACK]->draw(NULL, &dst, 0.0f);
        float cpos = HP_WIDTH * (1 - ((float)hp / MAX_HP));
        float chp = HP_WIDTH * ((float)hp / MAX_HP);
        dst = GuiRect(pos.x + cpos, pos.y, chp, UNIT_WIDTH);
        image[IMAGE_HP]->draw(NULL, &dst, 1.0f);
        dst = GuiRect(pos.x + 490, pos.y, UNIT_WIDTH, UNIT_WIDTH);
        image[IMAGE_ICON]->draw(NULL, &dst, 1.0f);
    }
}