///////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       d3dx10core.h
//  Content:    D3DX10 core types and functions
//
///////////////////////////////////////////////////////////////////////////

#include "d3dx10.h"

#ifndef __D3DX10CORE_H__
#define __D3DX10CORE_H__

// Current name of the DLL shipped in the same SDK as this header.
#define D3DX10_DLL_W L"d3dx10.dll"
#define D3DX10_DLL_A "d3dx10.dll"

#ifdef UNICODE
    #define D3DX10_DLL D3DX10_DLL_W 
#else
    #define D3DX10_DLL D3DX10_DLL_A
#endif

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////
// D3DX10_SDK_VERSION:
// -----------------
// This identifier is passed to D3DX10CheckVersion in order to ensure that an
// application was built against the correct header files and lib files. 
// This number is incremented whenever a header (or other) change would 
// require applications to be rebuilt. If the version doesn't match, 
// D3DX10CreateVersion will return FALSE. (The number itself has no meaning.)
///////////////////////////////////////////////////////////////////////////

#define D3DX10_VERSION 0x1002
#define D3DX10_SDK_VERSION 1000

HRESULT WINAPI D3DX10CheckVersion(UINT D3DSdkVersion, UINT D3DX10SdkVersion);
UINT WINAPI D3DX10GetDriverLevel(ID3D10Device *pDevice);

#ifdef __cplusplus
}
#endif //__cplusplus

//////////////////////////////////////////////////////////////////////////////
// D3DX10SPRITE flags:
// -----------------
// D3DX10SPRITE_DONOTSAVESTATE
//   Specifies device state is not to be saved and restored in Begin/End.
// D3DX10SPRITE_DONOTMODIFY_RENDERSTATE
//   Specifies device render state is not to be changed in Begin.  The device
//   is assumed to be in a valid state to draw vertices containing POSITION0, 
//   TEXCOORD0, and COLOR0 data.
// D3DX10SPRITE_OBJECTSPACE
//   The WORLD, VIEW, and PROJECTION transforms are NOT modified.  The 
//   transforms currently set to the device are used to transform the sprites 
//   when the batch is drawn (at Flush or End).  If this is not specified, 
//   WORLD, VIEW, and PROJECTION transforms are modified so that sprites are 
//   drawn in screenspace coordinates.
// D3DX10SPRITE_BILLBOARD
//   Rotates each sprite about its center so that it is facing the viewer.
// D3DX10SPRITE_BLEND
//   Enables BLEND(SRCALPHA, INVSRCALPHA) and ALPHATEST(alpha > 0).
//   ID3DX10Font expects this to be set when drawing text.
// D3DX10SPRITE_SORT_TEXTURE
//   Sprites are sorted by texture prior to drawing.  This is recommended when
//   drawing non-overlapping sprites of uniform depth.  For example, drawing
//   screen-aligned text with ID3DX10Font.
// D3DX10SPRITE_SORT_DEPTH_FRONTTOBACK
//   Sprites are sorted by depth front-to-back prior to drawing.  This is 
//   recommended when drawing opaque sprites of varying depths.
// D3DX10SPRITE_SORT_DEPTH_BACKTOFRONT
//   Sprites are sorted by depth back-to-front prior to drawing.  This is 
//   recommended when drawing transparent sprites of varying depths.
//////////////////////////////////////////////////////////////////////////////

typedef enum D3DX10SPRITE_FLAG
{
    D3DX10SPRITE_DONOTSAVESTATE              =    (1 << 0),
    D3DX10SPRITE_DONOTMODIFY_RENDERSTATE     =    (1 << 1),
    D3DX10SPRITE_OBJECTSPACE                 =    (1 << 2),
    D3DX10SPRITE_BILLBOARD                   =    (1 << 3),
    D3DX10SPRITE_BLEND                       =    (1 << 4),
    D3DX10SPRITE_SORT_TEXTURE                =    (1 << 5),
    D3DX10SPRITE_SORT_DEPTH_FRONTTOBACK      =    (1 << 6),
    D3DX10SPRITE_SORT_DEPTH_BACKTOFRONT      =    (1 << 7),
} D3DX10SPRITE_FLAG;


