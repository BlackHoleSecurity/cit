#include "MenuX_Options.h"
//-----------------------------------------HRESULT-----------------------------------------------------------------------------------------
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 );
tEndScene oEndScene = 0;

typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 , D3DPRIMITIVETYPE ,INT ,UINT ,UINT ,UINT ,UINT );
tDrawIndexedPrimitive oDrawIndexedPrimitive = 0;

#define HTSN(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);
