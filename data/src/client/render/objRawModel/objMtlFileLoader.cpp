#include "./objMtlFileLoader.h"
#include "./objTextureLoader.h"

#include <string.h>

#define OBJ_BUFFER_LENGTH 256

ObjMtlFileLoader::ObjMtlFileLoader(ObjRawModel *model, std::string dirPath)
{
    this->model = model;
    this->texLoader = ObjTextureLoader(dirPath);
}
bool ObjMtlFileLoader::readFile()
{
    char buf[OBJ_BUFFER_LENGTH] = {0};

    while (1)
    {
        file >> buf;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(buf, "newmtl"))
        {
            createMaterial();
        }
    }
    return true;
}

void ObjMtlFileLoader::createMaterial()
{
    char buf[OBJ_BUFFER_LENGTH] = {0};

    char name[MAX_MATERIAL_NAME];
    Touple4f ambient;
    Touple4f diffuse;
    Touple4f specular;
    Touple4f emissive;
    float power = 1.0f;
    GLuint texId;

    file >> buf;
    strcpy(name, buf);
    while (1)
    {
        file >> buf;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(buf, "Ns"))
        {
            float ns;
            file >> ns;
            power = ns;
        }
        else if (0 == strcmp(buf, "Ka"))
        {
            float r, g, b;
            file >> r >> g >> b;
            ambient = Touple4f(r, g, b, 1.0f);
        }
        else if (0 == strcmp(buf, "Kd"))
        {
            float r, g, b;
            file >> r >> g >> b;
            diffuse = Touple4f(r, g, b, 1.0f);
        }
        else if (0 == strcmp(buf, "Ks"))
        {
            float r, g, b;
            file >> r >> g >> b;
            specular = Touple4f(r, g, b, 1.0f);
        }
        else if (0 == strcmp(buf, "Ke"))
        {
            float r, g, b;
            file >> r >> g >> b;
            emissive = Touple4f(r, g, b, 1.0f);
        }
        else if (0 == strcmp(buf, "Ni"))
        {
            float ni;
            file >> ni;
        }
        else if (0 == strcmp(buf, "d"))
        {
            float d;
            file >> d;
        }
        else if (0 == strcmp(buf, "illum"))
        {
            skipLine();
            unsigned int posFile = file.tellg();
            file >> buf;
            if (0 == strcmp(buf, "map_Kd"))
            {
                std::string textureName;
                file >> textureName;
                texLoader.load(textureName, &texId);
            }
            else 
            {
                file.seekg(posFile, std::fstream::beg);
            }
            break;
        }
    }
    model->pushMaterial(ObjMaterial(name, ambient, diffuse, specular, emissive, power, texId));
}

bool ObjMtlFileLoader::load(const char *filePath)
{
    if (!loadFile(filePath))
    {
        return false;
    }

    return true;
}