#include "MiscUtils.h"

std::vector<std::string> explode(std::string str, std::string delim)
{
	std::vector<std::string> fragments;
	size_t found = 0;
	size_t delim_sz = delim.size();

	while((found = str.find(delim)) != std::string::npos)
	{
		fragments.push_back(str.substr(0, found));
		str = str.substr(found+delim_sz);
	}

	fragments.push_back(str);

	return fragments;
}
