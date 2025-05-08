#include "stdafx.h"
#include "Utility.h"

LARGE_INTEGER	System_Utility::Time_Start;
LARGE_INTEGER	System_Utility::Time_End;
LARGE_INTEGER	System_Utility::Time_Frequency;

void System_Utility :: CompilerCommandLine(std::string Message, ...)
{
	char    Buffer[2048], * p = Buffer;
	va_list args;
	int     n;
	va_start(args, Message);
	n = _vsnprintf_s(p, sizeof Buffer - 3, 2047, Message.c_str(), args);
	p += (n < 0) ? sizeof Buffer - 3 : n;
    while ( p > Buffer  &&  isspace(p[-1]) )
            *--p = '\0';

    *p++ = '\r';
    *p++ = '\n';
    *p   = '\0';

	OutputDebugStringA(Buffer);
}

std :: wstring System_Utility :: ConvertToWideText(const std::string &Text)
{
	MULTI_TEXT	Convert(Text.c_str());
	return std::wstring(Convert);
}

std :: string System_Utility :: ConvertToASCIText(const std::wstring &Text)
{
	MULTI_TEXT Convert(Text.c_str());
	return std::string(Convert);
}

std::string	System_Utility :: LowerCase(const std :: string & Text)
{
	std::string mText = Text;
	size_t size = Text.size();
	// Change all uppercase letters to lowercase
	for(size_t i = 0; i < size; ++i)
	{
		if(mText[i] >= 'A' && mText[i] <= 'Z')
			mText[i] += ('a' - 'A');
	}
	return mText;
}

std::string	System_Utility :: UpperCase(const std :: string & Text)
{
	std::string mText = Text;
	size_t size = Text.size();
	// Change all uppercase letters to Upper
	for(size_t i = 0; i < size; ++i)
	{
		if(mText[i] >= 'a' && mText[i] <= 'z')
			mText[i] += ('A' - 'a');
	}
	return mText;
}

std::string	System_Utility :: FormatText(std::string Format, ...)
{
	char    Buffer[2048], * p = Buffer;
	va_list args;
	int     n;
	va_start(args, Format);
	n = _vsnprintf_s(p, sizeof Buffer - 3, 2047, Format.c_str(), args);
	p += (n < 0) ? sizeof Buffer - 3 : n;
    while ( p > Buffer  &&  isspace(p[-1]) )
            *--p = '\0';

    *p++ = '\r';
    //*p++ = '\n';	// No end Line
    *p   = '\0';
	std::string Return = Buffer;
	return Return.substr(0, Return.length() - 1);
}


float System_Utility :: RandomFloat(float Min, float Max)
{
	if(Min > Max)
		std::swap(Min,Max);
	return (rand() / (static_cast<float>(RAND_MAX) + 1.0f)) * (Max - Min) + Min;
}

double System_Utility :: RandomDouble(double Min, double Max)
{
	if(Min > Max)
		std::swap(Min,Max);
	return (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (Max - Min) + Min;
}

void	System_Utility :: Start()
{	
	Time_End.QuadPart = Time_Start.QuadPart = 0;
	QueryPerformanceFrequency(&Time_Frequency);
	QueryPerformanceCounter(&Time_Start);
}

float	System_Utility :: End()
{
	QueryPerformanceCounter(&Time_End);
	return float(Time_End.QuadPart - Time_Start.QuadPart) * 1000.0f / float(Time_Frequency.QuadPart);
	//return (Time_End.QuadPart * (1000000.0f / Time_Frequency.QuadPart)) - (Time_Start.QuadPart * (1000000.0f / Time_Frequency.QuadPart));
}

System_HiResTimer::System_HiResTimer()
{
	Time_Frequency.QuadPart = 0;
}

void System_HiResTimer :: Start()
{
	Time_End.QuadPart = Time_Start.QuadPart = 0;
	QueryPerformanceFrequency(&Time_Frequency);
	QueryPerformanceCounter(&Time_Start);
	bisActive = true;
}

float System_HiResTimer :: End()
{
	bisActive = false;
	QueryPerformanceCounter(&Time_End);
	
	return float(Time_End.QuadPart - Time_Start.QuadPart) * 1000.0f / float(Time_Frequency.QuadPart);
	//return (Time_End.QuadPart * (1000000.0f / Time_Frequency.QuadPart)) - (Time_Start.QuadPart * (1000000.0f / Time_Frequency.QuadPart));
}