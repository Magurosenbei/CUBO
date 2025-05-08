#pragma once

class TextureHolder	: public Abstract_Single<TextureHolder>
{
	friend class Abstract_Single<TextureHolder>;
protected:
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_Textures;
public:
	//	Adds a texture of the specified path, if doesn't exist it will add to the lsit
	LPDIRECT3DTEXTURE9	AddTexture(std::string FilePath);
	//	Finds a texture of specified path, if doesn't exist return NULL
	LPDIRECT3DTEXTURE9	GetTexture(std::string FilePath);

	//	Unload all Resources
	void				Clear();
};