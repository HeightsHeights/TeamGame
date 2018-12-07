#include "./objRawModel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
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
ObjMaterial::ObjMaterial(char *name, Touple4f ambient, Touple4f diffuse, Touple4f specular, Touple4f emissive, float power, GLuint texId)
{
    strcpy(this->name, name);
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->emissive = emissive;
    this->power = power;
    this->texId = texId;
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
void ObjMaterial::applyTexture()
{
    glBindTexture(GL_TEXTURE_2D, texId);
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
        unsigned int vCount = subsets[i].getVertexCount();
        unsigned int mId = subsets[i].getMaterialId();

        /*色つけ*/
        materials[mId].applyMaterial();
        materials[mId].applyTexture();
        /*サブセットの描画*/
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, vCount, GL_UNSIGNED_INT, BUFFER_OFFSET(bIndex * sizeof(unsigned int)));
        bIndex += vCount;
        glBindVertexArray(0);
    }
}