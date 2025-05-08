// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma warning(disable : 4127)
#pragma warning(disable : 4201)
#pragma warning(disable : 4189)
#pragma warning(disable : 4482)
#pragma warning(disable : 4100)
#pragma warning(disable : 4244)

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
// C RunTime Header Files
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>
#include <stdexcept>
#include <memory>
#include <xmmintrin.h>  
#include <mmintrin.h>

#include <string>
#include <vector>
#include <map>
#include <deque>

#ifdef _MSC_VER
#ifdef NDEBUG
#define ASSERT(exp, msg)	{}
#define VERIFY(exp, msg)	(exp);
#else // NDEBUG
#define ASSERT(exp, msg)	if( !(exp) ) std::_Debug_message(L#msg, _CRT_WIDE(__FILE__), __LINE__);
#define VERIFY(exp, msg)	if( !(exp) ) std::_Debug_message(L#msg, _CRT_WIDE(__FILE__), __LINE__);
#endif // end NDEBUG
#else // _MSC_VER
#ifdef NDEBUG
#define ASSERT(exp, msg)	{}
#define VERIFY(exp, msg)	(exp);
#else // NDEBUG
#include <cassert>
#define ASSERT(exp, msg)		assert( (exp) );
#define VERIFY(exp, msg)		assert( (exp) );
#endif // end NDEBUG
#endif // end _MSC_VER

#include "Definition/targetver.h"
#include "Resource.h"
#include "Definition/LibaryInclude.h"
#include "Definition/Terms.h"
#include "Definition/AbstractTemplate.h"
#include "Definition/AppInclude.h"
