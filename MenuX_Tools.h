#include "MenuX_Includes.h"
int mx,my;
static struct key_s
{
	bool        bPressed;
	DWORD        dwStartTime;
}kPressingKey[256];

VOID Draw_Text(char* st,int x,int y,DWORD color,ID3DXFont* pFont)
{
    RECT Reth;
    SetRect(&Reth, x, y, x, y );
    pFont->DrawTextA(NULL,st,-1,&Reth,DT_NOCLIP|DT_LEFT,color);
}

VOID Draw_Text(int x, int y, DWORD color, LPSTR text, LPD3DXFONT pFont)
	{
		RECT Reth;
		SetRect(&Reth, x + 12, y - 8, x, y );
		pFont->DrawTextA(NULL, text, -1, &Reth, DT_NOCLIP|DT_LEFT, color);
	}
BOOL IsKeyPressed(int Key,DWORD dwTimeOut)
{
	if( HIWORD( GetKeyState( Key ) ) )
	{
		if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) )
		{
			kPressingKey[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKey[Key].dwStartTime = GetTickCount( );
 
			return TRUE;
		}
	}
	else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}

BOOL IsInMinimizeBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);	
	
	return(MousePosition.x > (x - 450) && MousePosition.x < (x + w - 12) && MousePosition.y > (y - 15) && MousePosition.y < (y + h - 15));
	//return(MousePosition.x > (x - 450) && MousePosition.x < (x + 450) && MousePosition.y > (y - 12) && MousePosition.y < (y + 12));
}

BOOL IsInTabBox(int x,int y)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);	
	return(MousePosition.x > (x - 35) && MousePosition.x < (x + 35) && MousePosition.y > (y - 10) && MousePosition.y < (y + 10));
}

BOOL IsInFiturBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);
	return(MousePosition.x > (x - 18) && MousePosition.x < (x + w - 18) && MousePosition.y > (y - 10) && MousePosition.y < (y + h - 10));
}

void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
 
D3DRECT rec = { x, y, x + w, y + h };
pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

void FillARGBTriangle(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color, IDirect3DDevice9 *pDevice)
{
	struct Vertex
	{
		float x,y,z,ht;
		DWORD Color;
	};

	Vertex V[4];
    V[0].Color = V[1].Color = V[2].Color = V[3].Color = color;
    V[0].z   = V[1].z   = V[2].z   = V[3].z   = 0.0f;
    V[0].ht = V[1].ht = V[2].ht = V[3].ht = 0.0f;

	V[0].x = (float)x1;
	V[0].y = (float)y1;
	V[1].x = (float)x2;
	V[1].y = (float)y2;
	V[2].x = (float)x3;
	V[2].y = (float)y3;
	V[3].x = (float)x1 + 1;
	V[3].y = (float)y1 + 1;

	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1); 
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,V,sizeof(Vertex));

}

VOID FillGradient(int x, int y, int h, int w, DWORD color1, DWORD color2, LPDIRECT3DDEVICE9 pDevice)
{
float alpha = 5;
     float step;
	DWORD r1 = (color1>>16)&0xff;
	DWORD g1 = (color1>>8)&0xff;
	DWORD b1 = (color1>>32)&0xff;
	DWORD r2 = (color2>>16)&0xff;
	DWORD g2 = (color2>>8)&0xff;
	DWORD b2 = (color2>>32)&0xff;
	float rDif,gDif,bDif;
	rDif = ((float)r2-(float)r1)/h;
	gDif = ((float)g2-(int)g1)/h;
	bDif = ((float)b2-(float)b1)/h;
	DWORD DrawCol;
	 step  = ((255 - alpha) / h);
	for(int i = 0;i<h;i++)
	{
	alpha = alpha + step;
		DrawCol = (r1+(int)(rDif * i) << 16) | (g1+(int)(gDif * i) << 8) | (b1+(int)(bDif*i));
		FillRGB(x,y+i,w,1,DrawCol, pDevice);
	}
}

VOID FillGradients(int x, int y, int h, int w, DWORD color1, DWORD color2, LPDIRECT3DDEVICE9 pDevice)
{
float alpha = 5;
     float step;
	DWORD r1 = (color1>>16)&0xff;
	DWORD g1 = (color1>>8)&0xff;
	DWORD b1 = (color1)&0xff;
	DWORD r2 = (color2>>16)&0xff;
	DWORD g2 = (color2>>8)&0xff;
	DWORD b2 = (color2)&0xff;
	float /*aDif,*/rDif,gDif,bDif;
	rDif = ((float)r2-(float)r1)/h;
	gDif = ((float)g2-(int)g1)/h;
	bDif = ((float)b2-(float)b1)/h;
	DWORD DrawCol;
	 step  = ((255 - alpha) / h);
	for(int i = 0;i<h;i++)
	{
	alpha = alpha + step;
		DrawCol = (r1+(int)(rDif * i) << 16) | (g1+(int)(gDif * i) << 8) | (b1+(int)(bDif*i));
		FillRGB(x,y+i,w,1,DrawCol, pDevice);
	}
}

void DrawBorders( int x, int y, int w, int h, int px, D3DCOLOR BorderColor,IDirect3DDevice9* pDevice ) 
{ 
	if( !pDevice )
		return;
    FillRGB( x, (y + h - px), w, px,     BorderColor, pDevice ); // Height Kanan
    FillRGB( x, y, px, h,                BorderColor, pDevice ); // Width Atas
    FillRGB( x, y, w, px,                BorderColor, pDevice ); // Height Kiri
    FillRGB( (x + w - px), y, px, h,     BorderColor, pDevice ); // Width Bawah
}

#define PI 3.14159265//Defining what PI is. PI is a Circle
void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color) 
{ 

    D3DXVECTOR2 Line[128]; 
    float Step = PI * 2.0 / numSides; 
    int Count = 0; 
    for (float a=0; a < PI*2.0; a += Step) 
    { 
        float X1 = radius * cos(a) + X; 
        float Y1 = radius * sin(a) + Y; 
        float X2 = radius * cos(a+Step) + X; 
        float Y2 = radius * sin(a+Step) + Y; 
        Line[Count].x = X1; 
        Line[Count].y = Y1; 
        Line[Count+1].x = X2; 
        Line[Count+1].y = Y2; 
        Count += 2; 
    } 
    NHLine->Begin(); 
    NHLine->Draw(Line,Count,Color); 
    NHLine->End(); 
}

void DrawPoint(int x, int y, int w, int h, DWORD color,IDirect3DDevice9* pDevice)
{
    FillRGB((int)x, (int)y, (int)w, (int)h, color, pDevice);

} 

char* ShowFPS()
	{
		static int FPSCounter = 0;
		static float FPSLastTickCount = 0.0f;
		static float FPSCurrentTickCount;
		static char cfps[6] = "";

		FPSCurrentTickCount = clock() * 0.001f;
		FPSCounter++;
		if ((FPSCurrentTickCount - FPSLastTickCount) > 1.0f)
		{
			FPSLastTickCount = FPSCurrentTickCount;
			sprintf(cfps, ": %d", FPSCounter);
			FPSCounter = 0;
		}
		return cfps;
	}

char* GetDate()
	{
		SYSTEMTIME st;
		GetSystemTime(&st);
		char *logbuf = new char[ 256 ];
		sprintf(logbuf,": %d-%d-%d" ,st.wDay,st.wMonth,st.wYear);
	return logbuf;
	}

char* GetTime()
{
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime(&current_time);
	char *logbuf = new char[ 256 ];
	sprintf(logbuf, ": %02d:%02d:%02d", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return logbuf;
}