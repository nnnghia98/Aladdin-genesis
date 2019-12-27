#include "Graphics.h"


Graphics* Graphics::_instance = NULL;
//=============================================================================
// Constructor
//=============================================================================
Graphics::Graphics()
{
	d3d = NULL;
	d3ddev = NULL;
	spriteHandler = NULL;
	fullscreen = false;
	width = GAME_WIDTH;    // width & height are replaced in initialize()
	height = GAME_HEIGHT;
	backColor = graphicsNS::BACK_COLOR;
}

//=============================================================================
// Destructor
//=============================================================================
Graphics::~Graphics()
{
	releaseAll();
}

//=============================================================================
// Get instance
//=============================================================================
Graphics* Graphics::getInstance()
{
	if (!_instance) _instance = new Graphics();
	return _instance;
}

//=============================================================================
// Release all
//=============================================================================
void Graphics::releaseAll()
{
	safeRelease(spriteHandler);
	safeRelease(d3d);
	safeRelease(d3ddev);
	safeDelete(_instance);
}

//=============================================================================
// Initialize DirectX graphics
//=============================================================================
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		DebugOut("Error initializing Direct3D.\n");
		return;
	}

	initD3Dpp();        // init D3D presentation parameters

	if (fullscreen)      // if full-screen mode
	{
		if (isAdapterCompatible())   // is the adapter compatible
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate; // set the refresh rate with a compatible one
		else DebugOut("The graphics device does not support the specified resolution and/or format.\n");
	}

	// determine if graphics card supports harware texturing and lighting and vertex shaders
	D3DCAPS9 caps;
	DWORD behavior;

	result = d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	// If device doesn't support HW T&L or doesn't support 1.1 vertex 
	// shaders in hardware, then switch to software vertex processing.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  // use software only processing
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;  // use hardware only processing

	//create Direct3D device
	result = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&d3dpp,
		&d3ddev);

	if (FAILED(result))
	{
		DebugOut("[ERROR] CreateDevice failed\n");
		return;
	}

	result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (FAILED(result))
	{
		DebugOut("[ERROR] Error creating Direct3D sprite\n");
		return;
	}

	// Configure for alpha blend of primitives
	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DebugOut("[INFO] InitGame done;\n");
}

//=============================================================================
// Initialize D3D presentation parameters
//=============================================================================
void Graphics::initD3Dpp()
{
	ZeroMemory(&d3dpp, sizeof(d3dpp));              // fill the structure with 0
	// fill in the parameters we need
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	if (fullscreen)                                  // if fullscreen
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24 bit color
	else
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   // use desktop setting
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = (!fullscreen);
	//if (VSYNC)   // if vertical sync is enabled
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	//else
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;    // Depth 24, Stencil 8
}

//=============================================================================
// Load the texture into default D3D memory (normal texture use)
// For internal engine use only. Use the TextureManager class to load game textures.
// Pre: filename is name of texture file.
//      transcolor is transparent color
// Post: width and height = size of texture
//       texture points to texture
// Returns HRESULT
//=============================================================================
HRESULT Graphics::loadTexture(const char* filename, COLOR_ARGB transcolor,
	UINT& width, UINT& height, LPDIRECT3DTEXTURE9& texture)
{
	// The struct for reading file info
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	if (filename == NULL)
	{
		texture = NULL;
		return D3DERR_INVALIDCALL;
	}

	// Get width and height from file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return result;
	width = info.Width;
	height = info.Height;

	// Create the new texture by loading from file
	result = D3DXCreateTextureFromFileEx(
		d3ddev,           //3D device
		filename,           //image filename
		info.Width,         //texture width
		info.Height,        //texture height
		1,                  //mip-map levels (1 for no chain)
		0,                  //usage
		D3DFMT_UNKNOWN,     //surface format (default)
		D3DPOOL_DEFAULT,    //memory class for the texture
		D3DX_DEFAULT,       //image filter
		D3DX_DEFAULT,       //mip filter
		transcolor,         //color key for transparency
		&info,              //bitmap file info (from loaded file)
		NULL,               //color palette
		&texture);         //destination texture

	if (FAILED(result))
		DebugOut("[ERROR] Error in Graphics::loadTexture\n");

	return result;
}

