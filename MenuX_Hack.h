DWORD MenuX_Hack()
{
	while(1)
	{
		//======================================================//
		//                  Desk : BrussKnife		            //
		//======================================================//
		if(bPiso == false)
		{
			BurstPiso	= _ReadMEM( (DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x24, 0xC94);
		}
		if(BrussKnife == 0)
		{
			bPiso = false;
			_WriteMEM( (DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x24, 0xC94, BurstPiso);
		}
		if(BrussKnife == 1)
		{
			bPiso = true;
			_WriteMEM( (DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x24, 0xC94, BurstPiso);
		}
		//======================================================//
		//                  Desk : FastChange	                //
		//======================================================//
		if(QuickChange==1)
		{
			if(IsBadReadPtr((void*)ResultBaseAmmo2,4)==0)
			{
				DWORD TheRead = *(PDWORD)((DWORD)ResultBaseAmmo2)+PTR_BaseAmmo-4;
				if(IsBadReadPtr((void*)TheRead,4)==0)
				{
					DWORD ReadKe1 = *(PDWORD)((DWORD)(TheRead))+0xEC;
					if(IsBadReadPtr((void*)ReadKe1,4)==0)
					{
						DWORD ReadKe2 = *(PDWORD)((DWORD)(ReadKe1))+0x67;
						if(IsBadReadPtr((void*)ReadKe2,4)==0)
						{
						*(PDWORD)ReadKe2=0x3FC28F5B;
						Sleep(50*2);
						}
					}
				}
			}
		}

		//======================================================//
		//                  Desk : NoRecoil		                //
		//======================================================//
		if(Recoil==1)
		{
			for(int d=0x20;d<=0x50;d+=4)
			{
				_WriteMEM((DWORD)ResultBaseAmmo2,PTR_NoRecoil,d,0x00000000);
			}
		}
		//======================================================//
		//                  Desk : Fast Reload		            //
		//======================================================//
		if(Reload==1)
		{
			for(int Kudet=0x1C;Kudet<=0x20;Kudet+=4)
			{
				if(IsBadReadPtr((void*)ResultBaseAmmo2,4)==0)
				{
					DWORD TheRead = *(PDWORD)((DWORD)ResultBaseAmmo2)+PTR_BaseAmmo;
					if(IsBadReadPtr((void*)TheRead,4)==0)
					{
						DWORD ReadKe1 = *(PDWORD)((DWORD)(TheRead))+Kudet;
						if(IsBadReadPtr((void*)ReadKe1,4)==0)
						{
							DWORD ReadKe2 = *(PDWORD)((DWORD)(ReadKe1))+0x30;
							if(IsBadReadPtr((void*)ReadKe2,4)==0)
							{
								DWORD ReadKe3 = *(PDWORD)((DWORD)(ReadKe2))+0x67;
								if(IsBadReadPtr((void*)ReadKe3,4)==0)
								{
									*(PDWORD)ReadKe3=0x41;
									Sleep(25*2);
								}
							}
						}
					}
				}
			}
		}
		//======================================================//
		//                  Desk : WEAPON BUG	                //
		//======================================================//

		if(WeaponBug_ ==1)
		{
			DWORD pBaseX = (DWORD)GetModuleHandleA("Pointblank.exe");
			NHMemFuction((void *)(pBaseX + WeaponBugs),(int*)(PBYTE)"\xC0",1);
		}


		if(WeaponBug_ ==0)
		{
			DWORD pBaseX = (DWORD)GetModuleHandleA("Pointblank.exe");
			NHMemFuction((void *)(pBaseX + WeaponBugs),(int*)(PBYTE)"\xBE",1);
		}
		//======================================================//
		//                  Desk : WALLBUG			            //
		//======================================================//

		if(WTW==1)
		{
			NHMemFuction((void *)((DWORD)LoadLibraryA("NxCharacter.2.8.1.dll")+0x16510),(int*)(PBYTE)"\x89\x8B\x38",3);
		}

		if(WTW==0)
		{	
			NHMemFuction((void *)((DWORD)LoadLibraryA("NxCharacter.2.8.1.dll")+0x16510),(int*)(PBYTE)"\x89\x8B\x34",3);
		}
		//======================================================//
		//                  Desk : Fast Bullet					//
		//======================================================//
		

		if (xFirex==1)
		{
			if(IsBadReadPtr((void*)ResultBaseAmmo2,4)==0)
			{
				DWORD TheRead = *(PDWORD)((DWORD)ResultBaseAmmo2)+PTR_BaseAmmo;
				if(IsBadReadPtr((void*)TheRead,4)==0)
				{
					DWORD ReadKe1 = *(PDWORD)((DWORD)(TheRead))+0x38;
					if(IsBadReadPtr((void*)ReadKe1,4)==0)
					{	
						*(PDWORD)ReadKe1=0x02;
						Sleep(250);
					}
					DWORD ReadKe2 = *(PDWORD)((DWORD)(TheRead))+0x3C;
					if(IsBadReadPtr((void*)ReadKe2,4)==0)
					{
						*(PDWORD)ReadKe1=0x02;
						Sleep(250);
					}
				}
			}
		}

		if(RefitFire == 1)
		{
			if(GetAsyncKeyState(VK_LBUTTON))
			{
				xFirex = 1;
				//Sleep(100);// kalau kurang cepat kurangin Sleepnya :3
			}
			else 
			{
				xFirex = 0;
				Sleep(0.5);
			}
		}


	}
	return 0;
}