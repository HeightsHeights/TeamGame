#include "./objRawModel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <limits>

#define OBJ_NAME_LENGTH 256
#define OBJ_BUFFER_LENGTH 256

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
int a = 0;
GLuint TextureID = 0;
/******************************************************************************
 * ObjSubset
******************************************************************************/
ObjSubset::ObjSubset()
{
    /*nothing*/
}
ObjSubset::ObjSubset(unsigned int vertexCount, unsigned int materialId)
{
    this->vertexCount = vertexCount;
    this->materialId = materialId;
}
/******************************************************************************
 * ObjMaterial
******************************************************************************/
ObjMaterial::ObjMaterial()
{
    /*nothing*/
}
ObjMaterial::ObjMaterial(char *name, Touple4f ambient, Touple4f diffuse, Touple4f specular, Touple4f emissive, float power)
{
    strcpy(this->name, name);
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->emissive = emissive;
    this->power = power;
}
bool ObjMaterial::isEqualName(const char *name)
{
    if (strcmp(this->name, name) == 0)
    {
        return true;
    }
    return false;
}
void ObjMaterial::applyMaterial()
{
    /*マテリアルの適用*/
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &power);
}

void ObjModelLoader::createTexture(std::string fileName)
{
    SDL_Surface *Surface = IMG_Load((this->dirPath + fileName).c_str());
    if (!Surface)
    {
        return;
    }
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    int Mode = GL_RGB;
    if (Surface->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    TextureID++;
}
/******************************************************************************
 * ObjRawModel
******************************************************************************/
ObjRawModel::ObjRawModel()
{
    /*nothing*/
}
void ObjRawModel::setVao(GLuint vao)
{
    this->vao = vao;
}
void ObjRawModel::pushSubset(const ObjSubset subset)
{
    subsets.push_back(subset);
}
void ObjRawModel::pushMaterial(const ObjMaterial material)
{
    materials.push_back(material);
}
unsigned int ObjRawModel::getMtlId(const char *mName)
{
    unsigned int mNum = materials.size();
    for (unsigned int i = 0; i < mNum; i++)
    {
        if (materials[i].isEqualName(mName))
        {
            return i;
        }
    }
    return -1;
}
void ObjRawModel::draw()
{

    unsigned int bIndex = 0;
    for (int i = 0; i < subsets.size(); i++)
    {
        /*サブセットからデータ読み込み*/
        //unsigned int bIndex = subsets[i].getBeginIndix();
        unsigned int vCount = subsets[i].getVertexCount();
        unsigned int mId = subsets[i].getMaterialId();

        /*色つけ*/
        materials[mId].applyMaterial();

        /*サブセットの描画*/
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, vCount, GL_UNSIGNED_INT, BUFFER_OFFSET(bIndex * sizeof(unsigned int)));
        bIndex += vCount;
        glBindVertexArray(0);
    }
}
/******************************************************************************
 * ObjModelLoader
******************************************************************************/
bool ObjModelLoader::loadObjFile(const char *filename)
{
    /*ファイルを読み込んでObjSubsetに変換しプッシュ*/
    char buf[OBJ_BUFFER_LENGTH] = {0};

    //ファイルを開ける
    file.open(filename, std::fstream::in);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> objFile is not found\n");
        return false;
    }

    while (1)
    {
        file >> buf;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(buf, "o"))
        {
            createSubset();
        }
        else if (0 == strcmp(buf, "usemtl"))
        {
            file.seekg(-6, std::ios_base::cur);
            createSubset();
        }
    }

    Vector3f normalArraySum[vertices.size()];
    for (unsigned int i = 0; i < indices.size(); i++)
    {
        normalArraySum[indices[i]] += normals[normalIndices[i]];
    }

    Vector2f textureArray[indices.size()];
    for (unsigned int i = 0; i < indices.size(); i++)
    {
        textureArray[i] = textures[textureIndices[i]];
    }

    GLuint vao = createVao();
    bindIndicesBuffer(indices.size() * sizeof(unsigned int), &indices[0]);
    storeAttributeData(0, vertices.size() * sizeof(Vector3f), vertices[0], GL_FALSE);
    storeAttributeData(2, vertices.size() * sizeof(Vector3f), normalArraySum[0], GL_TRUE);
    storeAttributeData(3, textureIndices.size() * sizeof(Vector2f), textureArray[0], GL_FALSE);
    unbindVao();

    ret->setVao(vao);

    file.close();
    return true;
}
void ObjModelLoader::createSubset()
{
    char buf[OBJ_BUFFER_LENGTH] = {0};

    unsigned int numVertex = 0;

    int materialId;

    while (1)
    {
        file >> buf;
        if (!(file))
        {
            break;
        }
        if (0 == strcmp(buf, "v"))
        {
            float x, y, z;
            file >> x >> y >> z;
            vertices.push_back(Vector3f(x, y, z));
        }
        else if (0 == strcmp(buf, "vt"))
        {
            float u, v;
            file >> u >> v;
            textures.push_back(Vector2f(u, v));
        }
        else if (0 == strcmp(buf, "vn"))
        {
            float x, y, z;
            file >> x >> y >> z;
            normals.push_back(Vector3f(x, y, z));
        }
        else if (0 == strcmp(buf, "usemtl"))
        {
            file >> buf;
            materialId = ret->getMtlId(buf);
            break;
        }
    }
    while (1)
    {
        file >> buf;
        if (!file)
        {
            break;
        }

        if (0 == strcmp(buf, "o"))
        {
            file.seekg(-1, std::ios_base::cur);
            break;
        }
        else if (0 == strcmp(buf, "usemtl"))
        {
            file.seekg(-6, std::ios_base::cur);
            break;
        }
        else if (0 == strcmp(buf, "f"))
        {
            unsigned int iVertex, iTexCoord, iNormal;
            for (int iFace = 0; iFace < 3; iFace++)
            {
                numVertex++;
                file >> iVertex;
                indices.push_back(iVertex - 1);

                if ('/' == file.peek())
                {
                    file.ignore();

                    if ('/' != file.peek())
                    {
                        file >> iTexCoord;
                        textureIndices.push_back(iTexCoord - 1);
                    }

                    if ('/' == file.peek())
                    {
                        file.ignore();
                        file >> iNormal;
                        normalIndices.push_back(iNormal - 1);
                    }
                }
                //改行
                if ('\n' == file.peek())
                {
                    break;
                }
            }
        }
    }

    ret->pushSubset(ObjSubset(numVertex, materialId));
}
GLuint ObjModelLoader::createVao()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}
void ObjModelLoader::storeAttributeData(const int attributeNumber, const GLsizeiptr size, const float *data, GLboolean normalize)
{
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attributeNumber);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, normalize, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void ObjModelLoader::bindIndicesBuffer(const GLsizeiptr size, const unsigned int *indices)
{
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void ObjModelLoader::unbindVao()
{
    glBindVertexArray(0);
}

bool ObjModelLoader::loadMtlFile(const char *filename)
{
    /*ファイルを読み込んでObjMaterialに変換しプッシュ*/
    char buf[OBJ_BUFFER_LENGTH] = {0};

    //ファイルを開ける
    file.open(filename, std::fstream::in);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> mtlFile is not found\n");
        return false;
    }

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

    file.close();
    return true;
}
void ObjModelLoader::createMaterial()
{
    char buf[OBJ_BUFFER_LENGTH] = {0};

    char name[MAX_MATERIAL_NAME];
    Touple4f ambient;
    Touple4f diffuse;
    Touple4f specular;
    Touple4f emissive;
    float power = 1.0f;

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
            file.ignore(std::numeric_limits<std::streamsize>::max(), file.widen('\n'));
            file >> buf;
            if (0 == strcmp(buf, "map_Kd"))
            {
                std::string textureName;
                file >> textureName;
                createTexture(textureName);
                break;
            }
            else
                break;
        }
    }
    ret->pushMaterial(ObjMaterial(name, ambient, diffuse, specular, emissive, power));
}

ObjModelLoader::ObjModelLoader()
{
    /*nothing*/
}
ObjRawModel *ObjModelLoader::load(const std::string dirPath, const std::string fileName)
{

    ret = new ObjRawModel();

    this->dirPath = dirPath;
    std::string objFileName = this->dirPath + fileName + ".obj";
    std::string mtlFileName = this->dirPath + fileName + ".mtl";

    if (!loadMtlFile(mtlFileName.c_str()))
    {
        fprintf(stderr, "Error --> loadMtlFile(%s)\n", mtlFileName.c_str());
        return NULL;
    }
    if (!loadObjFile(objFileName.c_str()))
    {
        fprintf(stderr, "Error --> loadObjFile(%s)\n", objFileName.c_str());
        return NULL;
    }

    return ret;
}