//////////////////////////////////////////////////////////////////////////////
// ID3DX10Sprite:
// ------------
// This object intends to provide an easy way to drawing sprites using D3D.
//
// Begin - 
//    Prepares device for drawing sprites.
//
// Draw -
//    Draws a sprite.  Before transformation, the sprite is the size of 
//    SrcRect, with its top-left corner specified by Position.  The color 
//    and alpha channels are modulated by Color. Center is used to determine
//    the point of rotation of the sprite in texels from its upper left (NULL
//    means to use 0,0 which is the upper left).
//
// Flush -
//    Forces all batched sprites to submitted to the device.
//
// End - 
//    Restores device state to how it was when Begin was called.
//
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3DX10Sprite ID3DX10Sprite;
typedef interface ID3DX10Sprite *LPD3DX10SPRITE;


// {BA0B762D-7D28-43ec-B9DC-2F84443B0614}
DEFINE_GUID(IID_ID3DX10Sprite, 
0xba0b762d, 0x7d28, 0x43ec, 0xb9, 0xdc, 0x2f, 0x84, 0x44, 0x3b, 0x6, 0x14);


#undef INTERFACE
#define INTERFACE ID3DX10Sprite

DECLARE_INTERFACE_(ID3DX10Sprite, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DX10Sprite
    STDMETHOD(GetDevice)(THIS_ ID3D10Device** ppDevice) PURE;

    STDMETHOD(GetTransform)(THIS_ D3DXMATRIX *pTransform) PURE;
    STDMETHOD(SetTransform)(THIS_ CONST D3DXMATRIX *pTransform) PURE;
    
    STDMETHOD(SetWorldViewRH)(THIS_ CONST D3DXMATRIX *pWorld, CONST D3DXMATRIX *pView) PURE;
    STDMETHOD(SetWorldViewLH)(THIS_ CONST D3DXMATRIX *pWorld, CONST D3DXMATRIX *pView) PURE;
    
    STDMETHOD(GetProjection)(THIS_ D3DXMATRIX *pProjection) PURE;
    STDMETHOD(SetProjection)(THIS_ CONST D3DXMATRIX *pProjection) PURE;

    STDMETHOD(Begin)(THIS_ UINT Flags) PURE;
    STDMETHOD(Draw)(THIS_ ID3D10ShaderResourceView* pTexture, CONST RECT *pSrcRect, CONST D3DXVECTOR3 *pCenter, CONST D3DXVECTOR3 *pPosition, D3DXCOLOR Color) PURE;
    STDMETHOD(Flush)(THIS) PURE;
    STDMETHOD(End)(THIS) PURE;
};


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

HRESULT WINAPI 
    D3DX10CreateSprite( 
        ID3D10Device*         pDevice, 
        LPD3DX10SPRITE*       ppSprite);

#ifdef __cplusplus
}
#endif //__cplusplus


//////////////////////////////////////////////////////////////////////////////
// ID3DX10ThreadPump:
//////////////////////////////////////////////////////////////////////////////

#undef INTERFACE
#define INTERFACE ID3DX10DataLoader

DECLARE_INTERFACE(ID3DX10DataLoader)
{
	STDMETHOD(Load)(THIS) PURE;
	STDMETHOD(Decompress)(THIS_ void **ppData, SIZE_T *pcBytes) PURE;
	STDMETHOD(Destroy)(THIS) PURE;
};

#undef INTERFACE
#define INTERFACE ID3DX10DataProcessor

DECLARE_INTERFACE(ID3DX10DataProcessor)
{
	STDMETHOD(Process)(THIS_ void *pData, SIZE_T cBytes) PURE;
	STDMETHOD(CreateDeviceObject)(THIS_ void **ppDataObject) PURE;
	STDMETHOD(Destroy)(THIS) PURE;
};

// {C93FECFA-6967-478a-ABBC-402D90621FCB}
DEFINE_GUID(IID_ID3DX10ThreadPump, 
0xc93fecfa, 0x6967, 0x478a, 0xab, 0xbc, 0x40, 0x2d, 0x90, 0x62, 0x1f, 0xcb);

#undef INTERFACE
#define INTERFACE ID3DX10ThreadPump

