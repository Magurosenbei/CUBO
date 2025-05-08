#pragma once

class FontText
{
	LPD3DXFONT	m_pFont;
	size_t		m_FontSize;
	RECT		m_RECT;
public:
	FontText();
	virtual ~FontText();


	//	@param FontFile :	Put anything if don't have file
	//	@param FontID	:	ID of the font, check the font file for this
	//	@param FontSize :	12, 16, 24 etc, unfortunately one Font 1 Size
	//	@param WidthHeight : Width and height of text area
	bool	Initialize(	const std::string & FontFile, const std::string & FontId,
						const size_t & FontSize, 
						const size_t & Width, const size_t & Height);

	void	WriteText(const size_t & x, const size_t & y, const std::string & Text, const size_t & Color);
};