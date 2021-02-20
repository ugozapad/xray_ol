#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#define POINTER_64 __ptr64
// template <typename StringType>
// void strconcat(StringType& OutString, const char* Str1, const char* Str2)
// {
// 	size_t SingleCharSize = sizeof(OutString[0]);
// 	//static_assert(sizeof(OutString[0]) == 1);
// 	if (sizeof(OutString[0]) == 1)
// 	{
// 		__debugbreak();
// 	}
// 
// 	size_t MaxBuffer = sizeof(OutString) / SingleCharSize;
// 
// 	size_t Str1Len = strlen(Str1);
// 	memcpy(OutString, Str1, Str1Len * SingleCharSize);
// 
// 	if (Str2 != nullptr)
// 	{
// 		size_t Str2Len = strlen(Str2);
// 		memcpy(&OutString[Str1Len], Str2, Str2Len * SingleCharSize);
// 	}
// }
// 
// template <typename StringType>
// char* strext(StringType& InOutString)
// {
// 	size_t strLen = sizeof(StringType);
// 
// 	for (size_t i = 0; i < strLen; i++)
// 	{
// 		char ch = InOutString[i];
// 		if (ch == '.')
// 		{
// 			return &InOutString[i];
// 		}
// 		else if (ch == '\0')
// 		{
// 			return nullptr;
// 		}
// 	}
// 
// 	return nullptr;
// }

typedef std::string AnsiString;
typedef std::vector<AnsiString> AStringVec;
typedef AStringVec::iterator AStringIt;

#define WINVER 0x0400