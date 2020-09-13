#include "pch.h"
#include <string>

void strReplace(std::wstring &s, const std::wstring &search, const std::wstring &replace)
{
	for (size_t pos = 0; ; pos += replace.length())
	{
		pos = s.find(search, pos);
		if (pos == std::wstring::npos)
			break;
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

#pragma warning (disable : 6386)
char* readNullTerminatedCharArray(char* src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		i++;
	}

	void* buffer = malloc(++i);
	if (!buffer || buffer == 0) return 0;
	memcpy(buffer, src, i);
	return (char *)buffer;
}