DECLARE_INTERFACE_(ID3DX10ThreadPump, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DX10ThreadPump
    STDMETHOD(AddWorkItem)(THIS_ ID3DX10DataLoader *pDataLoader, ID3DX10DataProcessor *pDataProcessor, HRESULT *pHResult, void **ppDeviceObject) PURE;
    STDMETHOD_(UINT, GetWorkItemCount)(THIS) PURE;

    STDMETHOD(WaitForAllItems)(THIS) PURE;
    STDMETHOD(ProcessDeviceObjectCreation)(THIS_ UINT iWorkItemCount);

    STDMETHOD(PurgeAllItems)(THIS) PURE;
    STDMETHOD(GetQueueStatus)(THIS_ UINT *pIoQueue, UINT *pProcessQueue, UINT *pDeviceQueue) PURE;
    
};

HRESULT WINAPI D3DX10CreateThreadPump(ID3DX10ThreadPump **ppThreadPump, UINT cIoThreads, UINT cProcThreads, UINT cDeviceThreads);


//////////////////////////////////////////////////////////////////////////////
// ID3DX10Font:
// ----------
// Font objects contain the textures and resources needed to render a specific 
// font on a specific device.
//
// GetGlyphData -
//    Returns glyph cache data, for a given glyph.
//
// PreloadCharacters/PreloadGlyphs/PreloadText -
//    Preloads glyphs into the glyph cache textures.
//
// DrawText -
//    Draws formatted text on a D3D device.  Some parameters are 
//    surprisingly similar to those of GDI's DrawText function.  See GDI 
//    documentation for a detailed description of these parameters.
//    If pSprite is NULL, an internal sprite object will be used.
//
//////////////////////////////////////////////////////////////////////////////

typedef struct _D3DX10FONT_DESCA
{
    INT Height;
    UINT Width;
    UINT Weight;
    UINT MipLevels;
    BOOL Italic;
    BYTE CharSet;
    BYTE OutputPrecision;
    BYTE Quality;
    BYTE PitchAndFamily;
    CHAR FaceName[LF_FACESIZE];

} D3DX10FONT_DESCA, *LPD3DX10FONT_DESCA;

typedef struct _D3DX10FONT_DESCW
{
    INT Height;
    UINT Width;
    UINT Weight;
    UINT MipLevels;
    BOOL Italic;
    BYTE CharSet;
    BYTE OutputPrecision;
    BYTE Quality;
    BYTE PitchAndFamily;
    WCHAR FaceName[LF_FACESIZE];

} D3DX10FONT_DESCW, *LPD3DX10FONT_DESCW;

#ifdef UNICODE
typedef D3DX10FONT_DESCW D3DX10FONT_DESC;
typedef LPD3DX10FONT_DESCW LPD3DX10FONT_DESC;
#else
typedef D3DX10FONT_DESCA D3DX10FONT_DESC;
typedef LPD3DX10FONT_DESCA LPD3DX10FONT_DESC;
#endif


typedef interface ID3DX10Font ID3DX10Font;
typedef interface ID3DX10Font *LPD3DX10FONT;


// {D79DBB70-5F21-4d36-BBC2-FF525C213CDC}
DEFINE_GUID(IID_ID3DX10Font, 
0xd79dbb70, 0x5f21, 0x4d36, 0xbb, 0xc2, 0xff, 0x52, 0x5c, 0x21, 0x3c, 0xdc);


#undef INTERFACE
#define INTERFACE ID3DX10Font

