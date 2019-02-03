#include "./cObjectData.h"

CObjectData::CObjectData()
{
    this->exist = false;
}

CObjectData::CObjectData(OBJECT_ID id, bool exist)
{
    this->exist = exist;
    this->objectId = id;
}
CObjectData::CObjectData(OBJECT_ID id, bool exist, Transform *transform)
{
    this->exist = exist;
    this->objectId = id;

    if (transform == NULL)
    {
        this->transform = Transform();
    }
    else
    {
        this->transform = *transform;
    }
}