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
            "nameFrames/statusmush",
            "nameFrames/statusbamboo",
            "main/hp",
            "main/hpback",
            "main/atkbuff",
            "main/hpbuff",
            "main/spbuff",
            "main/lifemush",
            "main/lifebamboo",
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
void StatusDrawer::draw(Vector2f pos, TEAM_ID id, unsigned int hp, bool alive, const char *name)
{
    if (hp > 999)
    {
        hp = 999;
    }

    float brightness = (float)(hp + 50) / 100;

    GuiRect dst = GuiRect(pos.x, pos.y - UNIT_WIDTH * 6 / 8, 4 * UNIT_WIDTH, UNIT_WIDTH * 2 + 10);
    image[IMAGE_NAME_FRAME_MUSH + id]->draw(NULL, &dst, (alive) ? 1.0f : 0.5f);

    GuiText *nameText = GuiTextLoader().load(FID_NORMAL, name, black);
    dst = GuiRect(pos.x + UNIT_WIDTH * 2 - std::string(name).length() * 15 / 2 + 10, pos.y - UNIT_WIDTH * 11 / 8 - 40, std::string(name).length() * 15, 30);
    nameText->draw(NULL, &dst, (alive) ? 1.0f : 0.5f);
    delete nameText;

    for (int i = 0; i < 3; i++)
    {
        if (i == 2 && hp == 0)
        {
            break;
        }
        dst = GuiRect(pos.x + 30 * (3 - i) + 80, pos.y - 40, 30, UNIT_WIDTH);
        image[hp % 10]->draw(NULL, &dst, brightness);
        hp = hp / 10;
    }
}

void StatusDrawer::drawTeamStatus(Vector2f pos, TEAM_ID id, TeamStatus status)
{
    if (id == TEAM_MUSH)
    {
        GuiRect dst = GuiRect(pos.x, pos.y, HP_WIDTH, UNIT_WIDTH);
        image[IMAGE_HPBACK]->draw(NULL, &dst, 0.0f);

        float chp = HP_WIDTH * ((float)status.hp / MAX_TEAM_HP);
        dst = GuiRect(pos.x, pos.y, chp, UNIT_WIDTH);
        image[IMAGE_HP]->draw(NULL, &dst, 1.0f);

        for (int i = 0; i < BUFF_NUMBER; i++)
        {
            dst = GuiRect(pos.x + 5 + 30 * i, pos.y - 45, UNIT_WIDTH / 2, UNIT_WIDTH / 2);
            image[IMAGE_ATKBUFF + i]->draw(NULL, &dst, (status.buff[i]) ? 1.0f : 0.2f);
        }

        dst = GuiRect(pos.x - 125, pos.y + UNIT_WIDTH, 560, 125);
        image[IMAGE_MUSHHPFRAME]->draw(NULL, &dst, 1.0f);
    }
    else
    {
        GuiRect dst = GuiRect(pos.x, pos.y, HP_WIDTH, UNIT_WIDTH);
        image[IMAGE_HPBACK]->draw(NULL, &dst, 0.0f);

        float cpos = HP_WIDTH * (1 - ((float)status.hp / MAX_TEAM_HP));
        float chp = HP_WIDTH * ((float)status.hp / MAX_TEAM_HP);
        dst = GuiRect(pos.x + cpos, pos.y, chp, UNIT_WIDTH);
        image[IMAGE_HP]->draw(NULL, &dst, 1.0f);

        for (int i = 0; i < BUFF_NUMBER; i++)
        {
            dst = GuiRect(pos.x + (310 + 30 * i), pos.y - 45, UNIT_WIDTH / 2, UNIT_WIDTH / 2);
            image[IMAGE_ATKBUFF + i]->draw(NULL, &dst, (status.buff[i]) ? 1.0f : 0.2f);
        }
        dst = GuiRect(pos.x - 35, pos.y + UNIT_WIDTH, 560, 125);
        image[IMAGE_BAMBOOHPFRAME]->draw(NULL, &dst, 1.0f);
    }
}

void StatusDrawer::drawTeamStatus(Vector2f pos, TEAM_ID id, TeamStatus status, Vector3f loc)
{
    float SIZE = 0.1f;
    if (id == TEAM_MUSH)
    {
        GuiRect dst = GuiRect(pos.x, pos.y, HP_WIDTH * SIZE, UNIT_WIDTH * SIZE);
        image[IMAGE_HPBACK]->draw(NULL, &dst, 0.0f, loc);

        loc.z -= 0.1f;
        float chp = HP_WIDTH * ((float)status.hp / MAX_TEAM_HP) * SIZE;
        dst = GuiRect(pos.x, pos.y, chp, UNIT_WIDTH * SIZE);
        image[IMAGE_HP]->draw(NULL, &dst, 1.0f, loc);

        loc.z -= 0.1f;
        for (int i = 0; i < BUFF_NUMBER; i++)
        {
            dst = GuiRect(pos.x + (5 + 30 * i) * SIZE, pos.y - 45 * SIZE, UNIT_WIDTH / 2 * SIZE, UNIT_WIDTH / 2 * SIZE);
            image[IMAGE_ATKBUFF + i]->draw(NULL, &dst, (status.buff[i]) ? 1.0f : 0.2f, loc);
        }

        loc.z -= 0.1f;
        dst = GuiRect(pos.x - 125 * SIZE, pos.y + UNIT_WIDTH * SIZE, 560 * SIZE, 125 * SIZE);
        image[IMAGE_MUSHHPFRAME]->draw(NULL, &dst, 1.0f, loc);
    }
    else
    {
        GuiRect dst = GuiRect(pos.x, pos.y, HP_WIDTH * SIZE, UNIT_WIDTH * SIZE);
        image[IMAGE_HPBACK]->draw(NULL, &dst, 0.0f, loc);

        loc.z -= 0.1f;
        float cpos = HP_WIDTH * (1 - ((float)status.hp / MAX_TEAM_HP)) * SIZE;
        float chp = HP_WIDTH * ((float)status.hp / MAX_TEAM_HP) * SIZE;
        dst = GuiRect(pos.x + cpos, pos.y, chp, UNIT_WIDTH * SIZE);
        image[IMAGE_HP]->draw(NULL, &dst, 1.0f, loc);

        loc.z -= 0.1f;
        for (int i = 0; i < BUFF_NUMBER; i++)
        {
            dst = GuiRect(pos.x + (310 + 30 * i) * SIZE, pos.y - 45 * SIZE, UNIT_WIDTH / 2 * SIZE, UNIT_WIDTH / 2 * SIZE);
            image[IMAGE_ATKBUFF + i]->draw(NULL, &dst, (status.buff[i]) ? 1.0f : 0.2f, loc);
        }

        loc.z -= 0.1f;
        dst = GuiRect(pos.x - 35 * SIZE, pos.y + UNIT_WIDTH * SIZE, 560 * SIZE, 125 * SIZE);
        image[IMAGE_BAMBOOHPFRAME]->draw(NULL, &dst, 1.0f, loc);
    }
}