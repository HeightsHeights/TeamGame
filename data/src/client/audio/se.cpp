#include "./se.h"

bool SE::loadFile(const char *fileName){
    se = Mix_LoadMUS(fileName);
    if(se == NULL){
        fprintf(stderr,"Error --> failed to open sefile.\n");
        return false;
    }
    return true;
}

void SE::play(){
    Mix_PlayMusic(se,1);
}

void SE::stop(){
    Mix_FadeOutMusic(100);
}

void SE::volume(){
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}