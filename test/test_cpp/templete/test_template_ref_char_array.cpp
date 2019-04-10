#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include <memory>
#include <cstring>
template<uint32_t Size>
inline void CopyToArray(const std::string & from,char (&to)[Size])
{
	uint32_t min = std::min(from.size(),Size);
	std::memcpy(to,from.c_str(),min);
	if(min < Size)
	{
		std::memset(&to[min],' ',Size-min);
	}
}

int main()
{
	std::string str("1234556789");
	char b[12];
	CopyToArray(str,b);
	for(int i=0;i<12;++i)
	{
		printf("%c",b[i]);
	}	
	return 0;
}
