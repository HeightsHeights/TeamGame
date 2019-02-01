#include "./cObjectData.h"

CObjectData::CObjectData()
{
}

CObjectData::CObjectData(OBJECT_ID id)
{
    this->objectId = id;
}
CObjectData::CObjectData(OBJECT_ID id, Transform *transform)
{
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