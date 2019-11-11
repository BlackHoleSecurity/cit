void menu::BoardersMinimize(LPDIRECT3DDEVICE9 pDevice)
{
	/* Main body */
	FillGradients (20,10,20,450,Menu_background,Menu_background,pDevice);
	Rectangle(20, 10, 450, 21, Menu_rectangle, pDevice);
	Rectangle(19, 9, 452, 21, Menu_special, pDevice);

	/* Windows Title */
	FillGradients (20,10,20,450,White,Grey,pDevice);
	Rectangle(20, 10, 450, 20, Menu_rectangle, pDevice);
	DrawString(mTitle, 230, 12, TitleText, 1);

	/* Main Minimazes */
	FillGradients (450,12,15,15,Red,Maroon,pDevice);  // x - 30  / y - 40 - 20
	DrawBorders (450,12,15,15,1,Black,pDevice);
	Draw_Text ("_",453,10,White,NHT3XT);
}
