#include "./bgm.h"

bool BGM::loadFile(const char *fileName){
    bgm = Mix_LoadMUS(fileName);
    if(bgm == NULL){
        fprintf(stderr,"Error --> failed to open bgmfile.\n");
        return false;
    }
    return true;
}

void BGM::play(){
    Mix_PlayMusic(bgm,-1);
}

void BGM::stop(){
    Mix_FadeOutMusic(2000);
}