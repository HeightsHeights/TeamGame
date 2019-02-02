#pragma once

#define MAX_DATA_SIZE 512

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
  void setCommand2DataBlock(int command) { setData(&command, sizeof(int)); }
};