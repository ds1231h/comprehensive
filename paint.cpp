#include "struct.h"

void DrawMyline(HDC hdc, PMYLINE pLine)// ����һ����
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

void DrawMyLines(HDC hdc, PMYLINE pLines, int iCount)// ����һ����
{
	for (int i = 0; i < iCount; i++)
	{
		DrawMyline(hdc, pLines);
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

	// ���ṹ�帳ֵ
	cc.lStructSize    = sizeof (CHOOSECOLOR);
	cc.hwndOwner      = hWnd;
	cc.hInstance      = NULL;
	cc.rgbResult      = *pColor;// ��ɫѡ��Ϊͨ����ɫ�Ի����е�ǰѡ�е���ɫ
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
