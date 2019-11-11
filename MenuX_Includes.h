#include <Windows.h>
#include <stdio.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <time.h>


//Pragmas
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "Winmm.lib")

//Texture
LPDIRECT3DVERTEXBUFFER9 iStreamData;
UINT iOffset = 0;
UINT iStride = 0;
LPDIRECT3DDEVICE9 i3Device;
D3DVIEWPORT9 NhViewport;

//Fonts
LPD3DXFONT NHT3XT	= NULL;

//Line
ID3DXLine *NHLine;

//Font Create
bool FontCreate = true;

//Text settings
char * mTitle		= ".::MASMEN TELAH KEMBALI::.";
char * mFitTitle	= ".::Fitur::.";
char * mDecTitle	= ".::Credits::.";
char * mExtra		= "\n\n\n\n";
char * mCredits		= "Credit By : Ki Ageng Cyberz\nContact :\nwww.facebook.com/men.elektro\nCopyright © 2015-2018\nAll Rights Reserved";
char Text[80];

//Mediaplay
int Play;
int Song;
int Browse;
int Next;
int Previous;

//Scroll bar
bool Scroll = false;


//==================================================================
// This file is part of Masmen D3D Private part 2
// Creadit Masmen
//==================================================================

#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <d3dx9.h>
#include <time.h>
//==========pragma comment========
#pragma comment(lib, "d3dx9.lib")
#pragma warning(disable:4996 4244)
#pragma warning(disable:4700 4293 4554)

using namespace std;
int PILIHAN1=0;
int PILIHAN2=0;
int PILIHAN3=0;
int PILIHAN4=0;
int PILIHAN5=0;
int PILIHAN6=0;
int PILIHAN7=0;
int GameFastExit;
int Nh_Teknology;
//-----ESP-----//
int Nh_Teknology1;
int Nh_Teknology2;
int Nh_Teknology3;
int Nh_Teknology4;
int Nh_Teknology26;
int Nh_Teknology27;
//-Deklarsi AIM-//
int Nh_Teknology5;
int Nh_Teknology6;
//---Call_AIM---//
int Nh_Teknology7;  //AIMTARGET
int Nh_Teknology8;  //AIMBULLET
int Nh_Teknology9;	//AIM SHOOT
int Nh_Teknology10; //AIM LOCKTARGET
int Nh_NEWAIM;
//---CallHack---//
int BrussKnife;
int SmartAmmoX;
int QuickChange;
int Recoil;
int Reload;
int WeaponBug_;
int WTW;
int xFirex, RefitFire;
int PisoTeleKill1;
int DamagePisoTeleKill1;


//---VISUALWH---//
int Nh_Teknology29;
int Nh_Teknology30;
int Nh_Teknology31;
int Nh_Teknology32;
int Nh_Teknology33;
int Nh_Teknology34;

bool bReload	= false;
bool bPiso		= false;
bool ReadAmmoo	= false;

#pragma message("SourceCode Database By: Ki Ageng Cyberz")
#pragma message("Author : Masmen")
#define HTSN(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);
