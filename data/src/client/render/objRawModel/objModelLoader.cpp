#include "./objModelLoader.h"
#include "./objFileLoader.h"
#include "./objMtlFileLoader.h"

#define OBJFILE_EXTENSION ".obj"
#define MTLFILE_EXTENSION ".mtl"

#include <stdio.h>
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

    std::string objFileName = dirPath + fileName + OBJFILE_EXTENSION;
    std::string mtlFileName = dirPath + fileName + MTLFILE_EXTENSION;

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