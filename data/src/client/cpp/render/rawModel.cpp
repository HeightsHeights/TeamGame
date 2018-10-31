//モデルデータ保存
//
#include "./header/rawmodel.h"
#include <fstream>
#include <string.h>
#define OBJ_NAME_LENGTH 128
#define OBJ_BUFFER_LENGTH 128
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RawModel::RawModel()
{
    this->vertexArrayObject = 0;
    this->vertexCount = 0;
}
RawModel::RawModel(GLuint vao, unsigned int vertexCount)
{
    this->vertexArrayObject = vao;
    this->vertexCount = vertexCount;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// マテリアル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// オブジェファイル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ModelLoader::loadOBJFile(const char *filename)
{
    std::ifstream file;
    char buf[OBJ_BUFFER_LENGTH] = {0};

    std::vector<Vector3f> vertices;
    std::vector<Vector2f> textures;
    std::vector<Vector3f> normals;
    std::vector<unsigned int> indices;

    std::vector<unsigned int> normalIndex;
    std::vector<Vector3f> normalArray;

    //ファイルを開ける
    file.open(filename, std::fstream::in);
    if (!file.is_open())
    {
        printf("error file_open\n");
        return false;
    }

    while (1)
    {
        //読み込み
        file >> buf;

        //閉じる
        if (!file)
        {
            break;
        }
        if (0 == strcmp(buf, "#"))
        {
            //コメント
        }

        //頂点情報
        else if (0 == strcmp(buf, "v"))
        {
            //頂点座標
            float x, y, z;
            file >> x >> y >> z;
            Vector3f v(x, y, z);
            vertices.push_back(v);
        }
        else if (0 == strcmp(buf, "vt"))
        {
            //テクスチャ座標
            float u, v;
            file >> u >> v;
            textures.push_back(Vector2f(u, v));
        }
        else if (0 == strcmp(buf, "vn"))
        {
            //法線ベクトル
            float x, y, z;
            file >> x >> y >> z;
            normals.push_back(Vector3f(x, y, z));
        }

        //インデックス情報
        else if (0 == strcmp(buf, "f"))
        {
            unsigned int iVertex, iTexCoord, iNormal;

            for (int iFace = 0; iFace < 3; iFace++)
            {
                file >> iVertex;
                indices.push_back(iVertex - 1);
                if ('/' == file.peek())
                {
                    file.ignore();

                    //テクスチャ情報があれば追加
                    if ('/' != file.peek())
                    {
                        file >> iTexCoord;
                        //T_INDICES.push_back(iTexCoord - 1);
                    }

                    if ('/' == file.peek())
                    {
                        file.ignore();
                        file >> iNormal;
                        normalIndex.push_back(iNormal - 1);
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
    Vector3f normalsArraySum[vertices.size()];
    for (unsigned int i = 0 ; i < vertices.size(); i++){
        normalsArraySum[i] = Vector3f_ZERO;
    }
    for (unsigned int i = 0 ; i < indices.size(); i++){
        normalsArraySum[indices[i] ]= normalsArraySum[indices[i]] + normals[normalIndex[i]];
    }
    for (unsigned int i = 0 ; i < vertices.size(); i++){
        normalsArraySum[i] = normalsArraySum[i ].normalize();
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3f), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalBufferObject;
    glGenBuffers(1, &normalBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(Vector3f), &normalsArraySum[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    vertexCount = vertices.size();

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// オブジェファイル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RawModel ModelLoader::loadFile(const char *filename)
{
    if (!loadOBJFile(filename))
    {
        printf("error read file\n");
        return *new RawModel(0, 0);
    }

    return *new RawModel(vao, vertexCount);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 描画
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RawModel::drawModel()
{
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLE_STRIP, vertexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
