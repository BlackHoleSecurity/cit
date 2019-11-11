#include "MenuX_ESP_Struct.h"
#include "MenuX_Function_Fitur.h"
//----------------------Esp Mode-------------------------------//
bool bHookedTele = false;
int GetTeam(char MyT);;
int GetTeam(char MyT)
{
	if(bHookedTele == true)
	{
		if (MyT == 0 ||MyT == 2||MyT == 4||MyT == 6||MyT == 8||MyT == 10||MyT == 12||MyT == 14)return 1;
		else
		if (MyT == 1 ||MyT == 3||MyT == 5||MyT == 7||MyT == 9||MyT == 11||MyT == 13||MyT == 15)return 2;
	  bHookedTele = false;
	}
	return 0;
}

void MenuX_Esp(LPDIRECT3DDEVICE9 pDevice)
{
	unsigned long dwBase	= *(DWORD*)ResultPlayerBase;
	unsigned long dwBase2	= *(DWORD*)ResultBaseESP;	
	CTeam		*pTeam		= ((CTeam*)(dwBase+PTR_TEAM));
	float ScreenCenterX = (NhViewport.Width /2.0f);
	float ScreenCenterY = (NhViewport.Height /2.0f);
	float ScreenBottomY = (NhViewport.Height);
	for (int i = 0; i<=15; i++)
	{
		if (dwBase !=0)
		{
			CHealth		*pHealth	= (CHealth*)((dwBase2 + 0x264) + i * 0x20);
			CNames		*pNames		= (CNames*) ((dwBase + PTR_NAMES) + i * 0x21);
			bHookedTele = true;
			int MySlot = GetTeam(GetMyCharaIndex()); 
			DWORD pCalculate = *(DWORD*)(dwBase + 0x4 * i + PTR_PLAYER );
			DWORD pCalculate2 = *(DWORD*)(dwBase + 0x4 * pTeam->iTeam + PTR_PLAYER );
			CPlayers	*pPlayer	= (CPlayers*)(pCalculate + 0x64 );
			CPlayers	*pLocal		= (CPlayers*)(pCalculate2 + 0x64 );
			D3DXVECTOR3 MyDistance	=	pLocal->pos - pPlayer->pos;
			float MyaDistance = D3DXVec3Length(&MyDistance );
			if(GetTeam(i) == MySlot) continue; 
			int myTeam	= GetTeam(i);
			if(GetUserBone(vStart10,15,i))
			{
				if(GetUserBone(vEnd10,9,i))
				{
					if(YoWorlToScreenGa(vStart10,vvStart10))
					{
						if(YoWorlToScreenGa(vEnd10,vvEnd10))
						{
							if (pHealth->CurHP > 1)
							{

								if (Nh_Teknology2 == 1)
								{
									HealthBar15((int)vvStart10.x-25,(int)vvEnd10.y+10,pHealth->CurHP);
								}
								if (Nh_Teknology1)	
								{
									DrawLine ((int)ScreenCenterX,(int)ScreenBottomY,(int)vvStart10.x,(int)vvEnd10.y,1,pHealth->CurHP);
								}
								if (Nh_Teknology26)
								{
									DrawBoxESP((float)vvStart10.x-(5000/MyaDistance)/30,(float)vvEnd10.y-(35000/MyaDistance)/45, 50000/MyaDistance/6*2/40,50000/MyaDistance/3*2/40, pHealth->CurHP, pDevice);
								}
							}
						}
					}
				}
			}
			if(GetUserBone(vEnd10,7,i))
			{
				if(YoWorlToScreenGa(vEnd10,vvEnd10))
				{
					if (pHealth->CurHP > 1)
					{
						if (Nh_Teknology4)		
						{
							DrawStringESP(vvEnd10.x-10,vvEnd10.y-40,Red," %s ",pNames->szNames);
							DrawStringESP(vvEnd10.x-9,vvEnd10.y-41,Black," %s ",pNames->szNames);
							DrawStringESP(vvEnd10.x-9,vvEnd10.y-42,Black," %s ",pNames->szNames);
						}
						
					}
				}
			}
			if (pHealth->CurHP > 1)
			{
				if(Nh_Teknology3 == 1)
				{
					if(GetUserBone(vStart,6,i))
					{
						if(GetUserBone(vEnd,7,i))
						{
							if(YoWorlToScreenGa(vStart,vvStart))
							{
								if(YoWorlToScreenGa(vEnd,vvEnd))
								{
									if(GetUserBone(vStart2,6,i))
									{
										if(GetUserBone(vEnd2,0,i))
										{
											if(YoWorlToScreenGa(vStart2,vvStart2))
											{
												if(YoWorlToScreenGa(vEnd2,vvEnd2))
												{
													if(GetUserBone(vStart3,6,i))
													{
														if(GetUserBone(vEnd3,10,i))
														{
															if(YoWorlToScreenGa(vStart3,vvStart3))
															{
																if(YoWorlToScreenGa(vEnd3,vvEnd3))
																{
																	if(GetUserBone(vStart4,6,i))
																	{
																		if(GetUserBone(vEnd4,11,i))
																		{
																			if(YoWorlToScreenGa(vStart4,vvStart4))
																			{
																				if(YoWorlToScreenGa(vEnd4,vvEnd4))
																				{
																					if(GetUserBone(vStart5,0,i))
																					{
																						if(GetUserBone(vEnd5,12,i))
																						{
																							if(YoWorlToScreenGa(vStart5,vvStart5))
																							{
																								if(YoWorlToScreenGa(vEnd5,vvEnd5))
																								{
																									if(GetUserBone(vStart6,0,i))
																									{
																										if(GetUserBone(vEnd6,13,i))
																										{
																											if(YoWorlToScreenGa(vStart6,vvStart6))
																											{
																												if(YoWorlToScreenGa(vEnd6,vvEnd6))
																												{
																													if(GetUserBone(vStart7,12,i))
																													{
																														if(GetUserBone(vEnd7,14,i))
																														{
																															if(YoWorlToScreenGa(vStart7,vvStart7))
																															{
																																if(YoWorlToScreenGa(vEnd7,vvEnd7))
																																{
																																	if(GetUserBone(vStart8,13,i))
																																	{
																																		if(GetUserBone(vEnd8,15,i))
																																		{
																																			if(YoWorlToScreenGa(vStart8,vvStart8))
																																			{
																																				if(YoWorlToScreenGa(vEnd8,vvEnd8))
																																				{
																																					if(GetUserBone(vStart9,14,i))
																																					{
																																						if(GetUserBone(vEnd9,8,i))
																																						{
																																							if(YoWorlToScreenGa(vStart9,vvStart9))
																																							{
																																								if(YoWorlToScreenGa(vEnd9,vvEnd9))
																																								{
																																									if(GetUserBone(vStart10,15,i))
																																									{
																																										if(GetUserBone(vEnd10,9,i))
																																										{
																																											if(YoWorlToScreenGa(vStart10,vvStart10))
																																											{
																																												if(YoWorlToScreenGa(vEnd10,vvEnd10))
																																												{
																																													DrawLine(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,pHealth->CurHP); //leher
																																													DrawLine(vvStart2.x,vvStart2.y,vvEnd2.x,vvEnd2.y,1,pHealth->CurHP);//Badan
																																													DrawLine(vvStart3.x,vvStart3.y,vvEnd3.x,vvEnd3.y,1,pHealth->CurHP);//Tangan Kiri
																																													DrawLine(vvStart4.x,vvStart4.y,vvEnd4.x,vvEnd4.y,1,pHealth->CurHP);//Tangan Kanan
																																													DrawLine(vvStart5.x,vvStart5.y,vvEnd5.x,vvEnd5.y,1,pHealth->CurHP);//Lengan Kiri
																																													DrawLine(vvStart6.x,vvStart6.y,vvEnd6.x,vvEnd6.y,1,pHealth->CurHP);//Lengan Kanan
																																													DrawLine(vvStart7.x,vvStart7.y,vvEnd7.x,vvEnd7.y,1,pHealth->CurHP);//Paha Kiri
																																													DrawLine(vvStart8.x,vvStart8.y,vvEnd8.x,vvEnd8.y,1,pHealth->CurHP);//Paha Kanan
																																													DrawLine(vvStart9.x,vvStart9.y,vvEnd9.x,vvEnd9.y,1,pHealth->CurHP);//Kaki Kiri
																																													DrawLine(vvStart10.x,vvStart10.y,vvEnd10.x,vvEnd10.y,1,pHealth->CurHP);//Kaki Kanan
																																												}
																																											}
																																										}
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}	
bHookedTele = false;
}
#include "MenuX_Observer.h"
