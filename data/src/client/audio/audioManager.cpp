#include "audioManager.h"

#include <fstream>

#define SE_DIR_PATH "./data/res/sound/se/"
#define BGM_DIR_PATH "./data/res/sound/bgm/"

std::string SE_NAME[SE_NUMBER] =
    {
        "attack.wav",
        "sodo.wav",
};

std::string BGM_NAME[BGM_NUMBER] =
    {
        "honobono.mp3",
        "famima.mp3",
};

AudioManager am;

bool AudioManager::init()
{
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        fprintf(stderr, "Error --> open audio device\n");
        return false;
    }

    for(int i = 0;i < BGM_NUMBER; i++){
        if(!am.bgm[i].loadFile((BGM_DIR_PATH + BGM_NAME[i]).c_str())){
            fprintf(stderr,"Error --> failed to initialization.\n");
            return false;
        }
    }

    for(int i = 0;i < SE_NUMBER; i++){
        if(!am.se[i].loadFile((SE_DIR_PATH + SE_NAME[i]).c_str())){
            fprintf(stderr,"Error --> failed to initialization.\n");
            return false;
        }
    }

    return true;
}

void AudioManager::playBGM(BGM_ID id){
    am.bgm[id].play();
}

void AudioManager::stopBGM(BGM_ID id){
    am.bgm[id].stop();
}

void AudioManager::volumeBGM(BGM_ID id){
    am.bgm[id].volume();
}

void AudioManager::playSE(SE_ID id){
    am.se[id].play(id);
}

void AudioManager::stopSE(SE_ID id){
    am.se[id].stop(id);
}

void AudioManager::volumeSE(SE_ID id){
    am.se[id].volume(id);
}