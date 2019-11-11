	
int GetMyCharaIndex()
{
	unsigned long dwBase	= *(DWORD*)ResultPlayerBase;
	CTeam *MyTeam = (CTeam*) ((dwBase + PTR_TEAM));
	return MyTeam->iTeam;
}

bool GetUserBone( D3DXVECTOR3 &Out,  int BoneIdx ,int Idx)
{
	DWORD dwGameBase = *(DWORD*)ResultBaseESP;
	if ( dwGameBase )
	{
		CGameBase* GameBase = (CGameBase*)( *(DWORD*)(dwGameBase + 0x14 + ( 0x4 * Idx ) ) );
		if ( GameBase && GameBase->Bones)
		{
			Out.x = GameBase->Bones->BoneData[ BoneIdx ].BoneMatrix._41;
			Out.y = GameBase->Bones->BoneData[ BoneIdx ].BoneMatrix._42;
			Out.z = GameBase->Bones->BoneData[ BoneIdx ].BoneMatrix._43;
			return true;
		}
	}
	return false;
}

bool YoWorlToScreenGa( D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
	D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
	D3DXMATRIX identity;
    D3DXVECTOR3 vScreen;
	i3Device->GetViewport(&NhViewport);
	NhViewport.X = NhViewport.Y = 0;
    NhViewport.MinZ     = 0;
    NhViewport.MaxZ     = 1;
	D3DXVec3Project(
		&vScreen, 
		&PlayerPos, 
		&NhViewport, 
		&pRC->pRenderData->ProjMatrix, 
		&pRC->pRenderData->ViewMatrix, 
		&pRC->pRenderData->WorldMatrix);
	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < NhViewport.Width && vScreen.y < NhViewport.Height)
	{
		PlayerScaled.x = vScreen.x;
		PlayerScaled.y = vScreen.y ;
		PlayerScaled.z = vScreen.z;
		return true; 
	}
	return false;
}
void DrawLine ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, float Health) 
{    
	DWORD HPcol = Blue;
	if (Health < 90)HPcol = Green;
	if (Health < 80) HPcol = Yellow;
	if (Health < 40) HPcol = Orange;
	if (Health < 10) HPcol = Red;
	D3DXVECTOR2 vLine[ 2 ]; // 2 Poin 
	NHLine->SetAntialias( 0 ); // Set Tepi 

	NHLine->SetWidth( dwWidth ); // Lebar Dari Line 
	NHLine->Begin(); 

	vLine[ 0 ][ 0 ] = Xa; // Jadikan Point Menjadi Array 
	vLine[ 0 ][ 1 ] = Ya; 
	vLine[ 1 ][ 0 ] = Xb; 
	vLine[ 1 ][ 1 ] = Yb; 

	NHLine->Draw( vLine, 2, HPcol ); // Draw Garis , Jumlah Garis , Warna Garis  
	NHLine->End(); // Selesai 
} 


void HealthBar15(int x, int y, float Health)
{
	const D3DCOLOR colours[] = { Red, Red, Red, Red, Orange, Orange, Orange, Orange, Yellow, Yellow, Yellow, Yellow, Green, Green, Green, Green, Green, Green, Blue, Blue }; // this is our order
	int boxSizeX = 2; 
	int boxSizeY = 7;
	int boxGap = 1;
	for ( int c = 0 ; c < 20; c++ )
	{
		if ( Health > ( 5 * c ) )
			DrawBorder(x-1,y-1,62,9,1,colours[c],i3Device );
	}
	for ( int i = 0 ; i < 20; i++ )
	{
		if ( Health > ( 5 * i ) )
			FillRGB(x,y, boxSizeX, boxSizeY,colours[i],i3Device);		
		else
			FillRGB(x,y, boxSizeX, boxSizeY,Grey,i3Device);
			x = x + boxSizeX+ boxGap;
	}
}
void DrawStringESP(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 200, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	NHT3XT->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}


void DrawBoxESP( int x, int y, int w, int h, float Health, IDirect3DDevice9* pDevice )
{
	DWORD HPcol = Blue;
	if (Health < 90)HPcol = Green;
	if (Health < 80) HPcol = Yellow;
	if (Health < 40) HPcol = Orange;
	if (Health < 10) HPcol = Red;
	DrawBorder( x, y, w, h, 1, HPcol, pDevice );
} 

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v;

	v.fX = X;
	v.fY = Y;
	v.fZ = Z;
	v.fRHW = RHW;
	v.Color = color;
	v.fU = U;
	v.fV = V;

	return v;
}

#define PISSS 3.14159265
void Circle( float x, float y, float rad, bool center, DWORD color ,LPDIRECT3DDEVICE9 pDevice)
{
	const int NUMPOINTS = 34;

	if(!center)
	{
		x -= rad;
		y -= rad;
	}

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;
	WedgeAngle = (float)( (2*PISSS) / NUMPOINTS );
	for( i=0; i<=NUMPOINTS; i++ )
	{
		Theta = i * WedgeAngle;
		X = (float)( x + rad * cos(Theta) );
		Y = (float)( y - rad * sin(Theta) );
		Circle[i] = CreateD3DTLVERTEX( X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f );
	}
	pDevice	->	SetFVF			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	pDevice	->	SetTexture		( 0, NULL );
	pDevice	->	DrawPrimitiveUP	( D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]) );
}

