
void DrawBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB(x,(y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB(x + w - px, y, px, h, BorderColor, pDevice);
}

void DrawBox(int x, int y, int w, int h, D3DCOLOR Color, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice) 
{

	DrawBorder(x, y, w, h, 2, BorderColor, pDevice);
	
	const DWORD D3D_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	struct Vertex {
		float x, y, w, h;
		D3DCOLOR Color;
	}
	V[4] = {{(float) x, (float)(y + h), 0.0f, 0.0f, Color}, 
			{(float) x, (float)y, 0.0f, 0.0f, Color}, 
			{(float)(x + w), (float)(y + h), 0.0f, 0.0f, Color}, 
			{(float)(x + w), (float)y, 0.0f, 0.0f, Color}
	};
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, D3DZB_FALSE);

	pDevice->SetFVF(D3D_FVF);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
}

void PrintText(LPD3DXFONT g_pFont, INT x, INT y, DWORD Flags, DWORD Color, CHAR *text, ...)
{
	RECT rec;
	SetRect(&rec, x, y, x, y);
	CHAR logbuf[512] = {0};

	va_list va_alist;
	va_start(va_alist, text);
	vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	
	va_end(va_alist);
	g_pFont->DrawTextA(NULL, logbuf, -1, &rec, Flags, Color);
}

void Item(CHAR *text, CHAR **opt, INT &val, INT maxvalue, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Color1, Color2;
	INT bVar = (val)?(val):0;
	extern INT Current;
	if(Menu && NHT3XT)
	{
		if(MenuSelection == qntHacks)
		{
			if(IsKeyPressed(VK_RIGHT,0))
				if(val < maxvalue - 1)
					val++;
			if(IsKeyPressed(VK_LEFT,0))
				if(val > 0)
					val--;
		}

		Color1 = White;
		Color2 = (bVar)?Green:Red;
		PrintText(NHT3XT, menux + 20, menuy + 20 + (qntHacks * 20), TLeft, Color1, text);
		PrintText(NHT3XT, menux - 15 + mxofs, menuy + 20 + (qntHacks * 20), TRight, Color2, opt[bVar]);
		

		qntHacks++;
	}
	Current++;
}

void Folder(CHAR *text, CHAR **opt, INT &val, INT maxvalue)
{
	DWORD Color1, Color2;
	int bVar = (val)?(val):0;
	extern int Current;
	if(Menu && NHT3XT)
	{
		if(MenuSelection == qntHacks)
		{
			if(IsKeyPressed(VK_RIGHT,0))
				if(val < maxvalue - 1)
					val++;
			if(IsKeyPressed(VK_LEFT,0))
				if(val > 0)
					val--;
		}

		Color1 = Yellow;
		Color2 = (bVar)?Yellow:Yellow;

		PrintText(NHT3XT, menux + 20, menuy + 20 + (qntHacks * 20), TLeft, Color1, text);
		PrintText(NHT3XT, menux - 15 + mxofs, menuy + 20 + (qntHacks * 20), TRight, Color2, opt[bVar]);

		qntHacks++;
	}
	Current++;
}











