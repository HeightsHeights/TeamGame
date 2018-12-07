#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "./audioLoder.h"

class BaseSound{
    private:
        static BGM *bg;
        static SE *s; 
    public:
        virtual bool loadFile(const char *fileName);
        virtual void playAudio();
        virtual void stopAudio();
};