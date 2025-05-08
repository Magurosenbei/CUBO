#pragma once

#define PI 3.14159265f
#define DEGTORAD(a) (a * PI / 180)
#define RADTODEG(a) (a * 180 / PI)

#define SmartPtr std::auto_ptr

#define APP_TITLE	L"CUBO"
#define APP_CLASS	L"CUBO-152-3EX-7LO3-20PZ"

#ifdef _DEBUG
#define WriteCommandLine System_Utility::CompilerCommandLine
#else
#define WriteCommandLine(a, ...)	{}
#endif

#define ARGB(a,r,g,b)	((DWORD(a)<<24) + (DWORD(r)<<16) + (DWORD(g)<<8) + DWORD(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + DWORD(b))

#define WM_TASKBARCALLBACK	WM_USER+150

#define MULTI_TEXT _bstr_t

#define VECTOR4 D3DXVECTOR4
#define VECTOR3 D3DXVECTOR3
#define VECTOR2 D3DXVECTOR2
#define DXRENDERSTATE _D3DRENDERSTATETYPE
#define DXWORLD D3DTS_WORLD

#define DXTEXTURE LPDIRECT3DTEXTURE9
