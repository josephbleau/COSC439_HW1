#ifndef MISCUTILS_H
#define MISCUTILS_H

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> explode(const std::string& str, const std::string& delim);
std::string implode(const std::vector<std::string>& list, const std::string& delim);

#endif
