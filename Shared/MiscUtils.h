#ifndef MISCUTILS_H
#define MISCUTILS_H

#include <iostream>
#include <string>
#include <vector>

/* Creates a vector of strings based on a delimited string. Inverse of implode. */
std::vector<std::string> explode(const std::string& str, const std::string& delim);

/* Creates a delimited string based on a vector of strings. Inverse of explode. */
std::string implode(const std::vector<std::string>& list, const std::string& delim);

#endif
