#pragma once

#define MAX_DATA_SIZE 256

class DataBlock
{
private:
  char dataBlock[MAX_DATA_SIZE];
  int dataSize;

public:
  DataBlock();
  ~DataBlock();
  operator char *() { return (char *)dataBlock; }
  operator const char *() const { return (const char *)dataBlock; }
  int getDataSize() { return this->dataSize; }
  void setData(void *data, int dataSize);
};