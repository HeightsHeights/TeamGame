#include "../../header/render/objRawModel.h"

#include <fstream>
#include <string.h>
#define OBJ_NAME_LENGTH 128
#define OBJ_BUFFER_LENGTH 128
/******************************************************************************
 * ObjSubset
******************************************************************************/
ObjSubset::ObjSubset()
{
    /*nothing*/
}
ObjSubset::ObjSubset(GLuint vao, unsigned int vertexCount, unsigned int materialId)
{
    this->vao = vao;
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
/******************************************************************************
 * ObjRawModel
******************************************************************************/
ObjRawModel::ObjRawModel()
{
    /*nothing*/
}
void ObjRawModel::pushMesh(const ObjSubset subset)
{
    subsets.push_back(subset);
}
void ObjRawModel::pushMaterial(const ObjMaterial material)
{
    materials.push_back(material);
}
void ObjRawModel::draw()
{
    for (int i = 0; i < subsets.size(); i++)
    {
        /*サブセットからデータ読み込み*/
        GLuint vao = subsets[i].getVao();
        unsigned int vCount = subsets[i].getVertexCount();
        unsigned int mId = subsets[i].getMaterialId();

        /*色つけ*/
        materials[mId].applyMaterial();

        /*サブセットの描画*/
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, vCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}