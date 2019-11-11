
D3DXVECTOR3 vStart,vEnd;
D3DXVECTOR3 vvStart,vvEnd;
D3DXVECTOR3 vStart2,vEnd2;
D3DXVECTOR3 vvStart2,vvEnd2;
D3DXVECTOR3 vStart3,vEnd3;
D3DXVECTOR3 vvStart3,vvEnd3;
D3DXVECTOR3 vStart4,vEnd4;
D3DXVECTOR3 vvStart4,vvEnd4;
D3DXVECTOR3 vStart5,vEnd5;
D3DXVECTOR3 vvStart5,vvEnd5;
D3DXVECTOR3 vStart6,vEnd6;
D3DXVECTOR3 vvStart6,vvEnd6;
D3DXVECTOR3 vStart7,vEnd7;
D3DXVECTOR3 vvStart7,vvEnd7;
D3DXVECTOR3 vStart8,vEnd8;
D3DXVECTOR3 vvStart8,vvEnd8;
D3DXVECTOR3 vStart9,vEnd9;
D3DXVECTOR3 vvStart9,vvEnd9;
D3DXVECTOR3 vStart10,vEnd10;
D3DXVECTOR3 vvStart10,vvEnd10;

class RenderContext;
//DWORD dwGFX			= (DWORD)GetModuleHandle("i3GfxDx.dll");
//RenderContext *pRC	= (RenderContext*)(dwGFX + 0x1AD2F0);
RenderContext *pRC	= (RenderContext*)(BaseRender);

#define PLAYERSIZE	0x11A8
struct CPlayers 
{ 
float yaw; 
float pitch; 
D3DXVECTOR3 pos; 
char unkno8[2704]; 
}; 


struct CTeam
{
	BYTE iTeam;
};
struct TeamScore
{
public:
	WORD  TScoreRed;
	WORD  TScoreBlue;
};
class CKill
{
public:
	BYTE bKill;
	char _0001[1];
	BYTE bDead;
	char _0003[1];
};
class CPing
{
public:
	BYTE iLog;
};
struct CHealth
{
	float CurHP;
};
struct CNames
{
    char szNames[0x21];
	float CurPlayer;
};
class CBone
{
public:
	D3DXMATRIX BoneMatrix;
};
class CBonesContext
{
public:
	char   Unk[0xC8]; // .\GameCharaBoneContext.cpp
	CBone* BoneData;
};
class CGameBase
{
public:
	char   Unk[0x558];
	CBonesContext* Bones;
};

class RenderData 
{
public:
	char unknownView[0x20];
	D3DXMATRIX ViewMatrix;
	//char unknownProj[0x60];
	D3DXMATRIX ProjMatrix; 
	char unknownWorld[0x1280];
	D3DXMATRIX WorldMatrix;
};

class RenderContext
{
public:
	RenderData* pRenderData; 
};
extern RenderContext *pRC;


