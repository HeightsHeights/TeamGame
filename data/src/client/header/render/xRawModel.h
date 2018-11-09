#pragma once

#pragma once

#define MAX_MATERIAL_NAME 128
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
/******************************************************************************
 * Xモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../../common/header/vector.h"
#include "../../../common/header/quat.h"

#include <stdio.h>
#include <vector>
#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class XRawModel{
    private:
    public:
    void draw();
};

class XModelLoader{
    private:
    public:
    XRawModel *load(const char *fileName);
};