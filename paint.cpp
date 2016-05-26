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
