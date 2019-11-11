
bool Shot = false;
bool HookedShot = false;
int HOOKAIMSHOT = 0;

bool AimOff= false;

		//======================================================//
		//           Desk : CODING PLAYER TARGET                //
		//======================================================//

DWORD BackupEDXTele;
int AimSlot,AimHead,AimHeadCrot = 0;
bool BulletEnable = false;
float fX,fY,fZ = 0;
_declspec(naked)void i3CollideeLine_SetEnd()
{
	_asm{
		cmp [BulletEnable],0
			je Skip
			mov eax,dword ptr ss:[esp+0x4]
		mov [BackupEDXTele],edx
			mov edx,[fX]
		mov [eax+0x0],edx
			mov edx,[fY]
		mov [eax+0x4],edx
			mov edx,[fZ]
		mov [eax+0x8],edx
			mov edx,[BackupEDXTele]
Skip:
		MOV EAX,DWORD PTR SS:[ESP+0x4]
		FLD DWORD PTR DS:[EAX]
		FSTP DWORD PTR DS:[ECX+0x18]
		FLD DWORD PTR DS:[EAX+0x4]
		FSTP DWORD PTR DS:[ECX+0x1C]
		FLD DWORD PTR DS:[EAX+0x8]
		FSTP DWORD PTR DS:[ECX+0x20]
		FLD DWORD PTR DS:[ECX+0x18]
		FSUB DWORD PTR DS:[ECX+0xC]
		FSTP DWORD PTR DS:[ECX+0x24]
		FLD DWORD PTR DS:[ECX+0x1C]
		FSUB DWORD PTR DS:[ECX+0x10]
		FSTP DWORD PTR DS:[ECX+0x28]
		FLD DWORD PTR DS:[ECX+0x20]
		FSUB DWORD PTR DS:[ECX+0x14]
		FSTP DWORD PTR DS:[ECX+0x2C]
		RETN 0x4
	}
}
class CDeathPlayer
{
public:
    BYTE Death[16];
};
 
class CLocalPlayerID
{
public:
    BYTE ID;
};
DWORD d;