//=============================================================================
// Load the texture into system memory (system memory is lockable)
// Provides direct access to pixel data. Use the TextureManager class to load
// textures for display.
// Pre: filename is name of texture file.
//      transcolor transparent color
// Post: width and height = size of texture
//       texture points to texture
// Returns HRESULT and fills TextureData structure.
//=============================================================================
HRESULT Graphics::loadTextureSystemMem(const char* filename, COLOR_ARGB transcolor,
	UINT& width, UINT& height, LPDIRECT3DTEXTURE9& texture)
{
	// The struct for reading bitmap file info
	D3DXIMAGE_INFO info;
	result = E_FAIL;        // Standard Windows return value

	if (filename == NULL)
	{
		texture = NULL;
		return D3DERR_INVALIDCALL;
	}

	// Get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return result;
	width = info.Width;
	height = info.Height;

	// Create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx(
		d3ddev,           //3D device
		filename,           //bitmap filename
		info.Width,         //bitmap image width
		info.Height,        //bitmap image height
		1,                  //mip-map levels (1 for no chain)
		0,                  //usage
		D3DFMT_UNKNOWN,     //surface format (default)
		D3DPOOL_SYSTEMMEM,  //systemmem is lockable
		D3DX_DEFAULT,       //image filter
		D3DX_DEFAULT,       //mip filter
		transcolor,         //color key for transparency
		&info,              //bitmap file info (from loaded file)
		NULL,               //color palette
		&texture);         //destination texture

	if (FAILED(result))
		DebugOut("[ERROR] Error in Graphics::loadTexture.\n");

	return result;
}

//=============================================================================
// Display the backbuffer
//=============================================================================
HRESULT Graphics::showBackbuffer()
{
	result = E_FAIL;    // default to fail, replace on success
	// Display backbuffer to screen
	result = d3ddev->Present(NULL, NULL, NULL, NULL);
	return result;
}

//=============================================================================
// Checks the adapter to see if it is compatible with the BackBuffer height,
// width and refresh rate specified in d3dpp. Fills in the pMode structure with
// the format of the compatible mode, if found.
// Pre: d3dpp is initialized.
// Post: Returns true if compatible mode found and pMode structure is filled.
//       Returns false if no compatible mode found.
//=============================================================================
bool Graphics::isAdapterCompatible()
{
	UINT modes = d3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,
		d3dpp.BackBufferFormat);
	for (UINT i = 0; i < modes; i++)
	{
		result = d3d->EnumAdapterModes(D3DADAPTER_DEFAULT,
			d3dpp.BackBufferFormat,
			i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&
			pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	return false;
}

//=============================================================================
// Draw the sprite described in SpriteData structure
// Color is optional, it is applied like a filter, WHITE is default (no change)
// Pre : sprite->Begin() is called
// Post: sprite->End() is called
// spriteData.rect defines the portion of spriteData.texture to draw
//   spriteData.rect.right must be right edge + 1
//   spriteData.rect.bottom must be bottom edge + 1
//=============================================================================
void Graphics::drawSprite(const SpriteData& spriteData, COLOR_ARGB color)
{
	if (spriteData.texture == NULL)      // if no texture
		return;

	// Find center of sprite
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(spriteData.width / 2 * spriteData.scale),
		(float)(spriteData.height / 2 * spriteData.scale));
	// Screen position of the sprite
	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.xViewport, (float)spriteData.yViewport);
	// Scaling X,Y
	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);
	if (spriteData.flipHorizontal)  // if flip horizontal
	{
		scaling.x *= -1;            // negative X scale to flip
		// Get center of flipped image.
		spriteCenter.x -= (float)(spriteData.width * spriteData.scale);
		// Flip occurs around left edge, translate right to put
		// Flipped image in same location as original.
		translate.x += (float)(spriteData.width * spriteData.scale);
	}
	if (spriteData.flipVertical)    // if flip vertical
	{
		scaling.y *= -1;            // negative Y scale to flip
		// Get center of flipped image
		spriteCenter.y -= (float)(spriteData.height * spriteData.scale);
		// Flip occurs around top edge, translate down to put
		// Flipped image in same location as original.
		translate.y += (float)(spriteData.height * spriteData.scale);
	}
	//Create a matrix to rotate, scale and position our sprite
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,                // the matrix
		NULL,                   // keep origin at top left when scaling
		0.0f,                   // no scaling rotation
		&scaling,               // scale amount
		&spriteCenter,          // rotation center
		(float)(spriteData.angle),  // rotation angle
		&translate);            // X,Y location

	// Tell the sprite about the matrix "Hello Neo"
	spriteHandler->SetTransform(&matrix);

	// Draw the sprite
	spriteHandler->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);
}

