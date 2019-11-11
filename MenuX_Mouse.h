void MenuX_Mouse(LPDIRECT3DDEVICE9 pDevice)
{
	Current = 1;
	pMenu.AddTab("DirectX"	,67  , 45, MenuX_TAB, 1,pDevice); 
	pMenu.AddTab("ESP"		,156 , 45, MenuX_TAB, 2, pDevice);
	pMenu.AddTab("AIM"		,245 , 45, MenuX_TAB, 3, pDevice);
	pMenu.AddTab("Memory"	,334 , 45, MenuX_TAB, 4, pDevice);
	pMenu.AddTab("Setting"	,423 , 45, MenuX_TAB, 5, pDevice);

	if(MenuX_TAB == 1)
	{
		pMenu.AddCheck("WallHack"		, SwiftONOF		,Nh_Teknology32	,1	,pDevice);
		pMenu.AddCheck("Chams Teror"	, optColor2		,Nh_Teknology30	,9	,pDevice);
		pMenu.AddCheck("Chams Swat"		, optColor2		,Nh_Teknology31 ,9	,pDevice);
		pMenu.AddCheck("Remove Smoke"	, SwiftONOF		,Nh_Teknology33 ,1	,pDevice);
		pMenu.AddCheck("CrossHair"		, optcrosshair	,Nh_Teknology34 ,2	,pDevice);
	}

	if(MenuX_TAB == 2)
	{
		pMenu.AddCheck("ESP Line"		, SwiftONOF		,Nh_Teknology1	,1	,pDevice);
		pMenu.AddCheck("ESP Health"		, SwiftONOF		,Nh_Teknology2	,1	,pDevice);
		pMenu.AddCheck("ESP Bone"		, SwiftONOF		,Nh_Teknology3	,1	,pDevice);
		//pMenu.AddCheck("ESP Tag"		, SwiftONOF		,Nh_Teknology4	,1	,pDevice);
		pMenu.AddCheck("ESP Box"		, SwiftONOF		,Nh_Teknology26	,1	,pDevice);
		pMenu.AddCheck("ESP Observer"	, SwiftONOF		,Nh_Teknology27	,1	,pDevice);
	}

	if(MenuX_TAB == 3)
	{
		pMenu.AddCheck("AIM Bullet"		, SwiftONOF		,Nh_Teknology8	,1	,pDevice);
		pMenu.AddCheck("Target AIM"		, MopTarget		,Nh_Teknology7	,1	,pDevice);
        pMenu.AddCheck("Target Random"	, SwiftONOF		,Nh_NEWAIM		,1	,pDevice);
		pMenu.AddCheck("WPSmoke Killer" , SwiftONOF		,PisoTeleKill1	,1	,pDevice);
	}
	if(MenuX_TAB == 4)
	{
		pMenu.AddCheck("Weapon Bugs"	, SwiftONOF		,WeaponBug_		,1	,pDevice);
		pMenu.AddCheck("Wall Bugs"		, SwiftONOF		,WTW			,1	,pDevice);
		pMenu.AddCheck("Smart Ammo"		, SwiftONOF		,SmartAmmoX		,1	,pDevice);
		pMenu.AddCheck("Norecoil"		, SwiftONOF		,Recoil			,1	,pDevice);
		pMenu.AddCheck("Fast Change"	, SwiftONOF		,QuickChange	,1	,pDevice);
		pMenu.AddCheck("Fast Reload"	, SwiftONOF		,Reload			,1	,pDevice);
		pMenu.AddCheck("Fast Knife"		, SwiftONOF		,BrussKnife		,1	,pDevice);
	}
	if(MenuX_TAB == 5)
	{
		pMenu.AddCheck("Keyboard MenuX"	, SwiftONOF		,MenuX_sShow	,1	,pDevice);
		pMenu.AddText ("Date MenuX"					,GetDate()	,pDevice);
		pMenu.AddText ("Time MenuX"					,GetTime()	,pDevice);
		pMenu.AddText ("FrameRate MenuX"			,ShowFPS()	,pDevice);
		pMenu.AddText ("Net Name"					,"RGC-NET"			,pDevice);
		pMenu.AddText ("Abaut MenuX"				,"RIZKY"			,pDevice);	
	}
}

void Navigation_M(LPDIRECT3DDEVICE9 pDevice)
{

	if(Menu && NHT3XT)
	{
		MenuX_Mouse(pDevice);
	}
}

void MenuSettings_M()
{
	menux = 10;
	menuy = 10;
	mxofs = 180;
	qntHacks = 0;
}

VOID RenderMenu_M(LPDIRECT3DDEVICE9 pDevice)
{
	MenuSettings_M();
	if(Menu && NHT3XT)
	{	
		/* Main body */
		FillGradients (20,10,80 + (Current * 20),450,Menu_background,Menu_background,pDevice);
		pMenu.Rectangle(20, 10, 450, 80 + (Current * 20), Menu_rectangle, pDevice);
		pMenu.Rectangle(19, 9, 452, 80 + (Current * 20), Menu_special, pDevice);
		/* Windows Title */
		FillGradients (20,10,20,450,White,Grey,pDevice);
		pMenu.Rectangle(20, 10, 450, 20, Menu_rectangle, pDevice);
		pMenu.DrawString(mTitle, 230, 12, TitleText, 1);
		/* Main Minimazes */
		FillGradients (450,12,15,15,Red,Maroon,pDevice);  
		DrawBorders (450,12,15,15,1,Black,pDevice);
		Draw_Text ("_",453,10,White,NHT3XT);
		/* Item body */
		pMenu.Rectangle(31, 61, 428, 12 + (Current * 20), Menu_rectangle, pDevice);
		pMenu.Rectangle(30, 60, 430, 14 + (Current * 20), Menu_special, pDevice);
		/*Title Fitur*/
		FillGradients (31,61,30,220,White,Grey,pDevice);
		pMenu.Rectangle(31, 61, 220, 30, Menu_rectangle, pDevice);
		pMenu.DrawString(mFitTitle, 145, 68, TitleText, 1);
		/* Title Credit */
		FillGradients (249,61,30,210,White,Grey,pDevice);
		pMenu.Rectangle(249, 61, 210, 30, Menu_rectangle, pDevice);
		pMenu.DrawString(mDecTitle, 355, 68, TitleText, 1);
		/*Credit*/
		pMenu.DrawString(mCredits, 355, 102, Title, 1);
		/* Function box */
		pMenu.Rectangle(250, 61, 1, 12 + (Current * 20), Menu_rectangle, pDevice);
		

	}
	Navigation_M(pDevice);
}