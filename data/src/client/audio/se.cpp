#include "./se.h"

bool SE::loadFile(const char *fileName){
    se = Mix_LoadWAV(fileName);
    if(se == NULL){
        fprintf(stderr,"Error --> failed to open sefile.\n");
        return false;
    }
    return true;
}

void SE::play(){
    Mix_PlayChannel(-1,se,0);
}

void SE::stop(){
    Mix_HaltChannel(-1);
}