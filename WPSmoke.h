//=========================MODE WP SMOKE===========================//
DWORD ALEXDoLineColly1(UINT i)
{
	D3DXVECTOR3	vBone, vLocal;
	DWORD DoLineCollyyy;
	int TargetBonex;
	switch(AimBody)
	{
	case 0:
		TargetBonex = 7.7; // Kepala
		break;
	case 1:
		TargetBonex = 5; // Badan
		break;
	case 2:
		TargetBonex = 2; // Perut
		break;
	case 3:
		TargetBonex = 0; // Vital
		break;
	case 4:
		TargetBonex = 12; // Pinggang Kiri
		break;
	case 5:
		TargetBonex = 13; // Pinggang Kanan
		break;
	case 6:
		TargetBonex = 14; // Lutut Kiri
		break;
	case 7:
		TargetBonex = 15; // Lutut Kanan
		break;
	case 8:
		TargetBonex = 8; // Kaki Kiri
		break;
	case 9:
		TargetBonex = 9; // Kaki Kanan
		break;
	case 10:
		TargetBonex = 10; // Tangan Kiri
		break;
	case 11:
		TargetBonex = 11; // Tangan Kanan
		break;
	}
	dwBasett   = ALEXYONGKIGANTENG1(OFS_Ammo2, resultpointer1baseALEXCallHitEvent , 0x2C);
	baseDoLineColly = ALEXYONGKIGANTENG4 (baseDoLineCollyy);
	getVCPos(&vLocal,0,0);
	vBone = GetUserBonePos2(i,TargetBonex);
	if (dwBasett)
	{
		DoLineCollyyy = ((DWORD (__thiscall *)(DWORD, D3DXVECTOR3*, D3DXVECTOR3*, DWORD))baseDoLineColly)(dwBasett, &vLocal, &vBone, GetTeam1(i));
	}
	return DoLineCollyyy;
}

#define baseALEXCallHitEventt 0x8D2FC0
//=========================MODE WP SMOKE===========================//
DWORD ALEXCallHitEvent1(UINT i)
{
	D3DXVECTOR3	vEnemy;
	DWORD ALEXCallHitEventtt;
	dwBasett   = ALEXYONGKIGANTENG1(OFS_Ammo2, 0x544, 0x1C);
	dwBasetttt   = ALEXYONGKIGANTENG3(OFS_Ammo2);
	baseALEXCallHitEvent = ALEXYONGKIGANTENG4(baseALEXCallHitEventt);
    getVCPos(&vEnemy,0,0);
    if (dwBasett)
	{
		ALEXCallHitEventtt = ((DWORD (__thiscall *)(DWORD, DWORD, D3DXVECTOR3*, DWORD))baseALEXCallHitEvent)(dwBasett, dwBasetttt, &vEnemy, dwBasett);
	}
	return ALEXCallHitEventtt;
}

//=========================MODE WP SMOKE===========================//

void ALEXCallDoLineColly1()
{
	for (int i = 0; i < 16; i++)
	{
		if (!GetMyCharaIndexed (i))continue;
		if(GetTeam1(GetMyCharaIndexed (i)) == GetTeam1(i))continue;
		if(IsAlive(i)){
		ALEXDoLineColly1(i);
		}
	}
}

//=========================MODE WP SMOKE===========================//
void ALEXHitEvent1()
{
	for (int i = 0; i < 16; i++)
	{
		if (!GetMyCharaIndexed (i))continue;
		if(GetTeam1(GetMyCharaIndexed (i)) == GetTeam1(i))continue;
		ALEXCallHitEvent1(i);
		if(IsAlive(i)){				
		ALEXCallHitEvent1(i);
		}
	}

}
//=========================MODE WP SMOKE===========================//
void IamKillYou1()
{
if(GetBattleState1()){
if(PisoTeleKill1){
ALEXCallDoLineColly1();
DamagePisoTeleKill1=1;
}
if(PisoTeleKill1==0){
DamagePisoTeleKill1=0;
}
if(DamagePisoTeleKill1==1){
	ALEXHitEvent1();
}
}}