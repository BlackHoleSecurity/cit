#include <windows.h>
//--------------------------------define HOOK & UNHOOK--------------------------------------------------------------------------------------------------
#define HOOK(func,addy) o##func = (t##func)DetourB8((DWORD)addy,(DWORD)pG##func,	12) 
#define UNHOOK(func,addy) o##func = (t##func)DetourB8((DWORD)addy,(DWORD)o##func,	12) 



DWORD DetourB8( DWORD  SrcVA, DWORD  DstVA, DWORD  Size )
{
DWORD DetourVA, dwProtect, i;

#define SIZEOF_MOVEAX_JMPEAX 7

	if ( SrcVA && DstVA && Size >= SIZEOF_MOVEAX_JMPEAX )
	{
		DetourVA = (DWORD) VirtualAlloc( 
			NULL, Size + SIZEOF_MOVEAX_JMPEAX, 
			MEM_COMMIT, PAGE_EXECUTE_READWRITE );

		if ( DetourVA && VirtualProtect( (VOID*)SrcVA, Size, PAGE_EXECUTE_READWRITE, &dwProtect ) )
		{
			for ( i=0; i < Size; i++ ) {
				*(BYTE*)( DetourVA + i ) = *(BYTE*)( SrcVA + i );
			}
			
			*(BYTE*)( DetourVA + Size + 0 ) = 0xB8;
			*(DWORD*)( DetourVA + Size + 1 ) = ( SrcVA + Size );
			*(WORD*)( DetourVA + Size + 5 ) = 0xE0FF;

			*(BYTE*)( SrcVA + 0 ) = 0xB8;
			*(DWORD*)( SrcVA + 1 ) = ( DstVA );
			*(WORD*)( SrcVA + 5 ) = 0xE0FF;

			VirtualProtect( (VOID*)SrcVA, Size, dwProtect, &dwProtect );

			VirtualProtect( (VOID*)DetourVA, Size + 
				SIZEOF_MOVEAX_JMPEAX, PAGE_EXECUTE_READ, &dwProtect );

	    	return DetourVA;
		}
	}
	return (0);
}



 void MakeJMP(PDWORD target, PDWORD newfunc)
{
	DWORD Jmpto=(DWORD)(newfunc)-(DWORD)target-5;
	DWORD a;
    VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &a);
    *(PBYTE)(target)=0xE9;
    *(PDWORD)((DWORD)(target)+1)=Jmpto;
	VirtualProtect(target, 8, a, &a);
}

class CHSBypass
{
public:
	char Fix[168];
	DWORD dwES;
	char Mix[156];
	DWORD dwDIP;
};

__declspec(naked)void HookES()
{ 
 _asm
	{
		push eax
		pop eax
		jmp pGEndScene
	}
}
__declspec(naked)void HookDIP()
{ 
 _asm
	{
		push eax
		pop eax
		jmp pGDrawIndexedPrimitive
	}
}


DWORD WINAPI MenuX_Hooking(LPVOID lpParam){
		if (hGfxDx > 0)
		{
				while(!i3Device)
				{
					DWORD ResultRenderPTR = *(PDWORD)((DWORD)(BaseRender))+Resulti3Bypass; /*EndRender@i3RenderContext@@QAEXXZ*/
					Sleep(1);
					if(IsBadStringPtrW((LPCWSTR)ResultRenderPTR,4)==NULL)
					{
						Sleep(1);
						DWORD d,ds;
						VirtualProtect((void*)(ResultRenderPTR), 4, PAGE_EXECUTE_READWRITE, &d);
						memcpy(&i3Device, (void *)ResultRenderPTR, 4);
						VirtualProtect((void*)(ResultRenderPTR), 4, d, &ds);
					}
					Sleep(10);	
				}
					Sleep(1);
					DWORD *g_pDevice = (DWORD*)i3Device;
					g_pDevice = (DWORD*)g_pDevice[0];
					HOOK(EndScene,g_pDevice[42]);
					UNHOOK(EndScene,g_pDevice[42]);
					*(PDWORD)&oDrawIndexedPrimitive = g_pDevice[82];
					*(PDWORD)&oEndScene = g_pDevice[42];
					MakeJMP((PDWORD)(g_pDevice[1] - 5), (PDWORD)(g_pDevice[4] - 5));
					MakeJMP((PDWORD)(g_pDevice[2] - 5), (PDWORD)(g_pDevice[5] - 5));
					MakeJMP((PDWORD)(g_pDevice[3] - 5), (PDWORD)(g_pDevice[6] - 5));
					MakeJMP((PDWORD)(g_pDevice[4] - 5), (PDWORD)HookES);
					MakeJMP((PDWORD)(g_pDevice[5] - 5), (PDWORD)HookDIP);
					while(1)
					{
						DWORD dwEhsvc = (DWORD)GetModuleHandleA(XStr( /*ehsvc.dll*/ 0x03, 0x09, 0x52, 0x373B2723, 0x35793C35, 0x36000000 ).c()) + dwHSBypass;
						CHSBypass *CHS	= *(CHSBypass**)dwEhsvc;
						g_pDevice[42]	= (DWORD)g_pDevice[1] - 5;
						g_pDevice[82]	= (DWORD)g_pDevice[2] - 5;
						CHS->dwES		= g_pDevice[42];
						CHS->dwDIP		= g_pDevice[82];
						Sleep(10);	
					}			
		}
	return 0;
}


