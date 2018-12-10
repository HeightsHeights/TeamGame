#include "audioManager.h"

#include <fstream>

#define SE_DIR_PATH "./data/"
#define BGM_DIR_PATH "./data/"

std::string SE_NAME[SE_NUMBER] =
    {
        ,
        ,

};

// bool AudioManager::initAudio(){
//     Mix_Init(MIX_INIT_MP3);
//     if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,1024) == -1){
//         fprintf(stderr,"Error --> open audio device\n");
//         return false;
//     }
//     return true;
// }

// void AudioManager::playAudio(Sound_ID aid){
//     audio[aid] -> playAudio();
// }

// void AudioManager::stopAudio(Sound_ID aid){
//     audio[aid] -> stopAudio();
// }
