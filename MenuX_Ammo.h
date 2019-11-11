
void _fastcall MenuX_SmartAmmoX(LPDIRECT3DDEVICE9 pDevice)
{
	{
		if(SmartAmmoX==1)
		{
			if(*(PBYTE) GetCalculateAmmo == 2)
			{
				ReadAmmoo = true;
			}
		}
		if(SmartAmmoX == 0)
		{
			ReadAmmoo = false;
		}
		if(ReadAmmoo == false)
		{
			__ReadMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x1C, 0xC79, 1);
			__ReadMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x1C, 0xC8D, 2);
			__ReadMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x1C, 0xC94, 3);
			__ReadMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x1C, 0xC98, 4);
			__ReadMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, 0x1C, 0xCA0, 5);
		}
		if(ReadAmmoo == true)
		{
			if(*(PBYTE) GetCalculateAmmo == 1)
			{
				for (int i=0x1C;i<=0x21;i+=4)
				{
					_WriteMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, i, 0xC79, WriteVaL1);
					_WriteMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, i, 0xC8D, WriteVaL2);
					_WriteMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, i, 0xC94, WriteVaL3);
					_WriteMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, i, 0xC98, WriteVaL4);
					_WriteMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, i, 0xCA0, WriteVaL4);
					_WriteMEM((DWORD)ResultBaseAmmo2, PTR_BaseAmmo, i, 0xCC0, WriteVaL5);
				}
			}
		}
	}
}