DECLARE_INTERFACE_(ID3DX10Font, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DX10Font
    STDMETHOD(GetDevice)(THIS_ ID3D10Device** ppDevice) PURE;
    STDMETHOD(GetDescA)(THIS_ D3DX10FONT_DESCA *pDesc) PURE;
    STDMETHOD(GetDescW)(THIS_ D3DX10FONT_DESCW *pDesc) PURE;
    STDMETHOD_(BOOL, GetTextMetricsA)(THIS_ TEXTMETRICA *pTextMetrics) PURE;
    STDMETHOD_(BOOL, GetTextMetricsW)(THIS_ TEXTMETRICW *pTextMetrics) PURE;

    STDMETHOD_(HDC, GetDC)(THIS) PURE;
    STDMETHOD(GetGlyphData)(THIS_ UINT Glyph, ID3D10ShaderResourceView** ppTexture, RECT *pBlackBox, POINT *pCellInc) PURE;

    STDMETHOD(PreloadCharacters)(THIS_ UINT First, UINT Last) PURE;
    STDMETHOD(PreloadGlyphs)(THIS_ UINT First, UINT Last) PURE;
    STDMETHOD(PreloadTextA)(THIS_ LPCSTR pString, INT Count) PURE;
    STDMETHOD(PreloadTextW)(THIS_ LPCWSTR pString, INT Count) PURE;

    STDMETHOD_(INT, DrawTextA)(THIS_ LPD3DX10SPRITE pSprite, LPCSTR pString, INT Count, LPRECT pRect, UINT Format, D3DXCOLOR Color) PURE;
    STDMETHOD_(INT, DrawTextW)(THIS_ LPD3DX10SPRITE pSprite, LPCWSTR pString, INT Count, LPRECT pRect, UINT Format, D3DXCOLOR Color) PURE;

#ifdef __cplusplus
#ifdef UNICODE
    HRESULT GetDesc(D3DX10FONT_DESCW *pDesc) { return GetDescW(pDesc); }
    HRESULT PreloadText(LPCWSTR pString, INT Count) { return PreloadTextW(pString, Count); }
#else
    HRESULT GetDesc(D3DX10FONT_DESCA *pDesc) { return GetDescA(pDesc); }
    HRESULT PreloadText(LPCSTR pString, INT Count) { return PreloadTextA(pString, Count); }
#endif
#endif //__cplusplus
};

#ifndef GetTextMetrics
#ifdef UNICODE
#define GetTextMetrics GetTextMetricsW
#else
#define GetTextMetrics GetTextMetricsA
#endif
#endif

#ifndef DrawText
#ifdef UNICODE
#define DrawText DrawTextW
#else
#define DrawText DrawTextA
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


HRESULT WINAPI 
    D3DX10CreateFontA(
        ID3D10Device*           pDevice,  
        INT                     Height,
        UINT                    Width,
        UINT                    Weight,
        UINT                    MipLevels,
        BOOL                    Italic,
        UINT                    CharSet,
        UINT                    OutputPrecision,
        UINT                    Quality,
        UINT                    PitchAndFamily,
        LPCSTR                  pFaceName,
        LPD3DX10FONT*           ppFont);

HRESULT WINAPI 
    D3DX10CreateFontW(
        ID3D10Device*           pDevice,  
        INT                     Height,
        UINT                    Width,
        UINT                    Weight,
        UINT                    MipLevels,
        BOOL                    Italic,
        UINT                    CharSet,
        UINT                    OutputPrecision,
        UINT                    Quality,
        UINT                    PitchAndFamily,
        LPCWSTR                 pFaceName,
        LPD3DX10FONT*           ppFont);

#ifdef UNICODE
#define D3DX10CreateFont D3DX10CreateFontW
#else
#define D3DX10CreateFont D3DX10CreateFontA
#endif


HRESULT WINAPI 
    D3DX10CreateFontIndirectA( 
        ID3D10Device*             pDevice,  
        CONST D3DX10FONT_DESCA*   pDesc, 
        LPD3DX10FONT*             ppFont);

HRESULT WINAPI 
    D3DX10CreateFontIndirectW( 
        ID3D10Device*             pDevice,  
        CONST D3DX10FONT_DESCW*   pDesc, 
        LPD3DX10FONT*             ppFont);

#ifdef UNICODE
#define D3DX10CreateFontIndirect D3DX10CreateFontIndirectW
#else
#define D3DX10CreateFontIndirect D3DX10CreateFontIndirectA
#endif

HRESULT WINAPI D3DX10UnsetAllDeviceObjects(ID3D10Device *pDevice);

#ifdef __cplusplus
}
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////
//
// TODO: move these to a central error header file
// 
#define _FACD3D  0x876
#define MAKE_D3DHRESULT( code )  MAKE_HRESULT( 1, _FACD3D, code )
#define MAKE_D3DSTATUS( code )  MAKE_HRESULT( 0, _FACD3D, code )

#define D3DERR_INVALIDCALL                      MAKE_D3DHRESULT(2156)
#define D3DERR_WASSTILLDRAWING                  MAKE_D3DHRESULT(540)

#endif //__D3DX10CORE_H__

