#include "stdafx.h"
#include "TextureHolder.h"

SmartPtr<TextureHolder> Abstract_Single<TextureHolder>::m_pInstance;

LPDIRECT3DTEXTURE9 TextureHolder::AddTexture(std::string FilePath)
{
	FilePath = System_Utility::LowerCase(FilePath.c_str());
	std::map<std::string, LPDIRECT3DTEXTURE9>::iterator it = m_Textures.find(FilePath);
	if(it != m_Textures.end())
		return it->second;

	LPDIRECT3DTEXTURE9 Texture;
	HRESULT Result = D3DXCreateTextureFromFileA(DxDevice::Instance()->Device(), FilePath.c_str(), &Texture);
	ASSERT(Result == S_OK, "Texture cannot be loaded");
	m_Textures.insert(std::make_pair(FilePath, Texture));
	return Texture;
}

LPDIRECT3DTEXTURE9 TextureHolder::GetTexture(std::string FilePath)
{
	FilePath = System_Utility::LowerCase(FilePath.c_str());
	std::map<std::string, LPDIRECT3DTEXTURE9>::iterator it = m_Textures.find(FilePath);
	if(it != m_Textures.end())
		return it->second;
	return NULL;
}