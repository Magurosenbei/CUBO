#include "stdafx.h"
#include "FontText.h"

FontText::FontText()
:	m_pFont(NULL), m_FontSize(12)
{

}

FontText::~FontText()
{
	m_pFont->Release();
}

bool FontText::Initialize(	const std::string &FontFile, const std::string & FontId,
							const size_t &FontSize, 
							const size_t &Width, const size_t &Height)
{
	m_FontSize = FontSize;
	m_RECT.right = Width;
	m_RECT.bottom = Height;

	size_t Found = AddFontResourceExA(FontFile.c_str(), FR_PRIVATE, 0);
	//ASSERT(Found != 0, "Error finding font");

	HRESULT Result = D3DXCreateFontA(	DxDevice::Instance()->Device(), FontSize, 0, FW_NORMAL, 0, FALSE, 
										DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
										FontId.c_str(), &m_pFont );
	ASSERT(Result == S_OK, "unable to create font");

	return (Result == S_OK);
}

void	FontText::WriteText(const size_t & x, const size_t & y, const std::string & Text, const size_t & Color)
{
	m_RECT.left = x;
	m_RECT.top = y;
	m_pFont->DrawTextA(NULL, Text.c_str(), -1, &m_RECT, 0, Color);
}