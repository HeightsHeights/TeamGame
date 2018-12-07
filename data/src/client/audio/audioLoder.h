#include <SDL2/SDL_mixer.h>

typedef enum{
    BGM_NULL = 0,
    BGM_TITLE = 1,
    BGM_MAIN = 2,
    BGM_NUMBER = 3,
}BGM_ID;

typedef enum{
    SE_NULL = 0,
    SE_SODO = 1,
    SE_HAMMER = 2,
    SE_NUMBER = 3,
}SE_ID;

class BGM{
    private:
    public:
        static Mix_Music *bgm[BGM_NUMBER];
};

class SE{
    private:
    public:
        static Mix_Music *se[SE_NUMBER];
};

