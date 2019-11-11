#include "Updater_Funtion.h"
#include "Updater_Signature.h"

DWORD ResultBase, ResultTeam, ResultAim, ResultPTR, SkillDamage, Resulti3Bypass, ResultESPHook, ResultUserDeath;
DWORD ResultPlayerWeapon, ResultPlayerBase, ResultAdrHealth, ResultBaseESP, ResultBaseAmmo2, ResultPlayerRespon, ResultBaseVK, ResultBaseFloadVK, GetCalculateAmmo;
DWORD PTR_TEAM, PTR_NAMES, PTR_PLAYER, PTR_RANK1, PTR_RANK2, PTR_RESPAWN; 
DWORD ResultBaseBullet, ResultBaseAutoShot, ResultBaseAimLockX, ResultBaseAimLockY;
DWORD PTR_NoRecoil, PTR_BaseAmmo, PTR_AmmoKanan, PTR_AmmoKiri, WeaponBugs, WallBugs, FloadKick, STR_HACKER_ID, Respawn, WallShot, FastPlant, pNightVision;


HMODULE hGfxDx		= LoadLibrary("i3GfxDx.dll");
HMODULE i3ScDx		= LoadLibrary("i3SceneDx.dll");
HMODULE i3Input		= LoadLibrary("i3InputDx.dll");
HMODULE i3GuiD		= LoadLibrary("i3GuiDx.dll");