DWORD GetPlayerTarget(int myIDX)
{
	DWORD BasePlayer_B = *(DWORD*)(ResultBaseESP);
	if(IsBadReadPtr((void*)BasePlayer_B,4))return 0;
	DWORD PlayerIndexA = *(DWORD*)(BasePlayer_B + 0x14 + (myIDX * 4));
	if(IsBadReadPtr((void*)PlayerIndexA,4))return 0;
	DWORD PlayerIndexB = *(DWORD*)(PlayerIndexA + 0x550);  //560
	if(IsBadReadPtr((void*)PlayerIndexB,4))return 0;
	DWORD IsTargetingEnemy = *(DWORD*)(PlayerIndexB + 0x94E8);
	if(IsBadReadPtr((void*)IsTargetingEnemy,4))return 0;
return IsTargetingEnemy;
}


DWORD BurstPiso, vReload = 0;
DWORD _ReadMEM(DWORD dwPtr,DWORD A1,DWORD B1,DWORD C1,DWORD D1)
{
	DWORD C=0;
	if (IsBadReadPtr((PDWORD)dwPtr,4)==0)
	{
		C=*(PDWORD)((DWORD)(dwPtr))+A1;
		if (IsBadReadPtr((PDWORD )C,4)==0)
		{
			C=*(PDWORD)((DWORD)(C ))+ B1;
			if (IsBadReadPtr((PDWORD)C,4)==0)
			{
				C=*(PDWORD)((DWORD)(C ))+ C1;
				if (IsBadReadPtr((PDWORD)C,4)==0)
				{
					C=*(PDWORD)((DWORD)(C ))+ D1;
					if (IsBadReadPtr((PDWORD)C,4)==0)
					{
						return *(PDWORD)C; 
					}
				}
			}
		}
	}
	return C;
}
DWORD _ReadMEM(DWORD dwPtr,DWORD A1,DWORD B1,DWORD C1)
{
	DWORD C=0;
	if (IsBadReadPtr((PDWORD)dwPtr,4)==0)
	{
		C=*(PDWORD)((DWORD)(dwPtr))+A1;
		if (IsBadReadPtr((PDWORD )C,4)==0)
		{
			C=*(PDWORD)((DWORD)(C ))+ B1;
			if (IsBadReadPtr((PDWORD)C,4)==0)
			{
				C=*(PDWORD)((DWORD)(C ))+ C1;
				if (IsBadReadPtr((PDWORD)C,4)==0)
				{
					return *(PDWORD)C; 
				}
			}
		}
	}
	return C;
}
DWORD BulletFast = 0;
DWORD _ReadMEM(DWORD dwPtr,DWORD A1,DWORD B1)
{
	DWORD C=0;
	if (IsBadReadPtr((PDWORD)dwPtr,4)==0)
	{
		C=*(PDWORD)((DWORD)(dwPtr))+A1;
		if (IsBadReadPtr((PDWORD )C,4)==0)
		{
			C=*(PDWORD)((DWORD)(C ))+ B1;
			if (IsBadReadPtr((PDWORD)C,4)==0)
			{
				return *(PDWORD)C; 
			}
		}
	}
	return C;
}

void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD WriteValue)
{
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0)
	{ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0)
		{ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0)
			{ 
				*(PDWORD)Temp = WriteValue;
			}
		}
	}
}

WORD WriteVaL1, WriteVaL2, WriteVaL3, WriteVaL4, WriteVaL5;
void __ReadMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD ReadValue)
{
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0)
	{ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0)
		{ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0)
			{ 
				Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
				if (IsBadReadPtr((PDWORD)Temp,4) == 0)
				{
					switch (ReadValue)
					{
						case 1:
						WriteVaL1 = *(PWORD)Temp;
						case 2:
						WriteVaL2 = *(PWORD)Temp;
						case 3:
						WriteVaL3 = *(PWORD)Temp;
						case 4:
						WriteVaL4 = *(PWORD)Temp;
						case 5:
						WriteVaL5 = *(PWORD)Temp;
					}
				}
			}
		}
	}
}
void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD WriteValue)
{
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0)
	{ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0)
		{ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0)
			{ 
				Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
				if (IsBadReadPtr((PDWORD)Temp,4) == 0)
				{
					*(PDWORD)Temp = WriteValue;
				}
			}
		}
	}
}


void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD Ptr4, DWORD WriteValue)
{
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0)
	{ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0)
		{ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0)
			{ 
				Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
				if (IsBadReadPtr((PDWORD)Temp,4) == 0)
				{
					Temp = *(PDWORD)((DWORD)(Temp)) + Ptr4;
					if (IsBadReadPtr((PDWORD)Temp,4) == 0)
					{
						*(PDWORD)Temp = WriteValue;
					}
				}
			}
		}
	}
}

void NHMemFuction (void *adr, void *ptr, int size)
{
        DWORD CheckProtection;
        VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &CheckProtection);
        memcpy(adr,ptr,size);
        VirtualProtect(adr,size,CheckProtection, &CheckProtection);
} 