void Graphics::drawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, COLOR_ARGB color_filter)
{
	if (texture == NULL)      // if no texture
		return;

	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	// Screen position of the sprite
	D3DXVECTOR2 translate = D3DXVECTOR2((float)x, (float)y);

	//Create a matrix to rotate, scale and position our sprite
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,                // the matrix
		NULL,                   // keep origin at top left when scaling
		0.0f,                   // no scaling rotation
		NULL,               // scale amount
		NULL,          // rotation center
		0.0f,  // rotation angle
		&translate);            // X,Y location

	// Tell the sprite about the matrix "Hello Neo"
	spriteHandler->SetTransform(&matrix);

	// Draw the sprite
	spriteHandler->Draw(texture, &r, NULL, NULL, color_filter);
}

//=============================================================================
// Test for lost device
//=============================================================================
HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;    // default to fail, replace on success
	if (d3ddev == NULL)
		return  result;
	result = d3ddev->TestCooperativeLevel();
	return result;
}

//=============================================================================
// Reset the graphics device
//=============================================================================
HRESULT Graphics::reset()
{
	initD3Dpp();                        // init D3D presentation parameters
	spriteHandler->OnLostDevice();
	result = d3ddev->Reset(&d3dpp);   // attempt to reset graphics device

	// Configure for alpha blend of primitives
	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	spriteHandler->OnResetDevice();
	return result;
}

//=============================================================================
// Toggle window or fullscreen mode
// Pre: All user created D3DPOOL_DEFAULT surfaces are freed.
// Post: All user surfaces are recreated.
//=============================================================================
void Graphics::changeDisplayMode(graphicsNS::DISPLAY_MODE mode)
{
	try {
		switch (mode)
		{
		case graphicsNS::FULLSCREEN:
			if (fullscreen)      // if already in fullscreen mode
				return;
			fullscreen = true; break;
		case graphicsNS::WINDOW:
			if (fullscreen == false) // if already in window mode
				return;
			fullscreen = false; break;
		default:        // default to toggle window/fullscreen
			fullscreen = !fullscreen;
		}
		reset();
		if (fullscreen)  // fullscreen
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
		}
		else            // windowed
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

			// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);   // get size of client area of window
			MoveWindow(hwnd,
				GAME_POSX,                                           // Left
				GAME_POSY,                                           // Top
				2*GAME_WIDTH /*+ (GAME_WIDTH - clientRect.right)*/,    // Right
				2*GAME_HEIGHT + 80 /*+ (GAME_HEIGHT - clientRect.bottom)*/, // Bottom
				TRUE);                                       // Repaint the window
		}

	}
	catch (...)
	{
		// An error occured, try windowed mode 
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);   // get size of client area of window
		MoveWindow(hwnd,
			GAME_POSX,                                           // Left
			GAME_POSY,                                           // Top
			2*GAME_WIDTH /*+ (GAME_WIDTH - clientRect.right)*/,    // Right
			2*GAME_HEIGHT + 80 /*+ (GAME_HEIGHT - clientRect.bottom)*/, // Bottom
			TRUE);                                       // Repaint the window
	}
}