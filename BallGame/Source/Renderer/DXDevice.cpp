#include "stdafx.h"
#include "DXDevice.h"

SmartPtr<DxDevice> Abstract_Single<DxDevice>::m_pInstance;

const D3DXVECTOR3	VECTOR3_X(1, 0, 0);
const D3DXVECTOR3	VECTOR3_Y(0, 1, 0);
const D3DXVECTOR3	VECTOR3_Z(0, 0, 1);

const D3DXVECTOR4	VECTOR4_X(1, 0, 0, 1);
const D3DXVECTOR4	VECTOR4_Y(0, 1, 0, 1);
const D3DXVECTOR4	VECTOR4_Z(0, 0, 1, 1);

const D3DXVECTOR4	COLOR_RED(1, 0, 0, 1);
const D3DXVECTOR4	COLOR_BLUE(0, 0, 1, 1);
const D3DXVECTOR4	COLOR_GREEN(0, 1, 0, 1);
const D3DXVECTOR4	COLOR_WHITE(1, 1, 1, 1);
const D3DXVECTOR4	COLOR_BLACK(0, 0, 0, 1);

DxDevice::DxDevice()
:	m_pD3D9(NULL),		m_pDevice(NULL), 
	m_pOverlay(NULL),	m_pSystemText(NULL), m_ScreenOffset(0, 0, 0)
{
}

DxDevice::~DxDevice()
{
}

void	DxDevice::Resize()
{
	Camera::Instance()->Initialize();
}

bool	DxDevice::Initialze(HINSTANCE Instance, HWND	Hwnd)
{
	m_pD3D9 = Direct3DCreate9(DIRECT3D_VERSION);
	ASSERT(m_pD3D9 != NULL, "Failed to create d3d9");

	D3DDISPLAYMODE DisplayMode;
	HRESULT	Result = m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);
	ASSERT(Result == S_OK, "DXDisplay Mode Failed");

	D3DPRESENT_PARAMETERS	PresentParams;
	memset(&PresentParams, 0x00, sizeof(PresentParams));
	PresentParams.BackBufferFormat = DisplayMode.Format;
	PresentParams.EnableAutoDepthStencil = false;
	PresentParams.AutoDepthStencilFormat = D3DFORMAT::D3DFMT_D16;
	PresentParams.Windowed = true;
	PresentParams.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;
	PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	PresentParams.hDeviceWindow = Window::Instance()->GetWindowHandle();

	Result = m_pD3D9->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
									Window::Instance()->GetWindowHandle(), D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&PresentParams, &m_pDevice );

	ASSERT(Result == S_OK, "Device Failed to create");

	Result = m_pDevice->CreateDepthStencilSurface(2048, 2048, D3DFORMAT::D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, true, &m_pZBuffer, NULL);
	ASSERT(Result == S_OK, "Failed to create ZBuffer");
	m_pDevice->SetDepthStencilSurface(m_pZBuffer);

	m_pDevice->SetRenderState(DXRENDERSTATE::D3DRS_ZENABLE, true);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);  
	m_pDevice->SetRenderState(DXRENDERSTATE::D3DRS_CULLMODE, D3DCULL_CW);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	m_pDevice->SetFVF(CUSTOMFVF);

	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP,		D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1,	D3DTA_DIFFUSE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2,	D3DTA_TEXTURE);

	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,	D3DTA_DIFFUSE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2,	D3DTA_TEXTURE);

	m_pDevice->SetSamplerState(0, D3DSAMPLERSTATETYPE::D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMPLERSTATETYPE::D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMPLERSTATETYPE::D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	m_pDevice->GetRenderTarget(0, &m_pBackBuffer);
	m_pDevice->GetViewport(&m_ViewPort);
	D3DXCreateSprite(m_pDevice, &m_pSpriteBatch);

	/*m_ScreenOffset.x = (2048 - m_ViewPort.Width) * -0.5f;
	m_ScreenOffset.y = (2048 - m_ViewPort.Height) * -0.5f;
	m_ScreenOffset.z = 0;*/

	m_RenderTargets.push_back(new RenderTarget(1024,	1024, 0, D3DFORMAT::D3DFMT_A32B32G32R32F));
	//m_RenderTargets.push_back(new RenderTarget(1024,	1024, 0, D3DFORMAT::D3DFMT_A32B32G32R32F));
	//m_RenderTargets.push_back(new RenderTarget(512,		512,  0, D3DFORMAT::D3DFMT_A32B32G32R32F));
	//m_RenderTargets.push_back(new RenderTarget(512,		512,  0, D3DFORMAT::D3DFMT_A32B32G32R32F));

	for(size_t i = 0; i < m_RenderTargets.size(); i++)
		m_RenderTargets[i]->Initialize();

	Window::Instance()->RegisterSubProgram("Camera",	Camera::Instance());
	Camera::Instance()->Initialize();

	m_pSystemText = SmartPtr<FontText>(new FontText);
	m_pSystemText->Initialize("Data/hymmnos.ttf", "Arial", 16, 800, 48);

	Console::Instance()->Initialize();
	return	true;
}

bool	DxDevice::Shutdown()
{
	m_pBackBuffer->Release();
	for(size_t i = 0; i < m_RenderTargets.size(); i++)
	{
		delete m_RenderTargets[i];
		m_RenderTargets[i] = NULL;		
	}
	m_RenderTargets.clear();

	m_pSpriteBatch->Release();

	m_pOverlay.release();

	m_pSystemText.reset(NULL);
	m_pSystemText.release();

	m_pDevice->Release();
	m_pD3D9->Release();
	return	true;
}

void	DxDevice::Render()
{
	for(size_t i = 0; i < m_RenderTargets.size(); i++)
		m_RenderTargets[i]->Render();

	// Set back original back buffer
	m_pDevice->SetRenderTarget(0, m_pBackBuffer);
	m_pDevice->SetViewport(&m_ViewPort);
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , ARGB(255, 0, 0, 0), 1.0f, 0.0f);
	m_pDevice->BeginScene();

	m_pSpriteBatch->Begin(0);
	m_pSpriteBatch->Draw(m_RenderTargets[0]->TEXTURE(), &m_RenderTargets[0]->m_Rectangle, NULL, &m_ScreenOffset, 0xffffffff);
	//m_pSpriteBatch->Draw(m_RenderTargets[1]->TEXTURE(), &m_Rectangle, NULL, &m_ScreenOffset, 0xffffffff);
	m_pSpriteBatch->End();

	if(m_pOverlay.get() != NULL)
		m_pOverlay->Render();

	//m_pSystemText->WriteText(0, 0, System_Utility::FormatText("FPS: %i UPS: %i Interval: %f", Window::Instance()->FPS(), Window::Instance()->UPS(), Window::Instance()->PrevInterval()), 0xffffffff);

	Console::Instance()->Render();
	
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void	DxDevice::RegisterToTarget(const size_t & ID, const std::string & Key, Abstract_Renderable * Address)
{
	m_RenderTargets[ID]->Subscribe(Key, Address);
}

void	DxDevice::UnRegisterToTarget(const size_t & ID, const std::string & Key, Abstract_Renderable * Address)
{
	m_RenderTargets[ID]->UnSubscribe(Key, Address);
}