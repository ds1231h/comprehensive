#include "struct.h"


int goCount;
BOOL gLoad;
int gDrawMode = DRAW_LINE;
MYLINE gLines;
MYELLIPSE gEllipse;
MYRECTANGLE gRectangle;
LOGPEN gPenInfo = {PS_SOLID, 1, RGB(0,0,0)};
LOGBRUSH gBrInfo = { BS_SOLID, RGB(255,255,255), NULL};
LOGFONT gFontInfo;

int WINAPI WinMain(HINSTANCE hInstance,         //当前实例句柄
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	MSG msg;

	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("EasyWin");
	HWND hwnd;
	WNDCLASS wcMainWnd;
	ATOM a;

	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcMainWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcMainWnd.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcMainWnd.lpszClassName = szAppName;

	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("简易绘图——作者：穆沛"),
		WS_OVERLAPPEDWINDOW | WS_EX_LEFT,
		100,
		100,
		400,
		300,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd) return FALSE;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	HMENU hMenu;

	switch (message)
	{
	case WM_CREATE:
		goCount = 2;
		gLoad =FALSE;
		return 0;

	case WM_INITMENUPOPUP:
		if (lParam == 1)
		{
			if (gDrawMode == DRAW_LINE)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_CHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
			}
			else if (gDrawMode == DRAW_RECT)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_CHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
			}
			else if (gDrawMode == DRAW_ELIP)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_CHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
			}
			else if (gDrawMode == MYMESSAGE)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_CHECKED);
			}
		}
		return 0;

	case WM_COMMAND:
		hMenu = GetMenu(hWnd);

		if (lParam == 0)
		{
			switch(LOWORD(wParam))
			{
			case ID_FILE_mySAVE:
				if (!MySaveData())
				{
					MessageBox(hWnd, TEXT("save data error!"), TEXT("error"), TRUE);
				}
				return 0;

			case ID_FILE_myLOAD:
				if (!MyLoadData())
				{
					MessageBox(hWnd, TEXT("load data error!"), TEXT("error"), TRUE);
				}
				return 0;

			case ID_DRAW_DRAWMYLINE:
			case ID_DRAW_DRAWMYLINES:
				gDrawMode = 1;
				return 0;

			case ID_DRAW_DRAWMYELLIPSE:
				gDrawMode = 3;
				return 0;

			case ID_DRAW_DRAWMYRECTANGLE:
				gDrawMode = 2;
				return 0;

			case ID_DRAW_MESSAGE:
				gDrawMode = 4;
				return 0;

			case ID_SETTING_PEN:
				GetMyColor(hWnd, &gPenInfo.lopnColor);
				return 0;

			case ID_SETTING_BRUSH:
				GetMyColor(hWnd, &gBrInfo.lbColor);
				break;
			}
		}

		// 取得开始位置与终止位置坐标
	case WM_LBUTTONDOWN:
		if(gDrawMode == DRAW_LINE)
		{
			gLines.ptS.x = GET_X_LPARAM(lParam);
			gLines.ptS.y = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == DRAW_RECT)
		{
			gRectangle.rect.left = GET_X_LPARAM(lParam);
			gRectangle.rect.top = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == DRAW_ELIP)
		{
			gEllipse.rect.left = GET_X_LPARAM(lParam);
			gEllipse.rect.top = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == MYMESSAGE)
		{
			gTexts.ptS.x = GET_X_LPARAM(lParam);
			gTexts.ptS.y = GET_Y_LPARAM(lParam);
			// 弹出对话框输入文本内容
			if (DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				MAKEINTRESOURCE(IDD_DIALOG1),
				hWnd, TextInputDlgProc) == IDOK)
			{
				AddOneTextInfo(gTexts);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		return 0;

	case WM_LBUTTONUP:
		if(gDrawMode == DRAW_LINE)
		{
			gLines.ptE.x = GET_X_LPARAM(lParam);
			gLines.ptE.y = GET_Y_LPARAM(lParam);
			gLines.penInfo = gPenInfo;
			AddOneLineInfo(gLines);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (gDrawMode == DRAW_RECT)
		{
			gRectangle.rect.right = GET_X_LPARAM(lParam);
			gRectangle.rect.bottom = GET_Y_LPARAM(lParam);
			gRectangle.brInfo = gBrInfo;
			gRectangle.penInfo = gPenInfo;
			AddOneRectInfo(gRectangle);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (gDrawMode == DRAW_ELIP)
		{
			gEllipse.rect.right = GET_X_LPARAM(lParam);
			gEllipse.rect.bottom = GET_Y_LPARAM(lParam);
			gEllipse.brInfo = gBrInfo;
			gEllipse.penInfo = gPenInfo;
			AddOneEllipseInfo(gEllipse);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:
		hdc=BeginPaint (hWnd, &ps);
		GetClientRect (hWnd, &rect);
		DrawMyline(hdc, pgLines);
		DrawMyLines(hdc, pgLines, goCount);
		DrawMyEllipse(hdc, pgEllipse);
		DrawMyRectangle(hdc, pgRectangle);
		for (int i=0; i <goCountmessage; i++)
		{
			TextOut(hdc, pgTexts[i].ptS.x, pgTexts[i].ptS.y, 
				(LPCWSTR)pgTexts[i].szText, lstrlen((LPCWSTR)pgTexts[i].szText));
		}
		EndPaint(hWnd, &ps ); 
		return 0;

	case WM_DESTROY:
		FreeBuffer();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

