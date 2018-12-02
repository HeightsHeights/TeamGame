#include "./dataBlock.h"
#include <string.h>
#include <unistd.h>
#include <assert.h>
DataBlock::DataBlock()
{
    this->dataSize = 0;
    bzero(this->dataBlock, MAX_DATA_SIZE * sizeof(char));
}
DataBlock::~DataBlock()
{
}
void DataBlock::setData(void *data, int dataSize)
{
    assert(data != NULL);
    assert(0 < dataSize);

    memcpy(this->dataBlock + this->dataSize, data, dataSize);
    this->dataSize += dataSize;
}