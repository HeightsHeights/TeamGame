#pragma once

#include <fstream>

class Console
{
private:
  bool input(char *str);

public:
  bool scanString(const char *message, const char *defaultValue, std::string *str);
};