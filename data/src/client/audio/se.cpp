#include "./se.h"

bool SE::loadFile(const char *fileName){
    se = Mix_LoadWAV(fileName);
    if(se == NULL){
        fprintf(stderr,"Error --> failed to open sefile.\n");
        return false;
    }
    return true;
}

void SE::play(int chnum){
    Mix_PlayChannel(chnum,se,0);
}

void SE::stop(int chnum){
    Mix_FadeOutChannel(chnum,100);
}

void SE::volume(int chnum){
    Mix_Volume(chnum,MIX_MAX_VOLUME/2);
}