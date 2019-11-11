#include <windows.h>
DWORD TeamColor;	
DWORD CGameContextPointer(void) {	
	
	unsigned long dwBase = *(DWORD*)ResultPlayerBase;
		return dwBase;
}
DWORD GetBasePlayerHealth(void) {	
	
	unsigned long dwBase2 = *(DWORD*)ResultBaseESP;
		return dwBase2;
}

CPing		*pPing(UINT i)	
{
	return (CPing*)((CGameContextPointer() + 0x3B6D0) + i * 1);
}

CKill		*pKill(UINT i)	
{
	return (CKill*)((CGameContextPointer() + 0x3B72C) + i * 4);
}

CNames		*oNames(UINT i)	
{
	return (CNames*)((CGameContextPointer() + PTR_NAMES) + i * 0x21);
}

CHealth		*oHealth(UINT i)	
{
	return (CHealth*)((GetBasePlayerHealth() + 0x264) + i * 0x20);
}

void PingServer(int x, int y, float Health, IDirect3DDevice9* pDevice)
{
	if( !pDevice )
		return;
	for (int index = 0; index <= (Health-1); index++)
	{
	D3DCOLOR HPcol = Green;
	if (Health == 3 )HPcol = Orange;
	if (Health == 2 )HPcol = Orange;
	if (Health == 1) HPcol = Red;
	FillRGB(x + (index*4),y,3,14,HPcol,pDevice);
	}
}

void HealthbarServer(IDirect3DDevice9* pDevice, int x, int y, float CurHP)
{
	if( !pDevice )
		return;
	float Long = (CurHP);
	FillRGB(x,y,CurHP*1.2,14,TeamColor,pDevice );
}

void DrawBoxObsv( int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
	FillRGB( x, y, w, h, BoxColor, pDevice );
	DrawBorder( x, y, w, h, 1, BorderColor, pDevice );
}

void DrawBoxServer( int x, int y, IDirect3DDevice9* pDevice )
{
	if( !pDevice )
		return;
    DrawBoxObsv( x, y, 167, 18,Black, TeamColor, pDevice );
}

void MenuX_DrawObserver(LPDIRECT3DDEVICE9 pDevice)
{
	int ServerRED	=500;
	int ServerBLUE	=250;
	int ServerY1	=480;	

	D3DVIEWPORT9 viewP;
	pDevice->GetViewport( &viewP );
	DWORD ScreenCenterX = viewP.Width / 2; 
	DWORD ScreenCenterY = viewP.Height / 2; 
	unsigned long dwBase	= *(DWORD*)ResultPlayerBase;
	TeamScore	*TeamzScore	= (TeamScore*)((CGameContextPointer() + 0x3B724));
	for (int i = 0; i<=15; i++)
	{
		if (pPing(i)->iLog > 0)
		//if (dwBase !=0)
		{
			bHookedTele = true;
			int myTeam	= GetTeam(i);
			
					
			if (Nh_Teknology27)		
			{
				if (myTeam == 1)
				{
					TeamColor = Red;

					DrawBoxServer(ScreenCenterX - ServerRED + 40,(int)ServerY1+(10*i),pDevice);
					HealthbarServer(pDevice,ScreenCenterX - ServerRED + 65,(int)(ServerY1+2)+(10*i),oHealth(i)->CurHP);
					PingServer(ScreenCenterX - ServerRED + 187,(int)(ServerY1+2)+(10*i),pPing(i)->iLog, pDevice);
					DrawStringESP(ScreenCenterX - ServerRED + 45,(ServerY1+2)+(10*i),White,"%d|%d  %s",pKill(i)->bKill,pKill(i)->bDead,oNames(i)->szNames);
					DrawStringESP(ScreenCenterX - ServerRED + 40,460,Red,"[Red Team : %d]",TeamzScore->TScoreRed);	
					
				}
	
				if (myTeam == 2)
				{
					TeamColor = Blue;

					DrawBoxServer(ScreenCenterX + ServerBLUE + 40,(ServerY1-10)+(10*i),pDevice);
					HealthbarServer(pDevice, ScreenCenterX + ServerBLUE + 65 ,(int)((ServerY1+2)-10)+(10*i),oHealth(i)->CurHP);
					PingServer(ScreenCenterX + ServerBLUE + 187,(int)((ServerY1+2)-10)+(10*i),pPing(i)->iLog, pDevice);	
					DrawStringESP(ScreenCenterX + ServerBLUE + 45,((ServerY1+2)-10)+(10*i),White,"%d|%d  %s",pKill(i)->bKill,pKill(i)->bDead,oNames(i)->szNames);		
					DrawStringESP(ScreenCenterX + ServerBLUE + 40,460,Blue,"[Blue Team : %d]",TeamzScore->TScoreBlue);	
				}
			}		
		}
	}	
bHookedTele = false;
}