float CalcDistance( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
        return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
                 ( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
                 ( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

BYTE GetUserLife(int iSlot)
{
    DWORD g_pGameContext   = *(DWORD*)ResultPlayerBase; //"bool __thiscall CGameCharaBase::RGC-NET"...
    CDeathPlayer *Life = (CDeathPlayer *) (g_pGameContext + ResultUserDeath);
    return Life->Death[iSlot];
    VirtualProtect((PVOID*)(g_pGameContext+ResultUserDeath), 10, PAGE_EXECUTE_READWRITE, &d);
}
//------------------------------------------------------------------
//"void __thiscall CGameContext::setMySlot"...
//------------------------------------------------------------------
int GetCharaIndex()//Obter Meu Slot.
{
    DWORD g_pGameContext   = *(DWORD*)ResultPlayerBase; //"bool __thiscall CGameCharaBase::RGC-NET"...
    CLocalPlayerID *LocID = (CLocalPlayerID *) (g_pGameContext + PTR_TEAM);
    return LocID->ID;
    VirtualProtect((PVOID*)(g_pGameContext + PTR_TEAM), 10, PAGE_EXECUTE_READWRITE, &d);
}

int GetPriorityTarget()
{
	int Result = -1;
	float fMaxDistance = 180.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	for (int index = 0; index < 16; index++)
	{
		if (!GetUserLife(index) && GetCharaIndex() != index)
		{
			if (GetCharaIndex() %2 != index % 2)
			{
				GetUserBone(LocPlayer, 7 , GetCharaIndex());
				GetUserBone(PlayerEnd, 7 , index);
				if (CalcDistance(LocPlayer, PlayerEnd) < fMaxDistance)
				{
					fMaxDistance = CalcDistance(PlayerEnd, LocPlayer);
					Result = index;
				}
			}
		}
	}
	return Result;
}

		//======================================================//
		//           Desk : CODING MouseHook	                //
		//======================================================//
void MouseHook();;
void MouseHook()
{
	_asm
	{
		cmp [Shot],0
			je Normal
			mov eax, 1;
		retn
Normal:
		mov eax, [ecx+0x14]// 5 byte
		ret
	}
}



		//======================================================//
		//               Desk : Aim Bullet	                    //
		//======================================================//
void NewAIM( float Health, IDirect3DDevice9* pDevice );
void MenuX_DoBulletMode(LPDIRECT3DDEVICE9 pDevice)
{
	unsigned long dwBase	= *(DWORD*)ResultPlayerBase;
	unsigned long dwBase2	= *(DWORD*)ResultBaseESP;	
	CTeam		*pTeam		= ((CTeam*)(dwBase+PTR_TEAM));
	CHealth		*pHealth	= (CHealth*)((dwBase2 + 0x264));
	D3DXVECTOR3 ScreenPos;
	D3DXVECTOR3 HeadPos;
	D3DXVECTOR3 HeadPoSS;
	float ScreenCenterX = (NhViewport.Width /2.0f);
	float ScreenCenterY = (NhViewport.Height /2.0f);
	float ScreenBottomY = (NhViewport.Height);
	if(Nh_Teknology8)
	{
		if(*(PBYTE)ResultBaseAmmo2 > NULL)
		{
			int AimSlot = GetPriorityTarget();
			if(AimSlot != -1)
			{
				D3DXVECTOR3 OnWorld,OnScreen;
				int BoneIndexSelector = 0;
					if(Nh_Teknology7 == 0) //Head
					{
						BoneIndexSelector = 7;
					}
					if(Nh_Teknology7 == 1)//Body
					{
						BoneIndexSelector = 5;
					}
					if(Nh_Teknology7 == 2)//Hand
					{
						BoneIndexSelector = 10;
					}
					if(Nh_Teknology7 == 3)//Foot
					{
						BoneIndexSelector = 9;
					}
					if(Nh_NEWAIM == 1)//NEWNEWRandom
					{
						NewAIM (pHealth->CurHP,pDevice);
					}
				D3DVIEWPORT9 viewP;
				pDevice->GetViewport( &viewP );
				DWORD ScreenCenterX = viewP.Width / 2; 
				DWORD ScreenCenterY = viewP.Height / 2; 
				if(GetUserBone(OnWorld,BoneIndexSelector,AimSlot)){
					BulletEnable = true;
					fX = OnWorld.x;
					fY = OnWorld.y + 0.1f;
					fZ = OnWorld.z;
					if(YoWorlToScreenGa(OnWorld,OnScreen))
					{
						DrawLine(ScreenCenterX-2,ScreenCenterY-2,OnScreen.x,OnScreen.y,1,pHealth->CurHP);///Line Bullet
						{
							int x = ( OnScreen.x);
							int y = ( OnScreen.y);
							int Color = Blue;
							Circle (x,y,6,true,Color,pDevice);
							FillRGB(x-10, y, 7, 1,Color,pDevice);//Left line
							FillRGB(x+4, y, 7, 1,Color,pDevice);//Right line
							FillRGB(x, y-10, 1, 7,Color,pDevice);//Top line
							FillRGB(x, y+4, 1, 7,Color,pDevice);//Bottom line
							D3DRECT rec16 = {x-2, y-2, x+ 2, y+2};
							D3DRECT rec17 = {x-2, y-2, x+ 2, y+2};  
							pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
							pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
						}
					}
				}
				else
				{
					BulletEnable = false;
				}			}
			else
			{
				BulletEnable = false;
			}
		}
	}
}

void NewAIM( float Health, IDirect3DDevice9* pDevice )
{
	if (Health < 120) {Nh_Teknology7 = 1;}
	if (Health < 70) {Nh_Teknology7 = 2;}
	if (Health < 30) {Nh_Teknology7 = 0;}
} 


DWORD NHFunctionAimX(BYTE *MemoryTarget, DWORD FunctionTarget)
{
Sleep(5);
*((DWORD *)(MemoryTarget)) = FunctionTarget;
Sleep(5);
return 0;
}

bool xHookedTele,cHookedShot = false;
DWORD OldProtect;
void MenuX_BuletHooK() 
{
	if(xHookedTele)return;
	VirtualProtect ( (LPVOID)(ResultBaseBullet), sizeof (ResultBaseBullet), PAGE_EXECUTE_READWRITE, &OldProtect ); 
	NHFunctionAimX((PBYTE)ResultBaseBullet,(DWORD)i3CollideeLine_SetEnd);
	VirtualProtect ( (LPVOID)(ResultBaseBullet), sizeof (ResultBaseBullet), OldProtect, &OldProtect ); 
	xHookedTele = true; 
}


void DoAutoShot()
{
if (HOOKAIMSHOT==1)
{ 
	if(HookedShot == false)
	{
		VirtualProtect ( (LPVOID)(ResultBaseAutoShot), sizeof (ResultBaseAutoShot), PAGE_EXECUTE_READWRITE, &OldProtect ); 
		NHFunctionAimX((PBYTE)ResultBaseAutoShot,(DWORD)MouseHook); 
		VirtualProtect ( (LPVOID)(ResultBaseAutoShot), sizeof (ResultBaseAutoShot), OldProtect, &OldProtect ); 
		HookedShot = true;
	}
}
		//======================================================//
		//                  Desk : AIM SHOOT	                //
		//======================================================//

if(Nh_Teknology9==1)
{
	HOOKAIMSHOT=1;
if(GetPlayerTarget(GetPriorityTarget()) > NULL)Shot = false;//kalo disni true
else Shot = true;
}
if(Nh_Teknology9==0)
{
	HOOKAIMSHOT=0;
if(GetPlayerTarget(GetPriorityTarget()) > NULL)Shot = true;
else Shot = false;
}	
}
