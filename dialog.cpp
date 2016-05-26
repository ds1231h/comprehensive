#include "struct.h"

BOOL CALLBACK TextInputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			AddTextBuffer();
			GetDlgItemText(hDlg, IDC_EDIT1, (LPWSTR)pgPaints.gTexts.pBuffer, 128);
			EndDialog(hDlg, TRUE);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
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