DWORD dwPB			= (DWORD)GetModuleHandleA("PointBlank.exe");
DWORD PB			= GetSizeofCode("PointBlank.exe");
DWORD dwi3GD		= (DWORD)GetModuleHandleA("i3GfxDx.dll");
DWORD i3GD			= GetSizeofCode("i3GfxDx.dll");
DWORD dwNxChara		= (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
DWORD NxChara		= GetSizeofCode("NxCharacter.2.8.1.dll");


DWORD i3CollideeLine= (DWORD)GetProcAddress(i3ScDx, "?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z"); // BaseBullet
DWORD GetButtonState= (DWORD)GetProcAddress(i3Input, "?GetButtonState@i3InputMouse@@QAEIXZ");	// BaseAutoShoot
DWORD i3GuiImage	= (DWORD)GetProcAddress(i3GuiD, "?GetTexture@i3GuiImage@@QAEPAVi3Texture@@XZ"); //BaseAimLockX
DWORD i3IndexArray	= (DWORD)GetProcAddress(hGfxDx, "?SetDataType@i3IndexArray@@QAEXW4I3G_IDX_TYPE@"); //BaseAimLockY

//-----------------------------HOOK Updater----------------------------------------//
DWORD BaseRender	= (DWORD)GetProcAddress(hGfxDx, XStr(0x0B, 0x29, 0x4F, 0x70370E22, 0x01313B32, 0x322A1A35, 0x35283826, 0x2B202151, 0x3325330F, 0x543A0C04, 0x0F091F2D, 0x001E0517, 0x0B003536, 0x36000000 ).c());
DWORD dwi3Bypass	= FindPattern(dwi3GD, i3GD, (PBYTE)Pattern_i3Bypass, Mask_i3Bypass);
DWORD dwESPHook		= FindPattern(dwi3GD, i3GD, (PBYTE)Pattern_HookESP, Mask_HookESP);
DWORD dwHSBypass	= 0x1F3C /*Exception Raised*/ + 0x7C;
//---------------------------------------------------------------------------------//
DWORD dwFramework	= FindPattern(dwPB, PB, (BYTE*)"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x6A\x01\x8B\x8D\x00\x00\x00\x00\x8B\x91\x00\x00\x00\x00\x8B\x85\x00\x00\x00\x00\x8B\x88\x00\x00\x00\x00\x8B\x12\x8B\x82\x00\x00\x00\x00\xFF\xD0\xE9\x00\x00\x00\x00\x83\x7D\xF8\x00", "xx????x????xxxx????xx????xx????xx????xxxx????xxx????xxxx") + 0x2;
DWORD dwRespawn		= FindPattern(dwPB, PB, (PBYTE)Pattern_Respawn, Mask_Respawn) - dwPB;
DWORD dwWallShot	= FindPattern(dwPB, PB, (PBYTE)Pattern_WallShot, Mask_WallShot);
DWORD dwFastPlant	= FindPattern(dwPB, PB, (PBYTE)Pattern_FastPlant, Mask_FastPlant) - dwPB;
DWORD dwpNightVision= FindPattern(dwPB, PB, (PBYTE)Pattern_pNightVision, Mask_pNightVision) - dwPB;
DWORD dwTeam		= FindPattern(dwPB, PB, (PBYTE)Pattern_PTRTeam, Mask_PTRTeam);
DWORD dwUser		= FindPattern(dwPB, PB, (PBYTE)Pattern_SetUserDeath, Mask_SetUserDeath);
DWORD dwAIMBullet	= FindPattern(dwPB, PB, (PBYTE)Pattern_AIM, Mask_AIM);
DWORD dwPTRRecoil	= FindPattern(dwPB, PB, (PBYTE)Pattern_Recoil, Mask_Recoil);
DWORD dwBaseWeapon	= FindPattern(dwPB, PB, (PBYTE)Pattern_BaseWeapon, Mask_BaseWeapon);
DWORD dwWeaponBugs	= FindPattern(dwPB, PB, (PBYTE)Pattern_WeaponBugs, Mask_WeaponBugs) - dwPB;
DWORD BasePeler		= FindPattern(dwPB, PB, (PBYTE)uPeler,"xxx????xxxx");
DWORD BaseFloadAVK	= FindPattern(dwPB, PB, (PBYTE)FloadAVK,"x????x????xxxx?xxxx");
DWORD dwWallBugs	= FindPattern(dwNxChara, NxChara, (PBYTE)Pattern_Wtw, Mask_Wtw) - dwNxChara;
DWORD FindStrHackerID	= FindPattern(dwPB, PB, (PBYTE)"\x53\x54\x52\x5F\x48\x41\x43\x4B\x45\x52\x5F\x49\x44\x00\x00\x00", "xxxxxxxxxxxxxxxx") - dwPB; 


void MenuX_Updater()
{
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwBaseWeapon+0x2), &ResultBase, sizeof(ResultBase), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwTeam+0x5), &ResultTeam, sizeof(ResultTeam), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwUser+0x2), &ResultUserDeath, sizeof(ResultUserDeath), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwAIMBullet+0xC), &ResultAim, sizeof(ResultAim), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRRecoil+0x2), &ResultPTR, sizeof(ResultPTR), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwi3Bypass+0x2), &Resulti3Bypass, sizeof(Resulti3Bypass), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwESPHook+0x2), &ResultESPHook, sizeof(ResultESPHook), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (BaseFloadAVK+0x6), &ResultBaseFloadVK, sizeof(ResultBaseFloadVK), NULL);
	//-----Base Adr-----//
	ResultPlayerWeapon					= ResultBase;
	ResultPlayerBase					= ResultBase + 0x1C;
	ResultAdrHealth                     = ResultBase + 0x1C - 0x34;
	ResultBaseESP	                    = ResultBase - 0x1C + 0x4;
	ResultBaseAmmo2                     = ResultBase - 0x1C;
	ResultPlayerRespon					= ResultBase - 0x28 - 0x24;
	ResultBaseVK						= ResultBase - 0x28;
	GetCalculateAmmo					= *(PDWORD)(BasePeler + 0x0C);
	//-----Base Ptr-----//
	PTR_TEAM							= ResultTeam;
	PTR_NAMES							= ResultTeam - 0x420;
	PTR_PLAYER							= ResultTeam - 0x1ED0;
	PTR_RANK1							= ResultTeam - 0x1C64;
	PTR_RANK2							= ResultTeam - 0x1C63;
	PTR_RESPAWN							= ResultTeam - 0x227A;
	//-----Base Adr AIM-----//
	ResultBaseBullet					= ResultAim;
	ResultBaseAutoShot					= ResultAim - 0x554;
	ResultBaseAimLockX					= ResultAim - 0x778;
	ResultBaseAimLockY					= ResultAim - 0x9A8;
	//-----Memory Hack-----//
	PTR_NoRecoil			=ResultPTR;
	PTR_BaseAmmo			=ResultPTR - 0x14;
	PTR_AmmoKanan			=ResultPTR + 0x744;
	PTR_AmmoKiri			=ResultPTR + 0x73C;
	WeaponBugs				=dwWeaponBugs;
	WallBugs				=dwWallBugs;
	FloadKick				=BaseFloadAVK;
	STR_HACKER_ID			=FindStrHackerID;
	Respawn					=dwRespawn;
	WallShot				=dwWallShot;
	FastPlant				=dwFastPlant;
	pNightVision			=dwpNightVision;
	Beep(1000, 500);
}
 
