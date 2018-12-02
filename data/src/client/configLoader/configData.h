#include <fstream>
class ConfigData
{

private:

public:
  ConfigData() {}
  ~ConfigData() {}
  std::string name;
  std::string serverAddress;
  std::string wiiRemoteId;
};