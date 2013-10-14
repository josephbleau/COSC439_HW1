#include "MiscUtils.h"

std::vector<std::string> explode(const std::string& str, const std::string& delim)
{
	std::vector<std::string> fragments;
	std::string s(str);
	size_t found = 0;
	size_t delim_sz = delim.size();

	while((found = s.find(delim)) != std::string::npos)
	{
		fragments.push_back(s.substr(0, found));
		s = s.substr(found+delim_sz);
	}

	fragments.push_back(s);

	return fragments;
}

std::string implode(const std::vector<std::string>& list, const std::string& delim)
{
	std::string ret;
	for( const std::string& s : list )
	{
		ret += s;
		ret += delim;
	} 

	ret.erase( ret.end() - delim.size(), ret.end() );
	return ret;
}
