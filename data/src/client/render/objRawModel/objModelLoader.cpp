#include "./objModelLoader.h"
#include "./objFileLoader.h"
#include "./objMtlFileLoader.h"

#include <stdio.h>
#define OBJ_NAME_LENGTH 256
#define OBJ_BUFFER_LENGTH 256
/******************************************************************************
 * ObjModelLoader
******************************************************************************/
ObjModelLoader::ObjModelLoader()
{
    /*nothing*/
}
ObjRawModel *ObjModelLoader::load(const std::string dirPath, const std::string fileName)
{

    ret = new ObjRawModel();

    std::string objFileName = dirPath + fileName + ".obj";
    std::string mtlFileName = dirPath + fileName + ".mtl";

    if (!ObjMtlFileLoader(ret, dirPath).load(mtlFileName.c_str()))
    {
        fprintf(stderr, "Error --> loadMtlFile(%s)\n", mtlFileName.c_str());
        return NULL;
    }
    if (!ObjFileLoader(ret).load(objFileName.c_str()))
    {
        fprintf(stderr, "Error --> loadObjFile(%s)\n", objFileName.c_str());
        return NULL;
    }

    return ret;
}