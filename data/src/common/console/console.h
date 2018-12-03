#pragma once

#include <fstream>

class Console
{
private:
  bool input(const char *message, const char *defaultValue, char *str);

public:
  bool scanString(const char *message, const char *defaultValue, std::string *str);
};