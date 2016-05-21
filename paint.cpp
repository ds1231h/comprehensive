#include "struct.h"

void DrawMyline(HDC hdc, PMYLINE pLine)// 传递一条线
{
	for (int i = 0; i < myCount.line; i++)
	{
		HPEN hPen = CreatePenIndirect(&pLine[i].penInfo);
		HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, pLine[i].ptS.x, pLine[i].ptS.y, NULL);
		LineTo(hdc, pLine[i].ptE.x, pLine[i].ptE.y);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
	}
}

void DrawMyEllipse(HDC hdc, PELLIPSE pgEllipse)
{
	for (int i = 0; i < myCount.ellipse; i++)
	{
		HPEN hPen = CreatePenIndirect(&pgEllipse[i].penInfo);
		HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
		HBRUSH hBr = CreateBrushIndirect(&pgEllipse[i].brInfo);
		HBRUSH hBrOld = (HBRUSH)SelectObject(hdc, hBr);
		Ellipse(hdc, pgEllipse[i].rect.left, pgEllipse[i].rect.top,
			pgEllipse[i].rect.right, pgEllipse[i].rect.bottom);
		SelectObject(hdc,hPenOld);
		SelectObject(hdc,hBrOld);
		DeleteObject(hPen);
		DeleteObject(hBr);
	}
}

void DrawMyRectangle(HDC hdc, PRECTANGLE pgRectangle)
{
	for (int i = 0; i < myCount.rectangle; i++)
	{
		HPEN hPen = CreatePenIndirect(&pgRectangle[i].penInfo);
		HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
		HBRUSH hBr = CreateBrushIndirect(&pgRectangle[i].brInfo);
		HBRUSH hBrOld = (HBRUSH)SelectObject(hdc, hBr);
		Rectangle(hdc, pgRectangle[i].rect.left, pgRectangle[i].rect.top,
			pgRectangle[i].rect.right, pgRectangle[i].rect.bottom);
		SelectObject(hdc,hPenOld);
		SelectObject(hdc,hBrOld);
		DeleteObject(hPen);
		DeleteObject(hBr);
	}
}

void DrawMytext(HDC hdc, PMYTEXT pText)
{
	for (int i=0; i <myCount.message; i++)
	{
		HFONT hfont = CreateFontIndirect(&pText[i].fontInfo);
		HFONT hfontPrev = (HFONT)SelectObject(hdc, hfont);
		SetTextColor(hdc, pText[i].rgbCurrent);
		TextOut(hdc, pgPaints.pgTexts[i].ptS.x, pgPaints.pgTexts[i].ptS.y, 
			(LPCWSTR)pgPaints.pgTexts[i].pBuffer, lstrlen((LPCWSTR)pgPaints.pgTexts[i].pBuffer));// 一直显示最后一次pBuffer的值
		SelectObject(hdc, hfontPrev);
		DeleteObject(hfont);
	}
}

BOOL GetMyColor(HWND hWnd, COLORREF *pColor)
{
	BOOL bRet = FALSE;
	CHOOSECOLOR  cc;
	COLORREF crCustomColors[16] =
	{
		RGB(255, 0, 0),
		RGB(0, 255, 0),
		RGB(0, 0, 255),
	};

	// 给结构体赋值
	cc.lStructSize    = sizeof (CHOOSECOLOR);
	cc.hwndOwner      = hWnd;
	cc.hInstance      = NULL;
	cc.rgbResult      = *pColor;// 颜色选定为通用颜色对话框中当前选中的颜色
	cc.lpCustColors   = crCustomColors;
	cc.Flags          = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData      = 0;
	cc.lpfnHook       = NULL;
	cc.lpTemplateName = NULL;

	if (ChooseColor (&cc))
	{
		*pColor = cc.rgbResult;
		bRet = TRUE;
	}
	return bRet;
}

BOOL GetMyFont(HWND hWnd, LOGFONT *lf, DWORD *rgbCurrent)
{
	CHOOSEFONT  cf;
	HFONT hfont, hfontPrev;
	DWORD rgbPrev;

	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = hWnd;
	cf.lpLogFont = lf;
	cf.rgbColors = *rgbCurrent;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

	if (ChooseFont(&cf)==TRUE)
	{
		*rgbCurrent= cf.rgbColors;
		lf = cf.lpLogFont;
		return TRUE;
	}
	return FALSE;
}