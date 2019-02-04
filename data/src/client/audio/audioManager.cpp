#include "audioManager.h"
#include <fstream>

#define SE_DIR_PATH "./data/res/sound/se/"
#define BGM_DIR_PATH "./data/res/sound/bgm/"

#define WAV_FILE_EXTENSION ".wav"
#define MP3_FILE_EXTENSION ".mp3"

BGM AudioManager::bgm[BGM_NUMBER];
SE AudioManager::se[SE_NUMBER];

bool AudioManager::init()
{
    const std::string BGM_NAME[BGM_NUMBER] =
        {
            "titlebgm",
            "mainbgm",
            "victory",
        };
    const std::string SE_NAME[SE_NUMBER] =
        {
            "decision",
            "cursor",
            "ready",
            "blow",
            "soword01",
            "gun",
            "explosion",
            "miss",
            "whistle",
            "buff",
        };
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        fprintf(stderr, "Error --> open audio device\n");
        return false;
    }

    for (int i = 0; i < BGM_NUMBER; i++)
    {
        if (!bgm[i].loadFile((BGM_DIR_PATH + BGM_NAME[i] + MP3_FILE_EXTENSION).c_str()))
        {
            fprintf(stderr, "Error --> failed to initialization.\n");
            return false;
        }
    }

    for (int i = 0; i < SE_NUMBER; i++)
    {
        if (!se[i].loadFile((SE_DIR_PATH + SE_NAME[i] + WAV_FILE_EXTENSION).c_str()))
        {
            fprintf(stderr, "Error --> failed to initialization.\n");
            return false;
        }
    }

    return true;
}

void AudioManager::playBGM(BGM_ID id)
{
    bgm[id].play();
}

void AudioManager::stopBGM(BGM_ID id)
{
    bgm[id].stop();
}

void AudioManager::volumeBGM(BGM_ID id)
{
    bgm[id].volume();
}

void AudioManager::playSE(SE_ID id)
{
    se[id].play(id);
}

void AudioManager::stopSE(SE_ID id)
{
    se[id].stop(id);
}

void AudioManager::volumeSE(SE_ID id)
{
    se[id].volume(id);
}

void AudioManager::fadeInBGM(BGM_ID id, int ms)
{
    bgm[id].fadeIn(ms);
}

void AudioManager::fadeOutBGM(BGM_ID id, int ms)
{
    bgm[id].fadeOut(ms);
}